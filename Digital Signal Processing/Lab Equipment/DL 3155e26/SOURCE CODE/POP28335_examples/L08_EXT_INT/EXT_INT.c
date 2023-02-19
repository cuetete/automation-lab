// DESCRIPTION:
//
//		External interrupt 
//		K5--XINT1  K6--XINT2
//		Press these two keys, Observing the change of the state of LED1-4
//		
////###########################################################################	



#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_Examples.h"   // Examples Include File

// Prototype statements for functions found within this file.
interrupt void xint1_isr(void);
interrupt void xint2_isr(void);

//Global variable
volatile Uint32 Xint1Count; //times of XINT1 occured
volatile Uint32 Xint2Count; //times of XINT2 occured
volatile Uint32 Xint2Loop;  //loop variable of XINT1 occured

#define keyon1 GpioDataRegs.GPADAT.bit.GPIO14
#define keyon2 GpioDataRegs.GPADAT.bit.GPIO15

#define DELAY 35.700L

void main(void)
{
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example


// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.XINT1 = &xint1_isr;		//define EXT INT ISR
   PieVectTable.XINT2 = &xint2_isr;
   EDIS; 
	
   Xint1Count = 0; //XINT1 Count
   Xint2Count = 0; //XINT2 Count 


   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;           
   PieCtrlRegs.PIEIER1.bit.INTx4 = 1;           
   PieCtrlRegs.PIEIER1.bit.INTx5 = 1;           
   IER |= M_INT1;                              //enable INT1
   EINT;                                       //enable Global interrupt
   
   //LED1-8  I/O Initialization   set LED1-8 OFF
   EALLOW;
   GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;		//LED1
   GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;		//LED2
   GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;      //LED3
   GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;      //LED4
   GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;
   GpioDataRegs.GPADAT.all=0x000003FC;   
   
   //LED CS	
   GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;   									// Enable pullup on GPIO27
   GpioDataRegs.GPASET.bit.GPIO27 = 1;   									// Load output latch
   GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;  									// GPIO27 = GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;   									// GPIO27 = output  
   GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;									// LED_CS=0,enable LEDs     
   EDIS; 
  
   //ser KEY5,6 as external interrupt spurce
   EALLOW;
   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;   		//KEY5  
   GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;          
   GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 0;         

   GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;  		//KEY6     
   GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;           
   GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 2;         
   GpioCtrlRegs.GPACTRL.bit.QUALPRD1 = 0xFF;     
   EDIS;

   EALLOW;
   GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 0x0E;   // XINT1-GPIO14(KEY5)
   GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 0x0F;   // XINT2-GPIO15(KEY6)
   EDIS;

   XIntruptRegs.XINT1CR.bit.POLARITY = 0;      // falling edge trigging
   XIntruptRegs.XINT2CR.bit.POLARITY = 0;     
   
   XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // enable XINT1
   XIntruptRegs.XINT2CR.bit.ENABLE = 1;        // enable XINT2
   	
   for(;;);
	
} 	

//ISR
interrupt void xint1_isr(void)
{
	Uint32 i;
	for(i=0;i<1000000;i++);    // elimination of jitter
	while(keyon1==0);
	GpioDataRegs.GPATOGGLE.all = 0xC;   //// GPIO2-GPIO3(LED1,2) State withdrawal     
	Xint1Count++;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; //Clear interrupt Flags
}

interrupt void xint2_isr(void)
{
	Uint32 i;
	for(Xint2Loop=1;Xint2Loop<=8;Xint2Loop++)
	{
	  GpioDataRegs.GPATOGGLE.all = 0x30;   // GPIO4-GPIO5(LED3,4) State withdrawal
      DELAY_US(100000);  //delay 0.1s
    }

	Xint2Count++;
	for(i=0;i<1000000;i++);    // elimination of jitter
	while(keyon2==0);
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; //Clear interrupt Flags

}



//===========================================================================
// No more.
//===========================================================================



