// DESCRIPTION:
//
//		Get the voltage value of the channel ADCINA0 
//		and dispaly it on four 7-segment LEDs
//		Connect DAC-V to ADC-1 first
//		Rotary knob VR, check whether the displayed voltage is in accordance with the measured voltage
////###########################################################################	


#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

void s_delay(void);
void delay_loop(void);
void spi_xmit(Uint16 a);
void spi_fifo_init(void);
void spi_init(void);
void error(void);


// ADC start parameters
#define ADC_MODCLK 0x5   // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*4)             = 15MHz
                         //    for 60 MHz devices:    HSPCLK =  60/(2*4)             = 7.5 MHz
#define ADC_CKPS   0x1   // ADC module clock = HSPCLK/2*ADC_CKPS   = 15MHz/(1*2)   = 7.5MHz
                         
#define ADC_SHCLK  0xf   // S/H width in ADC module periods                          = 16 ADC clocks
#define AVG        100  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   256  // Sample buffer size

// Global variable for this example
Uint16 SampleTable[BUF_SIZE];

void InitCS(void)
{                                         
	EALLOW;                               
	GpioCtrlRegs.GPBPUD.bit.GPIO60 = 0;   
	GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;   
	GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1; 
	EDIS; 
}

//------------------------------------------------------------------------------------
Uint16 SegData[16]=		//"0"~"F" code of common anode 7-SegmentLED
{
	0xC0,		//0
	0xF9,		//1
	0xA4,		//2
	0xB0,		//3
	0x99,		//4
	0x92,		//5
	0x82,		//6
	0xF8,		//7
	0x80,		//8
	0x90,		//9
	0x88,		//A
	0x83,		//B
	0xC6,		//C
	0xA1,		//E
	0x86,		//E
	0x8E		//F
};

void ShowChar(Uint16 s1, Uint16 s2, Uint16 s3, Uint16 s4)
{                                         
	Uint16 sdata=0;
	sdata=SegData[s1];
	sdata &=0x007F;
	sdata <<=8;
	sdata |=SegData[s2];
	spi_xmit(sdata);
	
	sdata=SegData[s3];
	sdata <<=8;
	sdata |=SegData[s4];
	spi_xmit(sdata);
	
	GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1;
	s_delay();
	GpioDataRegs.GPBSET.bit.GPIO60 = 1;
}

main()
{
   Uint16 i;
   Uint32 Sum=0;
   Uint32 Vin;
   Uint16 s1=1,s2=2,s3=3,s4=4;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP280x_SysCtrl.c file.
   InitSysCtrl();

// Specific clock setting for this example:
   EALLOW;
   SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT/£¨2*ADC_MODCLK£©=15MHZ
   EDIS;

// Step 2. Initialize GPIO:
// This example function is found in the DSP280x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

   InitCS();
   InitSpiaGpio(); 

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP280x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP280x_DefaultIsr.c.
// This function is found in DSP280x_PieVect.c.
   InitPieVectTable();

   InitAdc();  // For this example, init the ADC
   
   spi_fifo_init();	  
   spi_init();		  // init SPI

// Specific ADC setup for this example:
   AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;   //Setting the sampling window time£º£¨15+1£©*ADCCLK
   AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;  //ADC CLK£ºHSPCLK/2=6.25MHZ
   AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;         //
   AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;    //select channel: ADCAIN0
   AdcRegs.ADCTRL1.bit.CONT_RUN = 1;         //Continuous run


// Step 5.user code
   for (i=0; i<BUF_SIZE; i++)
   {
     SampleTable[i] = 0;
   }

   // Software startup SEQ1
   AdcRegs.ADCTRL2.all = 0x2000;

   //Get the ADC data and write it to buffer-SampleTable
   for(;;)
   {
     for (i=0; i<AVG; i++)
     {
        while (AdcRegs.ADCST.bit.INT_SEQ1== 0) {} // wait interrupt
        AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
        SampleTable[i] =((AdcRegs.ADCRESULT0>>4) );	
     }
	 for (i=0;i<AVG;i++)		//AVG times averaging	
	 {
      Sum+=SampleTable[i];
	  Sum=Sum/2;
	 }
	 
	 Vin=Sum*3*1000/4096;      ////voltage:Sum*3/4096, multiplied by 1000 
	 s1=Vin/1000;				//thousand
	 s2=Vin%1000/100;			//hundred
	 s3=Vin%1000%100/10;		//the
	 s4=Vin%1000%100%10;		//one
	 ShowChar(s1,s2,s3,s4);		//7-seg LEDs display
	 delay_loop();
   }
}

void s_delay(void)
{
    long      i;
    for (i = 0; i < 45000; i++) {}
}

void delay_loop()
{
    long      i;
                   for (i = 0; i < 4500000; i++) {} 
}

void error(void)
{
    asm("     ESTOP0");						// Test failed!! Stop!
    for (;;);
}

void spi_init()
{    
	SpiaRegs.SPICCR.all =0x004F;
	SpiaRegs.SPICTL.all =0x0006; 	                                                            
	SpiaRegs.SPIBRR =0x007F;	//SPI BR=25M/128	=195.3KHZ£»							
    SpiaRegs.SPICCR.all =0x00CF; 
    SpiaRegs.SPIPRI.bit.FREE = 1;  // free run
}
 
void spi_xmit(Uint16 a)
{
    SpiaRegs.SPITXBUF=a;
}    


void spi_fifo_init()										
{
    SpiaRegs.SPIFFTX.all=0xE040; 
    SpiaRegs.SPIFFRX.all=0x204f;
    SpiaRegs.SPIFFCT.all=0x0;
}  

//===========================================================================
// No more.
//===========================================================================

