#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

Uint16    *ExRamStart = (Uint16 *)0x100000;   //address of ExSRAM(IS61LV25616)

void main(void)
{
   Uint32	i;
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example
   InitXintf16Gpio(); 

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


// Step 4. Write Data to SRAM:
   
	for(i = 0; i < 0x4FFFF; i++)
	{
		*(ExRamStart + i) = 0x5555;
	}
	
	for(i = 0; i < 0x4FFFF; i++)
	{
		*(ExRamStart + i) = 0xAAAA;
	}

	for(i = 0; i< 0xFFFF; i++)
	{
		*(ExRamStart + i) = i;
		if(*(ExRamStart + i) != i)
		{
			   	asm ("      ESTOP0");//error 
		}
	}
         asm ("      ESTOP0");//ok	
}

//===========================================================================
// No more.
//===========================================================================
