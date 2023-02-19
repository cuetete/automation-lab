// DESCRIPTION:
//
//    This example TRANSMITS data to another E26(CANA) using wires(CANH-CANH CANL-CANL)
//	  Press K1 to send a CAN data frame
//    Check REVID and REVDATA if you recevie a CAN data frame
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include <stdio.h>

Uint32	MYID=0x155;			//local ID
Uint64  SENDATA=0x1122334455667788; //CAN data to be sent (length depend on DLC)

Uint32	REVID=0x156;		// CAN ID of another E26
Uint64  REVDATA=0;			// Received data

// This function reads out the contents of the indicated 
// by the Mailbox number (MBXnbr).
void mailboxb_read(int16 MBXnbr)
{
   volatile struct MBOX *Mailbox;
   Mailbox = &ECanaMboxes.MBOX0 + MBXnbr;
   while(ECanaRegs.CANRMP.all & (1<< MBXnbr) == 0 );   // Wait for mailbox receive panding flag to be set..
   ECanaRegs.CANRMP.all |= 1<< MBXnbr; // Clear receive panding flag
   REVDATA = Mailbox->MDL.all;  
   REVDATA <<=32;
   REVDATA |= Mailbox->MDH.all;  
   REVID = Mailbox->MSGID.all; 
   REVID >>=18;
} // MSGID of a rcv MBX is transmitted as the MDL data.

void delay_loop(Uint32 a)
{
   while(a--);
}

void main()
{

/* Create a shadow register structure for the CAN control registers. This is
 needed, since, only 32-bit access is allowed to these registers. 16-bit access
 to these registers could potentially corrupt the register contents. This is
 especially true while writing to a bit (or group of bits) among bits 16 - 31 */

   struct ECAN_REGS ECanaShadow;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example
   InitECanaGpio();

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

// No interrupts used in this example.

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
   EALLOW;
   // K1 I/O init
   GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;          // input


   EDIS;
   // In this case just initalize eCAN-A and eCAN-B
   InitECana();

// Step 5. User specific code:

/* Write to the MSGID field  */
   EALLOW;

   ECanaMboxes.MBOX25.MSGID.all = (MYID<<18); // Standard Identifier

/* Configure Mailbox under test as a Transmit mailbox Mailbox_25*/
   ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
   ECanaShadow.CANMD.bit.MD25 = 0;
   ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;

/* Enable Mailbox under test */

   ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   ECanaShadow.CANME.bit.ME25 = 1;
   ECanaRegs.CANME.all = ECanaShadow.CANME.all;

/* Write to DLC field in Master Control reg */
   ECanaMboxes.MBOX25.MSGCTRL.bit.DLC = 8;


/* Configure eCANA Mailbox_20 as a Receive mailbox */
   ECanaMboxes.MBOX20.MSGID.all = (REVID<<18); // Standard Identifier
/* Configure Mailbox under test as a Receive mailbox */
   ECanaShadow.CANMD.all = ECanbRegs.CANMD.all;
   ECanaShadow.CANMD.bit.MD20 = 1;
   ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;
/* Enable Mailbox under test */
   ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   ECanaShadow.CANME.bit.ME20 = 1;
   ECanaRegs.CANME.all = ECanaShadow.CANME.all;
   ECanaMboxes.MBOX20.MSGCTRL.bit.DLC = 8;
/* Write to DLC field in Master Control reg */
//   ECanbMboxes.MBOX25.MSGCTRL.bit.DLC = 8;

   EDIS;
/* Begin transmitting */
   while(1)
 {
 	delay_loop(5000000);
 	
 	if (GpioDataRegs.GPADAT.bit.GPIO16==0)			//Send a CAN data frame if K1 pressed
	{
	   ECanaMboxes.MBOX25.MDL.all = (Uint32)(SENDATA>>32);
       ECanaMboxes.MBOX25.MDH.all = (Uint32)SENDATA;
	   //Transmit the massage
       ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS25 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA25 == 0 );   // Wait for TA5 bit to be set..


       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA25 = 1;     	         // Clear TA5
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}
   	
 	if(ECanaRegs.CANRMP.bit.RMP20)			//Check flag whether the data has been received
 	{
		ECanaRegs.CANRMP.bit.RMP20=0;
		mailboxb_read(20); 	//read data from mailbox
	
 	}
  }
}


