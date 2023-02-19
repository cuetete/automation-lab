#include	"DSP28_Device.h"

Uint16	AicRegs;
Uint16	Led;
extern 	FLAGS   bFlags;

void	main(void)
		{
			/*��ʼ��ϵͳ*/
			InitSysCtrl();

			/*���ж�*/
			DINT;
			IER = 0x0000;
			IFR = 0x0000;
			/*��ʼ��PIE*/
			InitPieCtrl();

			/*��ʼ��PIEʸ����*/
			InitPieVectTable();	
			InitPeripherals();	
			
	
			EINT;   // Enable Global interrupt INTM
			ERTM;	// Enable Global realtime interrupt DBGM
		    play_Udisc();    

			while(1);
		}
		
		
		
		
//===============================end ======================
		
