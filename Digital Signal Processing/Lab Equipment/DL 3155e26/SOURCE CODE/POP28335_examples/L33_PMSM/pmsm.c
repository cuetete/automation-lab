/* ==============================================================================
System Name:  PMSM32

File Name:	PMSM3_2.C

Description:	Primary system file for the Real Implementation of Sensorless  
          		Field Orientation Control for a Three Phase Permanent-Magnet
          		Synchronous Motor (PMSM) using sliding-mode rotor position estimator

Originator:		Digital control systems Group - Texas Instruments

Note: In this software, the default inverter is supposed to be DMC1500 board. 
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20: Support both F280x and F281x targets 
 04-25-2005 Version 3.21: Move EINT and ERTM down to ensure that all initialization
 						  is completed before interrupts are allowed.
=================================================================================  */

// Include header files used in the main function
#include "PeripheralHeaderIncludes.h"
#include "IQmathLib.h"
#define   MATH_TYPE      IQ_MATH
#include "HVPM_Sensored.h"
#include "HVPM_Sensored-Settings.h"
#include <math.h>
//#include "stdio.h"
//#include "stdlib.h"

#define DSP28_PLLCR      10
#define DSP28_DIVSEL     2

//float* DutyReadData_x;
//float* Next;
//int16 i=0;
//_iq15 B=_IQ15(0);

//int ChSel[16]   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//int	TrigSel[16] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
//int ACQPS[16]   = {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};
_iq K1=_IQ(0.998);		//Offset filter coefficient K1: 0.05/(T+0.05);
_iq K2=_IQ(0.001999);	//Offset filter coefficient K2: T/(T+0.05);
extern _iq IQsinTable[];
extern _iq IQcosTable[];

// Prototype statements for functions found within this file.
interrupt void PWM_ISR(void);
interrupt void spiTxIsr(void);
interrupt void spiRxIsr(void);
void F28335_ileg2_dcbus_drv_read(ILEG2DCBUSMEAS *p);
void DeviceInit(void);
void PieCntlInit(void);
void PieVectTableInit(void);
void WDogDisable(void);
void InitPll(Uint16,Uint16);
void spi_fifo_init(void);
//add
//void MemCopy();
//void InitFlash();


// Global variables used in this system
_iq Vd_testing = _IQ(0.0);            // Vd testing (pu) 
_iq Vq_testing = _IQ(0.15);         // Vq testing (pu) 
_iq Id_ref = _IQ(0.0);                // Id reference (pu) 
_iq Iq_ref = _IQ(0.1);              // Iq reference (pu) 
_iq speed_ref = _IQ(0.15);           // Speed reference (pu)
int speed_ref_rpm;				// Speed reference (rpm) 
float T = 0.001/ISR_FREQUENCY;   // Samping period (sec), see parameter.h 

Uint16 SendData[8];
Uint16 ReceData[8];

Uint32 IsrTicker = 0;
int BackTicker = 0;

volatile int enable_flag = 1;
int lock_rotor_flag = 0;

int speed_loop_ps = 10;      // Speed loop prescaler
int speed_loop_count = 1;           // Speed loop counter

int16 DlogCh1 = 0;
int16 DlogCh2 = 0;
int16 DlogCh3 = 0;
int16 DlogCh4 = 0; 

// Instance a few transform objects
CLARKE clarke1 = CLARKE_DEFAULTS;
PARK park1 = PARK_DEFAULTS;
IPARK ipark1 = IPARK_DEFAULTS;

// Instance PID regulators to regulate the d and q synchronous axis currents,
// and speed
PI_CONTROLLER pi_spd = PI_CONTROLLER_DEFAULTS;
PI_CONTROLLER pi_id  = PI_CONTROLLER_DEFAULTS;
PI_CONTROLLER pi_iq  = PI_CONTROLLER_DEFAULTS;

// Instance a PWM driver instance
PWMGEN pwm1 = PWMGEN_DEFAULTS;

// Instance a PWM DAC driver instance
PWMDAC pwmdac1 = PWMDAC_DEFAULTS;

// Instance a Space Vector PWM modulator. This modulator generates a, b and c
// phases based on the d and q stationery reference frame inputs
SVGEN svgen1 = SVGEN_DEFAULTS;

// Instance a QEP interface driver 
QEP qep1 = QEP_DEFAULTS; 

// Instance a ramp controller to smoothly ramp the frequency
RMPCNTL rc1 = RMPCNTL_DEFAULTS;

//	Instance a ramp generator to simulate an Anglele
RAMPGEN rg1 = RAMPGEN_DEFAULTS;

// Create an instance of the current/dc-bus voltage measurement driver
ILEG2DCBUSMEAS ilg2_vdc1 = ILEG2DCBUSMEAS_DEFAULTS;

SPEED_MEAS_QEP speed1 = SPEED_MEAS_QEP_DEFAULTS;

// Create an instance of DATALOG Module
DLOG_4CH dlog = DLOG_4CH_DEFAULTS;      

void main(void)
{
	Uint32 i;

	DeviceInit();
// Globally synchronize all ePWM modules to the time base clock (TBCLK)
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
	
// User specific functions, Reassign vectors (optional), Enable Interrupts:

   // Waiting for enable flag set
   while (enable_flag==0) 
    { 
      BackTicker++;
    }
    
// Enable CNT_zero interrupt using EPWM1 Time-base
    EPwm1Regs.ETSEL.bit.INTEN = 1;   // Enable EPWM1INT generation 
    EPwm1Regs.ETSEL.bit.INTSEL = 1;  // Enable interrupt CNT_zero event
    EPwm1Regs.ETPS.bit.INTPRD = 1;   // Generate interrupt on the 1st event
	EPwm1Regs.ETCLR.bit.INT = 1;     // Enable more interrupts

// Reassign ISRs. 
        // Reassign the PIE vector for EPWM1_INT to point to a different 
        // ISR then the shell routine found in DSP280x_DefaultIsr.c.
        // This is done if the user does not want to use the shell ISR routine
        // but instead wants to use their own ISR.

	EALLOW;	// This is needed to write to EALLOW protected registers
	PieVectTable.EPWM1_INT = &PWM_ISR;
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
	PieVectTable.SPIRXINTA = &spiRxIsr;
	PieCtrlRegs.PIEIER6.bit.INTx1 = 1;
	PieVectTable.SPITXINTA = &spiTxIsr;
	PieCtrlRegs.PIEIER6.bit.INTx2 = 1;
	EDIS;   // This is needed to disable write to EALLOW protected registers

// Enable PIE group 3 interrupt 1 for EPWM1_INT
    PieCtrlRegs.PIEIER3.all = M_INT1;
    
    
    PieCtrlRegs.PIEIER6.all = M_INT2;

// Enable CPU INT3 for EPWM1_INT:
	IER |= M_INT3;
	IER |= M_INT6;
//Initialize SPI
	spi_fifo_init();
	   for(i=0; i<8; i++)
   {
      SendData[i] = i;
   }
// Initialize PWM module
    pwm1.PeriodMax = SYSTEM_FREQUENCY*1000000*T/2;  // Prescaler X1 (T1), ISR period = T x 1
    pwm1.HalfPerMax=pwm1.PeriodMax/2;
    pwm1.Deadband  = 2.0*SYSTEM_FREQUENCY;     	    // 120 counts -> 2.0 usec for TBCLK = SYSCLK/1
    PWM_INIT_MACRO(1,2,3,pwm1); 
// Initialize PWMDAC module
	pwmdac1.PeriodMax=500;		   	// @60Mhz, 1500->20kHz, 1000-> 30kHz, 500->60kHz
	pwmdac1.HalfPerMax=pwmdac1.PeriodMax/2;
	PWMDAC_INIT_MACRO(6,pwmdac1); 	// PWM 6A,6B
//	DutyReadData_x = (float*)calloc(1,2000);
// Initialize DATALOG module
    dlog.iptr1 = &DlogCh1;
    dlog.iptr2 = &DlogCh2;
    dlog.iptr3 = &DlogCh3;
    dlog.iptr4 = &DlogCh4;
    dlog.trig_value = 0x1;
    dlog.size = 0x400;
    dlog.prescalar = 5;
    dlog.init(&dlog);

// Initialize QEP module
    qep1.LineEncoder = 2500;
    qep1.MechScaler = _IQ30(0.25/qep1.LineEncoder);
    qep1.PolePairs = POLES/2;
    qep1.CalibratedAngle = 1000;
    QEP_INIT_MACRO(1,qep1);

// Initialize ADC module
   
    
	ilg2_vdc1.init(&ilg2_vdc1);
    
// Initialize the Speed module for QEP based speed calculation
    speed1.K1 = _IQ21(1/(BASE_FREQ*T));
    speed1.K2 = _IQ(1/(1+T*2*PI*5));  // Low-pass cut-off frequency
    speed1.K3 = _IQ(1)-speed1.K2;
    speed1.BaseRpm = 120*(BASE_FREQ/POLES);

// Initialize the RAMPGEN module
    rg1.StepAngleMax = _IQ(BASE_FREQ*T); 

// Initialize the PI module for Id
    pi_spd.Kp=_IQ(1.0);
	pi_spd.Ki=_IQ(T*speed_loop_ps/0.2);
	pi_spd.Umax =_IQ(0.95);
	pi_spd.Umin =_IQ(-0.95);
	
// Initialize the PI module for Iq	
	pi_id.Kp=_IQ(1.0);
	pi_id.Ki=_IQ(T/0.04);
	pi_id.Umax =_IQ(0.3);
	pi_id.Umin =_IQ(-0.3);
	
// Initialize the PI module for speed
	pi_iq.Kp=_IQ(1.0);
	pi_iq.Ki=_IQ(T/0.04);
	pi_iq.Umax =_IQ(0.8);
	pi_iq.Umin =_IQ(-0.8);

// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;	// Enable Global realtime interrupt DBGM

// IDLE loop. Just sit and loop forever:	
	for(;;) BackTicker++;

} 	

interrupt void PWM_ISR(void)
{
//	float A;
// Verifying the ISR
    IsrTicker++;

/* ***************** LEVEL1 ***************** */
#if (BUILDLEVEL==LEVEL1)	 

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
    rc1.TargetValue = speed_ref;		
	RC_MACRO(rc1)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
    rg1.Freq = rc1.SetpointValue;
	RG_MACRO(rg1)

// ------------------------------------------------------------------------------
//  Connect inputs of the INV_PARK module and call the inverse park trans. macro
//	There are two option for trigonometric functions:
//  IQ sin/cos look-up table provides 512 discrete sin and cos points in Q30 format
//  IQsin/cos PU functions interpolate the data in the lookup table yielding higher resolution. 
// ------------------------------------------------------------------------------
    ipark1.Ds = Vd_testing;
    ipark1.Qs = Vq_testing;
    
	//ipark1.Sine  =_IQ30toIQ(IQsinTable[_IQtoIQ9(rg1.Out)]);
    //ipark1.Cosine=_IQ30toIQ(IQcosTable[_IQtoIQ9(rg1.Out)]);

	ipark1.Sine=_IQsinPU(rg1.Out);
    ipark1.Cosine=_IQcosPU(rg1.Out);
	IPARK_MACRO(ipark1)

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
  	svgen1.Ualpha = ipark1.Alpha;
 	svgen1.Ubeta = ipark1.Beta;	
	SVGENDQ_MACRO(svgen1)

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
    pwm1.MfuncC1 = svgen1.Ta;  
    pwm1.MfuncC2 = svgen1.Tb;   
    pwm1.MfuncC3 = svgen1.Tc; 
	PWM_MACRO(1,2,3,pwm1);							// Calculate the new PWM compare values	

// ------------------------------------------------------------------------------
//    Connect inputs of the PWMDAC module 
// ------------------------------------------------------------------------------	
	pwmdac1.MfuncC1 = svgen1.Tc; 
    pwmdac1.MfuncC2 = svgen1.Tb-svgen1.Tc; 
    PWMDAC_MACRO(6,pwmdac1);
    
// ------------------------------------------------------------------------------
//    Connect inputs of the DATALOG module 
// ------------------------------------------------------------------------------
    DlogCh1 = (int16)_IQtoIQ15(svgen1.Ta);
    DlogCh2 = (int16)_IQtoIQ15(svgen1.Tb);
    DlogCh3 = (int16)_IQtoIQ15(svgen1.Tc);
    DlogCh4 = (int16)_IQtoIQ15(svgen1.Tb-svgen1.Tc);
//    B = _IQtoIQ15(svgen1.Tb-svgen1.Tc);
  
    
/*    if(IsrTicker==100)
    {
    	   	
    	A=_IQ15toF(B);
    	IsrTicker=0;
    	Next=DutyReadData_x+i; 
    	i++;   	
    	memcpy(Next,&A,2);    	
    	
    }
*/    

#endif // (BUILDLEVEL==LEVEL1)

/* ***************** LEVEL2 ***************** */
#if (BUILDLEVEL==LEVEL2)

	rc1.TargetValue = speed_ref;		
	RC_MACRO(rc1)
	
	rg1.Freq = rc1.SetpointValue;
	RG_MACRO(rg1)
	
	ipark1.Ds = Vd_testing;
    ipark1.Qs = Vq_testing;	
	ipark1.Sine=_IQsinPU(rg1.Out);
    ipark1.Cosine=_IQcosPU(rg1.Out);
	IPARK_MACRO(ipark1)
	
	svgen1.Ualpha = ipark1.Alpha;
 	svgen1.Ubeta  = ipark1.Beta;	
	SVGENDQ_MACRO(svgen1) 
	
	pwm1.MfuncC1 = svgen1.Ta;  
    pwm1.MfuncC2 = svgen1.Tb;   
    pwm1.MfuncC3 = svgen1.Tc; 
	PWM_MACRO(1,2,3,pwm1);
	
	pwmdac1.MfuncC1 = clarke1.As; 
    pwmdac1.MfuncC2 = clarke1.Bs; 
    PWMDAC_MACRO(6,pwmdac1)
    
	ilg2_vdc1.read(&ilg2_vdc1);
	
	clarke1.As = _IQ15toIQ((long)ilg2_vdc1.ImeasA);
	clarke1.Bs = _IQ15toIQ((long)ilg2_vdc1.ImeasB);
	CLARKE_MACRO(clarke1)
		
	park1.Alpha = clarke1.Alpha;
	park1.Beta = clarke1.Beta;
	park1.Angle = rg1.Out;
	park1.Sine = _IQsinPU(park1.Angle);
	park1.Cosine = _IQcosPU(park1.Angle);
	PARK_MACRO(park1)
		
//	speed_ref_rpm = (int)(speed1.rpm_max*speed_ref);
		
	/* select which of the variables are behing displayed trough data LOG */
	
	DlogCh1 = (int)_IQtoIQ15(rg1.Out);
	DlogCh2 = (int)_IQtoIQ15(svgen1.Ta);
	DlogCh3 = (int)(ilg2_vdc1.ImeasA);
	DlogCh4 = (int)(ilg2_vdc1.ImeasB);


#endif /* (BUILDLEVEL==LEVEL2) */

/* ***************** LEVEL3 ***************** */
#if (BUILDLEVEL==LEVEL3)

	rc1.target_value = _IQ(speed_ref);
	rc1.calc(&rc1);
	
	rg1.rmp_freq = rc1.setpt_value;
	rg1.calc(&rg1);
	
	pid1_iq.pid_ref_reg3 = _IQ(Iq_ref);
	pid1_iq.pid_fdb_reg3 = park1.qe;
	pid1_iq.calc(&pid1_iq);
	
	pid1_id.pid_ref_reg3 = _IQ(Id_ref);
	pid1_id.pid_fdb_reg3 = park1.de;
	pid1_id.calc(&pid1_id);
	
	ipark1.de = pid1_id.pid_out_reg3;
	ipark1.qe = pid1_iq.pid_out_reg3;	
	ipark1.ang = rg1.rmp_out;
	ipark1.calc(&ipark1);
	
	svgen_dq1.Ualfa = ipark1.ds;
	svgen_dq1.Ubeta = ipark1.qs;
	svgen_dq1.calc(&svgen_dq1);	
	
	pwm1.Mfunc_c1 = (int)_IQtoIQ15(svgen_dq1.Ta); /* Mfunc_c1 is in Q15 */
	pwm1.Mfunc_c2 = (int)_IQtoIQ15(svgen_dq1.Tb); /* Mfunc_c2 is in Q15 */  
	pwm1.Mfunc_c3 = (int)_IQtoIQ15(svgen_dq1.Tc); /* Mfunc_c3 is in Q15 */
	pwm1.update(&pwm1);
	
	ilg2_vdc1.read(&ilg2_vdc1);
	
	clarke1.as = _IQ15toIQ((long)ilg2_vdc1.ImeasA);
	clarke1.bs = _IQ15toIQ((long)ilg2_vdc1.ImeasB);
	clarke1.calc(&clarke1);

	park1.ds = clarke1.ds;
	park1.qs = clarke1.qs;
	park1.ang = rg1.rmp_out;
	park1.calc(&park1);
 
	speed_ref_rpm = (int)(speed1.rpm_max*speed_ref);
	
	/* select which of the variables are behing displayed trough data LOG */
	
	DlogCh1 = (int)_IQtoIQ15(rg1.rmp_out);
	DlogCh2 = (int)_IQtoIQ15(svgen_dq1.Ta);
	DlogCh3 = (int)(ilg2_vdc1.ImeasA);
	DlogCh4 = (int)(ilg2_vdc1.ImeasB);

#endif /* (BUILDLEVEL==LEVEL3) */


/* ***************** LEVEL4 ***************** */
#if (BUILDLEVEL==LEVEL4)

	rc1.target_value = _IQ(speed_ref);
	rc1.calc(&rc1);
	
	rg1.rmp_freq = rc1.setpt_value;
	rg1.calc(&rg1);
	
	pid1_iq.pid_ref_reg3 = _IQ(Iq_ref);
	pid1_iq.pid_fdb_reg3 = park1.qe;
	pid1_iq.calc(&pid1_iq);
	
	pid1_id.pid_ref_reg3 = _IQ(Id_ref);
	pid1_id.pid_fdb_reg3 = park1.de;
	pid1_id.calc(&pid1_id);
	
/*-----------------------------------------------------------------------------
Checking lockrtr_flg=FALSE for spinning mode, lockrtr_flg=TRUE for locked rotor mode 
-----------------------------------------------------------------------------*/
	if(lock_rotor_falg==1) {
		ipark1.de = pid1_id.pid_out_reg3;
		ipark1.qe = pid1_iq.pid_out_reg3;	
		ipark1.ang = 0;
		ipark1.calc(&ipark1);
		
		svgen_dq1.Ualfa = ipark1.ds;
		svgen_dq1.Ubeta = ipark1.qs;
		svgen_dq1.calc(&svgen_dq1);	
		
		pwm1.Mfunc_c1 = (int)_IQtoIQ15(svgen_dq1.Ta); /* Mfunc_c1 is in Q15 */
		pwm1.Mfunc_c2 = (int)_IQtoIQ15(svgen_dq1.Tb); /* Mfunc_c2 is in Q15 */  
		pwm1.Mfunc_c3 = (int)_IQtoIQ15(svgen_dq1.Tc); /* Mfunc_c3 is in Q15 */
		pwm1.update(&pwm1);
		
		ilg2_vdc1.read(&ilg2_vdc_vcon1);
		
		clarke1.as = _IQ15toIQ((long)ilg2_vdc_vcon1.Imeas_a);
		clarke1.bs = _IQ15toIQ((long)ilg2_vdc_vcon1.Imeas_b);
		clarke1.calc(&clarke1);
		
		park1.ds = clarke1.ds;
		park1.qs = clarke1.qs;
		park1.ang = 0;
		park1.calc(&park1);

	} else if(lock_rotor_flag==0)	{

		ipark1.de = pid1_id.pid_out_reg3;
		ipark1.qe = pid1_iq.pid_out_reg3;	
		ipark1.ang = rg1.rmp_out;
		ipark1.calc(&ipark1);
		
		svgen_dq1.Ualfa = ipark1.ds;
		svgen_dq1.Ubeta = ipark1.qs;
		svgen_dq1.calc(&svgen_dq1);	
		
		pwm1.Mfunc_c1 = (int)_IQtoIQ15(svgen_dq1.Ta); /* Mfunc_c1 is in Q15 */
		pwm1.Mfunc_c2 = (int)_IQtoIQ15(svgen_dq1.Tb); /* Mfunc_c2 is in Q15 */  
		pwm1.Mfunc_c3 = (int)_IQtoIQ15(svgen_dq1.Tc); /* Mfunc_c3 is in Q15 */
		pwm1.update(&pwm1);
		
		ilg2_vdc1.read(&ilg2_vdc1);
		
		clarke1.as = _IQ15toIQ((long)ilg2_vdc1.ImeasA);
		clarke1.bs = _IQ15toIQ((long)ilg2_vdc1.ImeasB);
		clarke1.calc(&clarke1);
		
		park1.ds = clarke1.ds;
		park1.qs = clarke1.qs;
		park1.ang = rg1.rmp_out;
		park1.calc(&park1);
	
	} 
	
	qep1.calc(&qep1);
	
	speed1.theta_elec = _IQ15toIQ((long)qep1.theta_elec);
	speed1.dir_QEP = (long)(qep1.dir_QEP);
	speed1.calc(&speed1);
	
	speed_ref_rpm = (int)(speed1.rpm_max*speed_ref);
	
/* select which of the variables are behing displayed trough data LOG */
	DlogCh1 = (int)_IQtoIQ15(rg1.rmp_out);
	DlogCh2 = (int)_IQtoIQ15(speed1.theta_elec);
	DlogCh3 = 0;
	DlogCh4 = 0;

#endif /* (BUILDLEVEL==LEVEL4) */


/* ***************** LEVEL5 ***************** */
#if (BUILDLEVEL==LEVEL5)

	if (speed_loop_count==speed_loop_ps) {   
	/* use R66 (Vcontrol) on DMC550 for adjusting speed reference */
		pid1_spd.pid_ref_reg3 = _IQ15toIQ((long)ilg2_vdc1.Vcontrol);
		pid1_spd.pid_fdb_reg3 = speed1.speed_frq;
		pid1_spd.calc(&pid1_spd);
		speed_loop_count=1;
	} else speed_loop_count++; 
	
	pid1_iq.pid_ref_reg3 = pid1_spd.pid_out_reg3;
	pid1_iq.pid_fdb_reg3 = park1.qe;
	pid1_iq.calc(&pid1_iq);
	
	pid1_id.pid_ref_reg3 = _IQ(Id_ref);
	pid1_id.pid_fdb_reg3 = park1.de;
	pid1_id.calc(&pid1_id);
	
	ipark1.de = pid1_id.pid_out_reg3;
	ipark1.qe = pid1_iq.pid_out_reg3;	
	ipark1.ang = speed1.theta_elec;
	ipark1.calc(&ipark1);
	
	svgen_dq1.Ualfa = ipark1.ds;
	svgen_dq1.Ubeta = ipark1.qs;
	svgen_dq1.calc(&svgen_dq1);	
	
	pwm1.Mfunc_c1 = (int)_IQtoIQ15(svgen_dq1.Ta); /* Mfunc_c1 is in Q15 */
	pwm1.Mfunc_c2 = (int)_IQtoIQ15(svgen_dq1.Tb); /* Mfunc_c2 is in Q15 */  
	pwm1.Mfunc_c3 = (int)_IQtoIQ15(svgen_dq1.Tc); /* Mfunc_c3 is in Q15 */
	pwm1.update(&pwm1);
	
	ilg2_vdc1.read(&ilg2_vdc1);
	
	clarke1.as = _IQ15toIQ((long)ilg2_vdc1.ImeasA);
	clarke1.bs = _IQ15toIQ((long)ilg2_vdc1.ImeasB);
	clarke1.calc(&clarke1);
		
	park1.ds = clarke1.ds;
	park1.qs = clarke1.qs;
	park1.ang = speed1.theta_elec;
	park1.calc(&park1);
		
	qep1.calc(&qep1);
		
	speed1.theta_elec = _IQ15toIQ((long)qep1.theta_elec);
	speed1.dir_QEP = (long)(qep1.dir_QEP);
	speed1.calc(&speed1);
		
	speed_ref = _IQ15toF((long)ilg2_vdc1.Vcontrol); 
	speed_ref_rpm = (int)(speed1.rpm_max*speed_ref);
	
	/* select which of the variables are behing displayed trough data LOG */
	DlogCh1 = (int)_IQtoIQ15(svgen_dq1.Ta);    
	DlogCh2 = (int)_IQtoIQ15(speed1.theta_elec);
	DlogCh3 = (int)(ilg2_vdc1.ImeasA);
	DlogCh4 = (int)(ilg2_vdc1.ImeasB);

#endif /* (BUILDLEVEL==LEVEL5) */

// ------------------------------------------------------------------------------
//    Call the DATALOG update function.
// ------------------------------------------------------------------------------
    dlog.update(&dlog);

// Enable more interrupts from this timer
	EPwm1Regs.ETCLR.bit.INT = 1;

// Acknowledge interrupt to recieve more interrupts from PIE group 3
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

void interrupt spiRxIsr(void)
{
	Uint16 i;
    for(i=0;i<8;i++)
    {
	    ReceData[i]=SpiaRegs.SPIRXBUF;		// Read data
	}
	
	SpiaRegs.SPIFFRX.bit.RXFFOVFCLR=1;  // Clear Overflow flag
	SpiaRegs.SPIFFRX.bit.RXFFINTCLR=1; 	// Clear Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x20;       // Issue PIE ack
}

void interrupt spiTxIsr(void)
{
	Uint16 i;
    for(i=0;i<8;i++)
    {
 	   SpiaRegs.SPITXBUF=SendData[i];      // Send data
    }

    for(i=0;i<8;i++)                    // Increment data for next cycle
    {
 	   SendData[i]++;
    }
    SpiaRegs.SPIFFTX.bit.TXFFINTCLR=1;  // Clear Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x20;  		// Issue PIE ACK
}

void spi_fifo_init()
{
// Initialize SPI FIFO registers
   SpiaRegs.SPICCR.bit.SPISWRESET=0; // Reset SPI

   SpiaRegs.SPICCR.all=0x001F;       //16-bit character, Loopback mode?
   SpiaRegs.SPICTL.all=0x0017;       //Interrupt enabled, Master/Slave XMIT enabled
   SpiaRegs.SPISTS.all=0x0000;
   SpiaRegs.SPIBRR=0x0063;           // Baud rate 0.375M
   SpiaRegs.SPIFFTX.all=0xC028;      // Enable FIFO's, set TX FIFO level to 8
   SpiaRegs.SPIFFRX.all=0x0028;      // Set RX FIFO level to 8
   SpiaRegs.SPIFFCT.all=0x00;
   SpiaRegs.SPIPRI.all=0x0010;

   SpiaRegs.SPICCR.bit.SPISWRESET=1;  // Enable SPI

   SpiaRegs.SPIFFTX.bit.TXFIFO=1;
   SpiaRegs.SPIFFRX.bit.RXFIFORESET=1;
}
void DeviceInit(void)
{
	WDogDisable(); 	// Disable the watchdog initially
	DINT;			// Global Disable all Interrupts
	IER = 0x0000;	// Disable CPU interrupts
	IFR = 0x0000;	// Clear all CPU interrupt flags



	InitPll(DSP28_PLLCR,DSP28_DIVSEL);	// choose from options above

// Initialise interrupt controller and Vector Table
// to defaults for now. Application ISR mapping done later.
	PieCntlInit();		
	PieVectTableInit();

   EALLOW; // below registers are "protected", allow access.

// LOW SPEED CLOCKS prescale register settings
   SysCtrlRegs.LOSPCP.all = 0x0002;		// Sysclk / 4 (37.5 MHz)
//   SysCtrlRegs.XCLK.bit.XCLKOUTDIV=2;
   SysCtrlRegs.HISPCP.all = 0x0001;//m 75 MHz
   // XCLKOUT to SYSCLKOUT ratio.  By default XCLKOUT = 1/4 SYSCLKOUT
   // XTIMCLK = SYSCLKOUT/2
   XintfRegs.XINTCNF2.bit.XTIMCLK = 1;
   // XCLKOUT = XTIMCLK/2
   XintfRegs.XINTCNF2.bit.CLKMODE = 1;
   // Enable XCLKOUT
   XintfRegs.XINTCNF2.bit.CLKOFF = 0;
      
      
   SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
   
   //------------------------------------------------

   SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;     // XTIMCLK
   SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;    // GPIO input clock

   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;	//eCAP1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.ECANAENCLK=0;   // eCAN-A
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;  // eQEP1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
   SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM2
   SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;  // ePWM3
   SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 1;  // ePWM4
   SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 1;	// ePWM5
   SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 1;	// ePWM6
//   SysCtrlRegs.PCLKCR1.bit.EPWM7ENCLK = 1;	// ePWM7
//   SysCtrlRegs.PCLKCR0.bit.HRPWMENCLK = 0;    // HRPWM

   
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 0;   // I2C
   //------------------------------------------------
//   SysCtrlRegs.PCLKCR0.bit.LINAENCLK = 0;   // LIN-A
   //------------------------------------------------
//   SysCtrlRegs.PCLKCR3.bit.CLA1ENCLK = 0;   // CLA1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;  	// SCI-A
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 0;	// SPI-A
//   SysCtrlRegs.PCLKCR0.bit.SPIBENCLK = 0;     // SPI-B
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Enable TBCLK
   //------------------------------------------------           

 
//  GPIO-00 - PIN FUNCTION = PWM1A
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;		// 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
//	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO0 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-01 - PIN FUNCTION = PWM1B
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;		// 0=GPIO,  1=EPWM1B,  2=Resv,  3=COMP1OUT
//	GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO1 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-02 - PIN FUNCTION = PWM2A
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;		// 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
//	GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO2 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-03 - PIN FUNCTION = PWM2B
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;		// 0=GPIO,  1=EPWM2B,  2=SPISOMI-A,  3=COMP2OUT
//	GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO3 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-04 - PIN FUNCTION = PWM3A
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;		// 0=GPIO,  1=EPWM3A,  2=Resv,  3=Resv
//	GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO4 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-05 - PIN FUNCTION = PWM3B
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;		// 0=GPIO,  1=EPWM3B,  2=SPISIMO-A,  3=ECAP1
//	GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO5 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-06 - PIN FUNCTION = PWM4A
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;		// 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
//	GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO6 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-07 - PIN FUNCTION = PWM4B
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;		// 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=Resv
//	GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO7 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-08 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;		// 0=GPIO,  1=EPWM5A,  2=Resv,  3=ADCSOC-A
//	GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO8 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-09 - PIN FUNCTION = Clear Fault
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;		// 0=GPIO,  1=EPWM5B,  2=LINTX-A,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;	// uncomment if --> Set Low initially
	GpioDataRegs.GPASET.bit.GPIO9 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-10 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;	// 0=GPIO,  1=EPWM6A,  2=Resv,  3=ADCSOC-B
//	GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO10 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-11 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;	// 0=GPIO,  1=EPWM6B,  2=LINRX-A,  3=Resv
//	GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO11 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-12 - PIN FUNCTION = TZ1
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;	// 0=GPIO,  1=TZ1,  2=SCITX-A,  3=SPISIMO-B
//	GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO12 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-13 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;	// 0=GPIO,  1=TZ2,  2=Resv,  3=SPISOMI-B
	GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO13 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-14 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;	// 0=GPIO,  1=TZ3,  2=LINTX-A,  3=SPICLK-B
	GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO14 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-15 - PIN FUNCTION = OCP
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;	// 0=GPIO,  1=TZ1,  2=LINRX-A,  3=SPISTE-B
	GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO15 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//  GPIO-16 - PIN FUNCTION = SPISIMO-A
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;	// 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
//	GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO16 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-17 - PIN FUNCTION = SPISOMI-A
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;	// 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ3
//	GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO17 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-18 - PIN FUNCTION = SPICLK-A
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;	// 0=GPIO,  1=SPICLK-A,  2=LINTX-A,  3=XCLKOUT
//	GpioCtrlRegs.GPADIR.bit.GPIO18 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO18 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-19 - PIN FUNCTION = SPISTE-A
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;	// 0=GPIO,  1=SPISTE-A,  2=LINRX-A,  3=ECAP1
//	GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO19 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-20 - PIN FUNCTION = EQEPA-1
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;	// 0=GPIO,  1=EQEPA-1,  2=Resv,  3=COMP1OUT
//	GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO20 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-21 - PIN FUNCTION = EQEPB-1
	GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;	// 0=GPIO,  1=EQEPB-1,  2=Resv,  3=COMP2OUT
//	GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO21 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-22 - PIN FUNCTION = GPIO
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;	// 0=GPIO,  1=EQEPS-1,  2=Resv,  3=LINTX-A
	GpioCtrlRegs.GPADIR.bit.GPIO22 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO22 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-23 - PIN FUNCTION = EQEPI-1
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;	// 0=GPIO,  1=EQEPI-1,  2=Resv,  3=LINRX-A
//	GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO23 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-24 - PIN FUNCTION = ECAP1
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;	// 0=GPIO,  1=ECAP1,  2=Resv,  3=SPISIMO-B
	GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO24 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-25 - PIN FUNCTION = GPIO
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;	// 0=GPIO,  1=Resv,  2=Resv,  3=SPISOMI-B
	GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO25 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-26 - PIN FUNCTION = GPIO
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;	// 0=GPIO,  1=Resv,  2=Resv,  3=SPICLK-B
	GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO26 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-27 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;	// 0=GPIO,  1=Resv,  2=Resv,  3=SPISTE-B
	GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO27 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-28 - PIN FUNCTION = SCI-RX
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;	// 0=GPIO,  1=SCIRX-A,  2=I2CSDA-A,  3=TZ2
//	GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO28 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-29 - PIN FUNCTION = SCI-TX
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;	// 0=GPIO,  1=SCITXD-A,  2=I2CSCL-A,  3=TZ3
//	GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO29 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-30 - PIN FUNCTION = CANRX-A
	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0;	// 0=GPIO,  1=CANRX-A,  2=Resv,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO30 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-31 - PIN FUNCTION = CANTX-A
	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;	// 0=GPIO,  1=CANTX-A,  2=Resv,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO31 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//  GPIO-32 - PIN FUNCTION = I2CSDA-A
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;	// 0=GPIO,  1=I2CSDA-A,  2=SYNCI,  3=ADCSOCA
//	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO32 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-33 - PIN FUNCTION = I2CSCL-A
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;	// 0=GPIO,  1=I2CSCL-A,  2=SYNCO,  3=ADCSOCB
//	GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO33 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-34 - PIN FUNCTION = LED3 on controlCARD
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;	// 0=GPIO,  1=Resv,  2=Resv,  3=Resv
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;		// 1=OUTput,  0=INput 
	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO34 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// GPIO 35-38 are defaulted to JTAG usage, and are not shown here to enforce JTAG debug
// usage. 
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//  GPIO-39 - PIN FUNCTION = GPIO
	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;	// 0=GPIO,  1=Resv,  2=Resv,  3=Resv
	GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO39 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-40 - PIN FUNCTION = EPWM7A
//	GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 1;	// 0=GPIO,  1=EPWM7A,  2=Resv,  3=Resv
//	GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO40 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-41 - PIN FUNCTION = EPWM7B
//	GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 1;	// 0=GPIO,  1=EPWM7B,  2=Resv,  3=Resv
//	GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO41 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-42 - PIN FUNCTION = LED2
	GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0;	// 0=GPIO,  1=Resv,  2=Resv,  3=COMP1OUT
	GpioCtrlRegs.GPBDIR.bit.GPIO42 = 1;		// 1=OUTput,  0=INput 
	GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO42 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-43 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;	// 0=GPIO,  1=Resv,  2=Resv,  3=COMP2OUT
	GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;		// 1=OUTput,  0=INput 
//	GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO43 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//  GPIO-44 - PIN FUNCTION = LED1
	GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;	// 0=GPIO,  1=Resv,  2=Resv,  3=Resv
	GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1;		// 1=OUTput,  0=INput 
	GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO44 = 1;		// uncomment if --> Set High initially
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
	EDIS;	// Disable register access
}

//============================================================================
// NOTE:
// IN MOST APPLICATIONS THE FUNCTIONS AFTER THIS POINT CAN BE LEFT UNCHANGED
// THE USER NEED NOT REALLY UNDERSTAND THE BELOW CODE TO SUCCESSFULLY RUN THIS
// APPLICATION.
//============================================================================

void WDogDisable(void)
{
    EALLOW;
    SysCtrlRegs.WDCR= 0x0068;
    EDIS;
}

// This function initializes the PLLCR register.
//void InitPll(Uint16 val, Uint16 clkindiv)
void InitPll(Uint16 val, Uint16 divsel)
{

   // Make sure the PLL is not running in limp mode
   if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)
   {
      // Missing external clock has been detected
      // Replace this line with a call to an appropriate
      // SystemShutdown(); function.
      asm("        ESTOP0");
   }

   // DIVSEL MUST be 0 before PLLCR can be changed from
   // 0x0000. It is set to 0 by an external reset XRSn
   // This puts us in 1/4
   if (SysCtrlRegs.PLLSTS.bit.DIVSEL != 0)
   {
       EALLOW;
       SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
       EDIS;
   }

   // Change the PLLCR
   if (SysCtrlRegs.PLLCR.bit.DIV != val)
   {

      EALLOW;
      // Before setting PLLCR turn off missing clock detect logic
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
      SysCtrlRegs.PLLCR.bit.DIV = val;
      EDIS;

      // Optional: Wait for PLL to lock.
      // During this time the CPU will switch to OSCCLK/2 until
      // the PLL is stable.  Once the PLL is stable the CPU will
      // switch to the new PLL value.
      //
      // This time-to-lock is monitored by a PLL lock counter.
      //
      // Code is not required to sit and wait for the PLL to lock.
      // However, if the code does anything that is timing critical,
      // and requires the correct clock be locked, then it is best to
      // wait until this switching has completed.

      // Wait for the PLL lock bit to be set.

      // The watchdog should be disabled before this loop, or fed within
      // the loop via ServiceDog().

	  // Uncomment to disable the watchdog
      WDogDisable();

      while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)
      {
	      // Uncomment to service the watchdog
          // ServiceDog();
      }

      EALLOW;
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
      EDIS;
    }

    // If switching to 1/2
	if((divsel == 1)||(divsel == 2))
	{
		EALLOW;
	    SysCtrlRegs.PLLSTS.bit.DIVSEL = divsel;
	    EDIS;
	}


	// NOTE: ONLY USE THIS SETTING IF PLL IS BYPASSED (I.E. PLLCR = 0) OR OFF
	// If switching to 1/1
	// * First go to 1/2 and let the power settle
	//   The time required will depend on the system, this is only an example
	// * Then switch to 1/1
	if(divsel == 3)
	{
		EALLOW;
	    SysCtrlRegs.PLLSTS.bit.DIVSEL = 2;
	    DELAY_US(50L);
	    SysCtrlRegs.PLLSTS.bit.DIVSEL = 3;
	    EDIS;
    }
}


// This function initializes the PIE control registers to a known state.
//
void PieCntlInit(void)
{
    // Disable Interrupts at the CPU level:
    DINT;

    // Disable the PIE
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

	// Clear all PIEIER registers:
	PieCtrlRegs.PIEIER1.all = 0;
	PieCtrlRegs.PIEIER2.all = 0;
	PieCtrlRegs.PIEIER3.all = 0;	
	PieCtrlRegs.PIEIER4.all = 0;
	PieCtrlRegs.PIEIER5.all = 0;
	PieCtrlRegs.PIEIER6.all = 0;
	PieCtrlRegs.PIEIER7.all = 0;
	PieCtrlRegs.PIEIER8.all = 0;
	PieCtrlRegs.PIEIER9.all = 0;
	PieCtrlRegs.PIEIER10.all = 0;
	PieCtrlRegs.PIEIER11.all = 0;
	PieCtrlRegs.PIEIER12.all = 0;

	// Clear all PIEIFR registers:
	PieCtrlRegs.PIEIFR1.all = 0;
	PieCtrlRegs.PIEIFR2.all = 0;
	PieCtrlRegs.PIEIFR3.all = 0;	
	PieCtrlRegs.PIEIFR4.all = 0;
	PieCtrlRegs.PIEIFR5.all = 0;
	PieCtrlRegs.PIEIFR6.all = 0;
	PieCtrlRegs.PIEIFR7.all = 0;
	PieCtrlRegs.PIEIFR8.all = 0;
	PieCtrlRegs.PIEIFR9.all = 0;
	PieCtrlRegs.PIEIFR10.all = 0;
	PieCtrlRegs.PIEIFR11.all = 0;
	PieCtrlRegs.PIEIFR12.all = 0;
}	


void PieVectTableInit(void)
{

   	int16	i;
	Uint32 *Source = (void *) &PieVectTableInit;
	Uint32 *Dest = (void *) &PieVectTable;
		
	EALLOW;	
	for(i=0; i < 128; i++)
		*Dest++ = *Source++;	
	EDIS;

	// Enable the PIE Vector Table
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;	
		
}

interrupt void ISR_ILLEGAL(void)   // Illegal operation TRAP
{
  // Insert ISR Code here

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm("          ESTOP0");
  for(;;);

}

// This function initializes the Flash Control registers

//                   CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results

void InitFlash(void)
{
   EALLOW;
   //Enable Flash Pipeline mode to improve performance
   //of code executed from Flash.
   FlashRegs.FOPT.bit.ENPIPE = 1;

   //                CAUTION
   //Minimum waitstates required for the flash operating
   //at a given CPU rate must be characterized by TI.
   //Refer to the datasheet for the latest information.

   //Set the Paged Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 5;

   //Set the Random Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 5;

   //Set the Waitstate for the OTP
   FlashRegs.FOTPWAIT.bit.OTPWAIT = 8;

   //                CAUTION
   //ONLY THE DEFAULT VALUE FOR THESE 2 REGISTERS SHOULD BE USED
   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
   EDIS;

   //Force a pipeline flush to ensure that the write to
   //the last register configured occurs before returning.

   asm(" RPT #7 || NOP");
}


void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    { 
       *DestAddr++ = *SourceAddr++;
    }
    return;
}

