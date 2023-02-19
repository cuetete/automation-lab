#ifndef _I2C_H
#define _I2C_H


#define	E2PROM_INITED_MARK_ADDR	1022
#define	E2PROM_FAULT_START_ADDR	320
#define	E2PROM_PARA_START_ADDR	0
#define	E2PROM_PARA_TOTAL_NUM	91
#define	E2PROM_PARA_VERIFY_ADDR	254
#define E2PROM_SpdADOffset_ADDR	256
#define	E2PROM_TorADOffset_ADDR	258


#define SDA_R   GpioDataRegs.GPBDAT.bit.GPIO32;     //read sda state.
#define SDA_W0  GpioDataRegs.GPBCLEAR.bit.GPIO32=1; //out 0.
#define SDA_W1  GpioDataRegs.GPBSET.bit.GPIO32=1;   //out 1.
#define SCL_0   GpioDataRegs.GPBCLEAR.bit.GPIO33=1; //out 0.
#define SCL_1   GpioDataRegs.GPBSET.bit.GPIO33=1;   //out 1.

extern void SaveToE2PROM_16(Uint16 addr,Uint16 data);
extern Uint16 RecallPara(Uint16 paracode);
extern void writebyte(Uint16 addr,Uint16 data);
extern Uint16 readbyte(Uint16 addr);
extern void E2PROMAllParaInit(void);
extern void SavePara (Uint16 Pn, Uint16 Val);

#endif
//===========================================================================
// No more.
//=========================================================================== 

