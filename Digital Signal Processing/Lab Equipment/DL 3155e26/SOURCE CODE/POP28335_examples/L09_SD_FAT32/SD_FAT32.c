// DESCRIPTION:
//
//		Writing a txt file to the SD card 
//		 
//		
////###########################################################################	


#include "DSP2833x_Device.h"     // DSP2823x Headerfile Include File
#include "DSP2833x_examples.h"   // DSP2823x Examples Include File

//////////////////////////////////////
extern	void play_Udisc();

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
   InitXintf();
   InitSpiaGpio();

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
	
// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
   spi_initialization();		//Initialize SPI	
   
   sd_card_insertion();			//Check for card insertion
   sd_initialization();			//Initialize card

   sd_read_register(SEND_CSD);		//Read CSD register
   sd_read_register(READ_OCR);		//Read OCR register
   sd_read_register(SEND_CID);		//Read CID register

   play_Udisc();		//write text to SD card

   asm("     ESTOP0");  // test failed!! Stop!
   for (;;);
   
} 	


// Step 7. Insert all local Interrupt Service Routines (ISRs) and functions here:	

//===========================================================================
// No more.
//===========================================================================

