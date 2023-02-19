// DESCRIPTION:
//
//		LCD1602 dispaly 
//		1st line: DE LORENZO   2nd line: DL 3155E26
//
//        RS--GPIO0 R/W--GND  EN--GPIO1  D0--GPIO2 
//        D1--GPIO3 D2--GPIO4 D3--GPIO5  D4--GPIO6 
//        D5--GPIO7 D6--GPIO8 D7--GPIO9 
//        74244EN--GPIO24
//		
////###########################################################################		

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define uchar unsigned char
#define LCD_RS GpioDataRegs.GPADAT.bit.GPIO0
#define LCD_EN GpioDataRegs.GPADAT.bit.GPIO1
#define LCD_DB GpioDataRegs.GPADAT.all

void Init_Port(void);
void LCD_init(void);                        
void LCD_write_command(uchar command);     
void LCD_write_data(uchar dat);             
void show(char *cont);                      


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

// Step 4. Initialize the Device Peripheral.
// InitPeripherals();  // Not required for this example
   Init_Port();
   LCD_init();
   
   LCD_write_command(0x80);	//1st line position:0x80
   show("   DE LORENZO   ");
               
   LCD_write_command(0xc0);	//2nd line position:0xC0
   show("   DL 3155E26   ");
   for(;;);
} 

void show(char *cont)
{
 while(*cont!=0)
 {
  LCD_write_data(*cont);
  DELAY_US(500);  
  cont++;
 }
}

void Init_Port(void)
{
   EALLOW;   
   GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;     //enable GPIO0 PULLUP
   GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;     //disable GPIO1 PULLUP
   GpioCtrlRegs.GPAMUX1.all = 0;   		  //set GPIO0-GPIO15 as GPIO
   GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;   // set GPIO24 as GPIO
   GpioCtrlRegs.GPADIR.all = 0x10003FF;	  //set GPIO0-GPIO9 and GPIO24 as output
   GpioCtrlRegs.GPAQSEL1.all = 0x0000;  	
   GpioCtrlRegs.GPAQSEL2.all = 0x0000;    	
   GpioDataRegs.GPADAT.bit.GPIO0 = 1;	//set GPIO0 High
   GpioDataRegs.GPADAT.bit.GPIO1 = 0;	//set GPIO1 Low
   GpioDataRegs.GPADAT.bit.GPIO24 = 0;  	//74244 EN=0
   EDIS;
} 

void LCD_write_command(uchar command)
{
LCD_EN=0;
LCD_RS=0;         
LCD_DB=(command<<2)|0x0000;
DELAY_US(500); 
LCD_EN=1;
DELAY_US(1000);
LCD_EN=0;

}

void LCD_write_data(uchar dat)
{
LCD_EN=0;
LCD_RS=1;         
LCD_DB=(dat<<2)|0x0001;
DELAY_US(500); 
LCD_EN=1; 
DELAY_US(1000);
LCD_EN=0;
}

void LCD_init(void)
{
DELAY_US(15000);
LCD_write_command(0x38);
DELAY_US(5000);
LCD_write_command(0x38);
DELAY_US(5000);
LCD_write_command(0x38);//set two lines
LCD_write_command(0x38);
LCD_write_command(0x08);//diaplay off
LCD_write_command(0x01);//clear
LCD_write_command(0x06);//set mode 
LCD_write_command(0x0c);//display on

}



//===========================================================================
// No more.
//===========================================================================
