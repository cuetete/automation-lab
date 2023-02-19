// DESCRIPTION:
//
//		Display characters 0-F on the four 7-segment LEDs
//		 
//		
////###########################################################################	

#include "DSP2833x_Device.h"     
#include "DSP2833x_Examples.h"   

void s_delay(void);
void delay_loop(void);
void spi_xmit(Uint16 a);
void spi_fifo_init(void);
void spi_init(void);
void error(void);

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

//------------------------------------------------------------------------------------------
void InitCS(void)		//74244 pin EN
{                                         
	EALLOW;                               
	GpioCtrlRegs.GPBPUD.bit.GPIO60 = 0;   
	GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;   
	GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1; //EN=0,enable 8 segled display
	EDIS; 
}

void ShowChar(Uint16 s1, Uint16 s2, Uint16 s3, Uint16 s4)		//s1:thousand s2:hundred s3:ten s4:one (0-F)
{                                         
	Uint16 sdata=0;
	sdata=SegData[s1];
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

void main(void)
{
   Uint16 s1=1,s2=2,s3=3,s4=4;
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
	
// Step 4. Initialize the Device Peripheral. This function can be
   InitSpiaGpio();
   spi_fifo_init();	   
   spi_init(); 
   InitCS();		
   for(;;)
   {    
	  ShowChar(s1,s2,s3,s4);
	  s1++;
	  if(s1>15) s1=1;
	  s2++;
	  if(s2>15) s2=1;
	  s3++;
	  if(s3>15) s3=1;
	  s4++;
	  if(s4>15) s4=1;
	  delay_loop();
   }
} 	



void s_delay()
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


void spi_init()  			//SPI Initialize
{    
	SpiaRegs.SPICCR.all =0x000F; // 16bit
	SpiaRegs.SPICTL.all =0x0006; // master
                                   
	SpiaRegs.SPIBRR =0x007F;	//SPI baudrate=25M/128	=195.3KHZ£»							
    SpiaRegs.SPICCR.all =0x00CF;
    SpiaRegs.SPIPRI.bit.FREE = 1;
}

void spi_xmit(Uint16 a)		//SPI sending
{
    SpiaRegs.SPITXBUF=a;
}    


void spi_fifo_init()		//SPI FIFO Initialize									
{
    SpiaRegs.SPIFFTX.all=0xE040;                                 
    SpiaRegs.SPIFFRX.all=0x204f;                            
    SpiaRegs.SPIFFCT.all=0x0; 
}  

//===========================================================================
// No more.
//===========================================================================

