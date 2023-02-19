// DESCRIPTION:
//
//    UDP communication
//    Using the UDP protocol to interact with the computer
//
//###########################################################################


#include "DSP2833x_Device.h"     
#include "DSP2833x_Examples.h"  
#include "W5500.h" 

/****************º¯ÊýÉùÃ÷*******************/  


void s_delay(void);
void delay_loop(void);
void SPI_Init(void);
interrupt void W5500_isr(void);

//Net Parameters
void Load_Net_Parameters(void)
{
	Gateway_IP[0] = 192;
	Gateway_IP[1] = 168;
	Gateway_IP[2] = 1;
	Gateway_IP[3] = 1;

	Sub_Mask[0]=255;
	Sub_Mask[1]=255;
	Sub_Mask[2]=255;
	Sub_Mask[3]=0;

	Phy_Addr[0]=0x0c;
	Phy_Addr[1]=0x29;
	Phy_Addr[2]=0xab;
	Phy_Addr[3]=0x7c;
	Phy_Addr[4]=0x00;
	Phy_Addr[5]=0x01;

	IP_Addr[0]=192;
	IP_Addr[1]=168;
	IP_Addr[2]=1;
	IP_Addr[3]=99;

	S0_Port[0] = 0x13;
	S0_Port[1] = 0x88;

	S0_Mode=UDP_MODE;
}

void W5500_Socket_Set(void)
{
	if(S0_State==0)
	{
		if(Socket_UDP(0)==TRUE)
		{
			S0_State=S_INIT|S_CONN;
		}
		else
		{
			S0_State=0;
		}
	}
}

void W5500_Initialization(void)
{
	W5500_Init();
	Detect_Gateway();
	Socket_Init(0);	
	W5500_Socket_Set();
}

void W5500_Config(void)
{
	Load_Net_Parameters();
	W5500_Initialization();
}

void main(void)
{
   InitSysCtrl();
   InitSpiaGpio();  
   DINT;
   InitPieCtrl();

   IER = 0x0000;
   IFR = 0x0000;

   InitPieVectTable();
   EALLOW;
   PieVectTable.XINT3 = &W5500_isr;
   EDIS;  
   
   EALLOW;		//W5500 CS
   GpioDataRegs.GPBSET.bit.GPIO51 = 1;         
   GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;       
   GpioCtrlRegs.GPBDIR.bit.GPIO51 = 1;         
   GpioDataRegs.GPBSET.bit.GPIO51=1;
   EDIS;
   
   EALLOW;		//W5500 INT
   GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;         
   GpioCtrlRegs.GPBDIR.bit.GPIO52 = 0;          
   GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = 2;        
   GpioCtrlRegs.GPBCTRL.bit.QUALPRD2 = 1;   
   GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;
   EDIS;
   
   EALLOW;
   GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 52;   // XINT3-GPIO52
   EDIS;
   
   XIntruptRegs.XINT3CR.bit.POLARITY = 0;      // falling edge
   XIntruptRegs.XINT3CR.bit.ENABLE = 1;        
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          
   PieCtrlRegs.PIEIER12.bit.INTx1 = 1;          
   IER |= M_INT12;                           
   EINT; 
   
   SPI_Init();
   W5500_Config();		
   for(;;)
   {    
	  if(W5500_Interrupt)
		{
			W5500_Interrupt_Process();		//W5500 data Process
		}
   }
} 	


void s_delay()
{
    long      i;
    for (i = 0; i < 45000; i++) {} //
}

void delay_loop()
{
    long      i;
    for (i = 0; i < 4500000; i++) {} //
}

void error(void)
{
    asm("     ESTOP0");						// Test failed!! Stop!
    for (;;);
}

void SPI_Init(void)
{    
	SpiaRegs.SPICCR.all =0x0007; //8bit
	SpiaRegs.SPICTL.all =0x0006;                   
	SpiaRegs.SPIBRR =0x003F;	//SPI BD =25M/32	=781KHZ£»		
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 0; 
	SpiaRegs.SPICTL.bit.CLK_PHASE=1;					
    SpiaRegs.SPICCR.bit.SPISWRESET=1; 
    SpiaRegs.SPIPRI.bit.FREE = 1;   
}

//W5500-INT ISR
interrupt void	W5500_isr(void) 
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;		//clear flag
	W5500_Interrupt=1;
}

   
//-----------------------------------------------------------------------------------------------------------

