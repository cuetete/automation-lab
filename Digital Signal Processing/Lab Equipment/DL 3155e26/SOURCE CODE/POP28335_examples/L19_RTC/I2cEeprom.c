#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define uchar unsigned char

#define SDA_R   GpioDataRegs.GPBDAT.bit.GPIO32;     
#define SDA_W0  GpioDataRegs.GPBCLEAR.bit.GPIO32=1; 
#define SDA_W1  GpioDataRegs.GPBSET.bit.GPIO32=1;  
#define SCL_0   GpioDataRegs.GPBCLEAR.bit.GPIO33=1; 
#define SCL_1   GpioDataRegs.GPBSET.bit.GPIO33=1; 
#define DELAY_UNIT	100							
Uint16 eromrw_err;								

void writebyte(uchar addr,uchar data);
uchar readbyte(uchar addr);
void Eerom_Gpio_Init(void);
void delay(Uint16 time);
void initiic() ;
void begintrans();
void stoptrans();
void ack();
void bytein(uchar ch);
uchar byteout(void);
void Init8563(void);
void GetTime(void);

uchar TAB_T[]={0x00,0x00,0x17,0x26,0x05,0x01,0x18};//second.minute.hour.day.date,month,year

void Eerom_Gpio_Init(void)
{
	EALLOW;
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;	  	 
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;   	 
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;  	 
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3; 	 

    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;	  	 
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;   	 
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;   
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;   
    EDIS;
}
__inline void SDA_READ(void)
{
    EALLOW;
    GpioCtrlRegs.GPBDIR.bit.GPIO32=0;       //Input, SDA
    EDIS;
}

__inline void SDA_WRITE(void)
{
    EALLOW;
    GpioCtrlRegs.GPBDIR.bit.GPIO32=1;       //Output. SDA
    EDIS;
}




///=========================GPIO SIMULATE I2c communication=====================*/
void delay(Uint16 time)  
{
    for(; time>0 ; time--)
    {
        asm(" nop");
        asm(" nop");
        asm(" nop");
        asm(" nop");
		asm(" nop");
        asm(" nop");
        asm(" nop");
        asm(" nop");
    }
}


void begintrans(void)       			 
{
    SDA_WRITE();            				 
    SDA_W1;         						//SDA=1 
    delay(DELAY_UNIT * 10);         		 
    SCL_1;          						//SCL=1
    delay(DELAY_UNIT * 10);         		 
    SDA_W0;         						//SDA=0
    delay(DELAY_UNIT * 10);        			 
    SCL_0;
}

void stoptrans(void)        				//TOP
{
    SDA_WRITE();            				//SDA output
    SCL_0;
    delay(DELAY_UNIT * 10);        			// 
    SDA_W0;         						//SDA=0
    delay(DELAY_UNIT * 10);         		// 
    SCL_1;          						//SCL=1
    delay(DELAY_UNIT * 10);         		// 
    SDA_W1;         						//SDA=1
    delay(DELAY_UNIT * 10);	
}

void ack(void)              				//wait ACK
{
    Uint16 d;
    Uint16  i;     
    SDA_READ();             				//SDA input
    SDA_W1;
    delay(DELAY_UNIT * 2);          		
    SCL_1;          						//SCL=1
    delay(DELAY_UNIT * 2);         		
    i = 0;              
    do
    {
        d = SDA_R;
        i++;
        delay(DELAY_UNIT);	
    }
    while((d == 1) && (i <= 500));      	// 

    if (i >= 499)
    {
        eromrw_err = 0xff;
        stoptrans();
    }
    
    i = 0;           
    SCL_0;          						//SCL=0
    delay(DELAY_UNIT * 2);          		 
}

void bytein(uchar ch)  				
{
    uchar i;     
    SCL_0;          						//SCL=0
    delay(DELAY_UNIT * 2);					 
    SDA_WRITE();            				//SDA output
    delay(DELAY_UNIT);         				  
    for(i=8;i>0;i--)
    {	
        if ((ch & 0x80)== 0) 
    	{
            SDA_W0;     					 
            delay(DELAY_UNIT);				
    	}
        else 
    	{
            SDA_W1;
            delay(DELAY_UNIT);				 
    	}
        SCL_1;      						//SCL=1 
        delay(DELAY_UNIT * 2);      		 
        ch <<= 1;
        SCL_0;      						//SCL=0 
        delay(DELAY_UNIT);      			 
    } 
    ack();
}

uchar byteout(void)        				 
{
    uchar i;
    uchar ch=0;

    SDA_READ();             				 
    delay(DELAY_UNIT * 2);         			 
    for(i=8;i>0;i--)
    {
        ch <<= 1;
        SCL_0;      						//SCL=1
        delay(DELAY_UNIT);      			 
        SCL_1;      						//SCL=0
        ch |= SDA_R;    					 
        delay(DELAY_UNIT * 2);      		 
    }
    return(ch);
}

void writebyte(uchar addr,uchar data) 	 
{
    begintrans();							 
    bytein(0xA2);  							 
    bytein(addr);       					 
    bytein(data);      						
    stoptrans();					 
    delay(8000);
}



uchar readbyte(uchar addr) 				 
{
    uchar c;    
    begintrans();       				
    bytein(0xA2);   
    bytein(addr);       					 
    begintrans();       					  
    bytein(0xA3);       					 
    c = byteout();      					 
    stoptrans();        					 
    delay(2000);        					 
    return(c);
}

void Init8563(void)
{
	uchar i,ucAddr=0x02;
	writebyte(0x00,0x00);
	writebyte(0x01,0x11);
	writebyte(0x0D,0x03);  //CLKOUT frequency =1Hz
	for(i=0;i<7;i++)
	{
		writebyte(ucAddr,TAB_T[i]);
		ucAddr++;
	}
}

void GetTime(void)
{
	uchar i,ucAddr=0x02;
	uchar *pTime=TAB_T;
	for(i=0;i<7;i++)
	{
		pTime[i]=readbyte(ucAddr);
		ucAddr++;
	}
	pTime[0]&=0x7f; //������Чλ
	pTime[1]&=0x7f;
	pTime[2]&=0x3f;
	pTime[3]&=0x3f;
	pTime[4]&=0x07;
	pTime[5]&=0x1f;
}





//===========================================================================
// No more.
//===========================================================================
