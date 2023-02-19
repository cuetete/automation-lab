// DESCRIPTION:
//
//    FIR
//	  fIn[]:original signal
//	  fOut[]:Signal processed by FIR
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"  

#define FIRNUMBER 25
#define SIGNAL1F 1000
#define SIGNAL2F 4500
#define SAMPLEF  10000
#define PI 3.1415926

float InputWave();
float FIR();

float fHn[FIRNUMBER]={ 0.0,0.0,0.001,-0.002,-0.002,0.01,-0.009,
                       -0.018,0.049,-0.02,0.11,0.28,0.64,0.28,
                       -0.11,-0.02,0.049,-0.018,-0.009,0.01,
                       -0.002,-0.002,0.001,0.0,0.0
                     };
float fXn[FIRNUMBER]={ 0.0 };
float fInput,fOutput;
float fSignal1,fSignal2;
float fStepSignal1,fStepSignal2;
float f2PI;
int i;
float fIn[256],fOut[256];
int nIn,nOut;

void main(void)
{
   nIn=0; nOut=0;
   f2PI=2*PI;
   fSignal1=0.0;
   fSignal2=PI*0.1;
   fStepSignal1=2*PI/30;
   fStepSignal2=2*PI*1.4;
   

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
   // InitGpio(); Skipped for this example

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


// Step 4.
   while(1)
	{
		fInput=InputWave();
		fIn[nIn]=fInput;
		nIn++; nIn%=256;
		fOutput=FIR();
		fOut[nOut]=fOutput;
		nOut++;
		if ( nOut>=256 )
		{
			nOut=0;		/* set breakpoint here */
		}
	}



}

float InputWave()
{
	for ( i=FIRNUMBER-1;i>0;i-- )
		fXn[i]=fXn[i-1];
	fXn[0]=sin(fSignal1)+cos(fSignal2)/6.0;
	fSignal1+=fStepSignal1; 
	if ( fSignal1>=f2PI )	fSignal1-=f2PI;
	fSignal2+=fStepSignal2;
	if ( fSignal2>=f2PI )	fSignal2-=f2PI;
	return(fXn[0]);
}

float FIR()
{
	float fSum;
	fSum=0;
	for ( i=0;i<FIRNUMBER;i++ )
	{
		fSum+=(fXn[i]*fHn[i]);
	}
	return(fSum);
}




//===========================================================================
// No more.
//===========================================================================

