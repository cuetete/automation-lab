// DESCRIPTION:
//
//		Key 
//		Press K1-K6, Observing the change of the state of LED1-6
//
//		
////###########################################################################	


#include "DSP2833x_Device.h"     // DSP2823x Headerfile Include File
#include "DSP2833x_examples.h"   // DSP2823x Examples Include File

//////////////////////////////////////////////////
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
// Setup only the GP I/O only for SPI-A functionality
// This function is found in DSP2833x_Spi.c
//   InitXintf();
 //  InitSpiaGpio();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts 
   DINT;

// Initialize PIE control registers to their default state.
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
   EALLOW;
   //LED I/Os all output 
   GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;
   //set LED8 LED9 OFF
   GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;
   GpioDataRegs.GPASET.bit.GPIO8 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;
   GpioDataRegs.GPASET.bit.GPIO9 = 1;
   //LED CS	
   GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;   									// Enable pullup on GPIO27
   GpioDataRegs.GPASET.bit.GPIO27 = 1;   									// Load output latch
   GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;  									// GPIO27 = GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;   									// GPIO27 = output  
   GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;									// LED_CS=0,enable LEDs

   EDIS;
   
   EALLOW;
   // KEY I/Os all input
   GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;          // input
   GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;          // input
   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;          // input
   GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;          // input
   GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;          // input
   GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;          // input

   EDIS;
////////////////////////////////////////////////
  while (1)
  {
  	if (GpioDataRegs.GPADAT.bit.GPIO12==0) GpioDataRegs.GPADAT.bit.GPIO4=0;		//KEY3-LED3
   	else GpioDataRegs.GPADAT.bit.GPIO4=1;

  	if (GpioDataRegs.GPADAT.bit.GPIO13==0) GpioDataRegs.GPADAT.bit.GPIO5=0;		//KEY4-LED4
   	else GpioDataRegs.GPADAT.bit.GPIO5=1;
   	
  	if (GpioDataRegs.GPADAT.bit.GPIO14==0) GpioDataRegs.GPADAT.bit.GPIO6=0;		//KEY5-LED5
   	else  GpioDataRegs.GPADAT.bit.GPIO6=1;

  	if (GpioDataRegs.GPADAT.bit.GPIO15==0) GpioDataRegs.GPADAT.bit.GPIO7=0;		//KEY6-LED6
   	else GpioDataRegs.GPADAT.bit.GPIO7=1;	
   	
   	if (GpioDataRegs.GPADAT.bit.GPIO16==0) GpioDataRegs.GPADAT.bit.GPIO2=0;		//KEY2-LED2
   	else GpioDataRegs.GPADAT.bit.GPIO2=1;
   	
   	if (GpioDataRegs.GPADAT.bit.GPIO17==0) GpioDataRegs.GPADAT.bit.GPIO3=0;		//KEY1-LED1
   	else GpioDataRegs.GPADAT.bit.GPIO3=1;
  }
} 	

	
//===========================================================================
// No more.
//===========================================================================

