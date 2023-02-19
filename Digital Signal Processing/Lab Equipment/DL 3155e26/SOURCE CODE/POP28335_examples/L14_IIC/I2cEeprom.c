#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define SDA_R   GpioDataRegs.GPBDAT.bit.GPIO32;  
#define SDA_W0  GpioDataRegs.GPBCLEAR.bit.GPIO32=1;
#define SDA_W1  GpioDataRegs.GPBSET.bit.GPIO32=1;  
#define SCL_0   GpioDataRegs.GPBCLEAR.bit.GPIO33=1;
#define SCL_1   GpioDataRegs.GPBSET.bit.GPIO33=1;  
#define DELAY_UNIT	10								
Uint16 eromrw_err;									

void writebyte(Uint16 addr,Uint16 data);
Uint16 readbyte(Uint16 addr);
void Eerom_Gpio_Init(void);
void delay(Uint16 time);
void initiic() ;
void begintrans();
void stoptrans();
void ack();
void bytein(Uint16 ch);
Uint16 byteout(void);


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
    SDA_W1;         						
    delay(DELAY_UNIT * 10);         		
    SDA_WRITE();            				
    delay(DELAY_UNIT * 10);         		
    SCL_1;          						
    delay(DELAY_UNIT * 10);         		
    SDA_W0;         						
    delay(DELAY_UNIT * 10);        			
}

void stoptrans(void)        				
{
    SDA_WRITE();            				
    delay(DELAY_UNIT * 10);        			
    SDA_W0;         						
    delay(DELAY_UNIT * 10);         		
    SCL_1;          						
    delay(DELAY_UNIT * 10);         		
    SDA_W1;         						
    delay(DELAY_UNIT * 10);	
}

void ack(void)              				
{
    Uint16 d;
    Uint16  i;     
    SDA_READ();             				
    delay(DELAY_UNIT * 2);          		
    SCL_1;          						
    delay(DELAY_UNIT * 2);         			
    i = 0;              
    do
    {
        d = SDA_R;
        i++;
        delay(DELAY_UNIT);	
    }
    while((d == 1) && (i <= 500));      	

    if (i >= 499)
    {
        eromrw_err = 0xff;
    }
    
    i = 0;           
    SCL_0;          						
    delay(DELAY_UNIT * 2);          		
}

void bytein(Uint16 ch)  					
{
    Uint16 i;     
    SCL_0;          						
    delay(DELAY_UNIT * 2);					
    SDA_WRITE();            				
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
        SCL_1;      						
        delay(DELAY_UNIT * 2);      		
        ch <<= 1;
        SCL_0;      						
        delay(DELAY_UNIT);      			
    } 
    ack();
}

Uint16 byteout(void)        				
{
    unsigned char i;
    Uint16 ch;
    ch = 0;

    SDA_READ();             				
    delay(DELAY_UNIT * 2);         			
    for(i=8;i>0;i--)
    {
        ch <<= 1;
        SCL_1;      						
        delay(DELAY_UNIT);      			
        ch |= SDA_R;    					
        delay(DELAY_UNIT);     				
        SCL_0;      						
        delay(DELAY_UNIT * 2);      		
    }
    return(ch);
}

void writebyte(Uint16 addr,Uint16 data) 	
{
    begintrans();							
    bytein(0xA0 + ((addr & 0x0300) >> 7));  
    bytein(addr);       					
    bytein(data);      						
    stoptrans();							
    delay(8000);
}



Uint16 readbyte(Uint16 addr) 				
{
    Uint16 c;    
    begintrans();       					
    bytein(0xA0 + ((addr & 0x0300) >> 7));  
    bytein(addr);       					
    begintrans();       					
    bytein(0xA1);       					
    c = byteout();      					
    stoptrans();        					
    delay(2000);        					
    return(c);
}









//===========================================================================
// No more.
//===========================================================================
