// DESCRIPTION:
//
//    FFT
//	  INPUT[]:original signal
//	  OUT[]:Signal processed by FFT
//###########################################################################


#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include"math.h"

#define PI 3.1415926
#define SAMPLENUMBER 128

void InitForFFT();
void MakeWave();
//void FFT(float dataR[SAMPLENUMBER],float dataI[SAMPLENUMBER]);

int INPUT[SAMPLENUMBER],DATA[SAMPLENUMBER];
float fWaveR[SAMPLENUMBER],fWaveI[SAMPLENUMBER],w[SAMPLENUMBER];
float sin_tab[SAMPLENUMBER],cos_tab[SAMPLENUMBER];


void FFT(float dataR[SAMPLENUMBER],float dataI[SAMPLENUMBER])
{
	int x0,x1,x2,x3,x4,x5,x6,xx;
	int i,j,k,b,p,L;
	float TR,TI,temp;
	
	/********** following code invert sequence ************/
	for ( i=0;i<SAMPLENUMBER;i++ )
	{
		x0=x1=x2=x3=x4=x5=x6=0;
		x0=i&0x01; x1=(i/2)&0x01; x2=(i/4)&0x01; x3=(i/8)&0x01;x4=(i/16)&0x01; x5=(i/32)&0x01; x6=(i/64)&0x01;
		xx=x0*64+x1*32+x2*16+x3*8+x4*4+x5*2+x6;
		dataI[xx]=dataR[i];
	}
	for ( i=0;i<SAMPLENUMBER;i++ )
	{
		dataR[i]=dataI[i]; dataI[i]=0; 
	}

	/************** following code FFT *******************/
	for ( L=1;L<=7;L++ )
	{ /* for(1) */
		b=1; i=L-1;
		while ( i>0 ) 
		{
			b=b*2; i--;
		} /* b= 2^(L-1) */
		for ( j=0;j<=b-1;j++ ) /* for (2) */
		{
			p=1; i=7-L;
			while ( i>0 ) /* p=pow(2,7-L)*j; */
			{
				p=p*2; i--;
			}
			p=p*j;
			for ( k=j;k<128;k=k+2*b ) /* for (3) */
			{
				TR=dataR[k]; TI=dataI[k]; temp=dataR[k+b];
				dataR[k]=dataR[k]+dataR[k+b]*cos_tab[p]+dataI[k+b]*sin_tab[p];
				dataI[k]=dataI[k]-dataR[k+b]*sin_tab[p]+dataI[k+b]*cos_tab[p];
				dataR[k+b]=TR-dataR[k+b]*cos_tab[p]-dataI[k+b]*sin_tab[p];
				dataI[k+b]=TI+temp*sin_tab[p]-dataI[k+b]*cos_tab[p];
			} /* END for (3) */
		} /* END for (2) */
	} /* END for (1) */
	for ( i=0;i<SAMPLENUMBER/2;i++ )
	{ 
		w[i]=sqrt(dataR[i]*dataR[i]+dataI[i]*dataI[i]);
	}
} /* END FFT */




void InitForFFT()
{
	int i;
	
	for ( i=0;i<SAMPLENUMBER;i++ )
	{
		sin_tab[i]=sin(PI*2*i/SAMPLENUMBER);
		cos_tab[i]=cos(PI*2*i/SAMPLENUMBER);
	}
}

void MakeWave()
{
	int i;
	
	for ( i=0;i<SAMPLENUMBER;i++ )
	{
		INPUT[i]=sin(PI*2*8*i/SAMPLENUMBER)*1024;// ---1024
	}
}


void main(void)
{
   int i;

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

    InitForFFT();
	MakeWave();
	for ( i=0;i<SAMPLENUMBER;i++ )
	{
		fWaveR[i]=INPUT[i];
		fWaveI[i]=0.0f;
		w[i]=0.0f;
	}
	FFT(fWaveR,fWaveI);
	for ( i=0;i<SAMPLENUMBER;i++ )
	{
		DATA[i]=w[i];
	}
	
	for(;;)
	{ 
	} //break point


}





//===========================================================================
// No more.
//===========================================================================

