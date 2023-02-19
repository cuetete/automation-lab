// DESCRIPTION:
//
//    IIR
//	  fIn[]:original signal
//	  fOut[]:Signal processed by FIR
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"

#define IIRNUMBER 2
#define SIGNAL1F 1000
#define SIGNAL2F 4500
#define SAMPLEF  10000
#define PI 3.1415926

float InputWave();
float IIR();

float fBn[IIRNUMBER]={ 0.0,0.7757 };
float fAn[IIRNUMBER]={ 0.1122,0.1122 };
float fXn[IIRNUMBER]={ 0.0 };
float fYn[IIRNUMBER]={ 0.0 };
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
//	fStepSignal1=2*PI/30;
//	fStepSignal2=2*PI*1.4;
	fStepSignal1=2*PI/50;
	fStepSignal2=2*PI/2.5;
   
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
   for(;;)
   {
		fInput=InputWave();
		fIn[nIn]=fInput;
		nIn++; nIn%=256;
		fOutput=IIR();
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
	for ( i=IIRNUMBER-1;i>0;i-- )
	{
		fXn[i]=fXn[i-1];
		fYn[i]=fYn[i-1];
	}
	fXn[0]=sin(fSignal1)+cos(fSignal2)/6.0;
	fYn[0]=0.0;
	fSignal1+=fStepSignal1; 
	if ( fSignal1>=f2PI )	fSignal1-=f2PI;
	fSignal2+=fStepSignal2;
	if ( fSignal2>=f2PI )	fSignal2-=f2PI;
	return(fXn[0]);
}

float IIR()
{
	float fSum;
	fSum=0.0;
	for ( i=0;i<IIRNUMBER;i++ )
	{
		fSum+=(fXn[i]*fAn[i]);
		fSum+=(fYn[i]*fBn[i]);
	}
	return(fSum);
}

//===========================================================================
// No more.
//===========================================================================

