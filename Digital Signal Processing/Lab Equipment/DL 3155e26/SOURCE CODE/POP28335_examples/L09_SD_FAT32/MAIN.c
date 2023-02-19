#include	"DSP28_Device.h"

Uint16	AicRegs;
Uint16	Led;
extern 	FLAGS   bFlags;

void	main(void)
		{
			/*初始化系统*/
			InitSysCtrl();

			/*关中断*/
			DINT;
			IER = 0x0000;
			IFR = 0x0000;
			/*初始化PIE*/
			InitPieCtrl();

			/*初始化PIE矢量表*/
			InitPieVectTable();	
			InitPeripherals();	
			
	
			EINT;   // Enable Global interrupt INTM
			ERTM;	// Enable Global realtime interrupt DBGM
		    play_Udisc();    

			while(1);
		}
		
		
		
		
//===============================end ======================
		
