#ifndef MY_H
#define MY_H


#define	M_INT1		0x0001
#define	M_INT2		0x0002
#define	M_INT3		0x0004
#define	M_INT4		0x0008
#define	M_INT5		0x0010
#define	M_INT6		0x0020
#define	M_INT7		0x0040
#define	M_INT8		0x0080
#define	M_INT9		0x0100
#define	M_INT10		0x0200
#define	M_INT11		0x0400
#define	M_INT12		0x0800
#define	M_INT13		0x1000
#define	M_INT14		0x2000
#define	M_DLOG		0x4000
#define	M_RTOS		0x8000

#define	BIT0		0x0001
#define	BIT1		0x0002
#define	BIT2		0x0004
#define	BIT3		0x0008
#define	BIT4		0x0010
#define	BIT5		0x0020
#define	BIT6		0x0040
#define	BIT7		0x0080
#define	BIT8		0x0100
#define	BIT9		0x0200
#define	BIT10		0x0400
#define	BIT11		0x0800
#define	BIT12		0x1000
#define	BIT13		0x2000
#define	BIT14		0x4000
#define	BIT15		0x8000



//---------------------------------------------------------------------------
// For Portability, User Is Recommended To Use Following Data Type Size
// Definitions For 16-bit and 32-Bit Signed/Unsigned Integers:
//


typedef int             int16;
typedef long            int32;
//typedef unsigned int    Uint16;
//typedef unsigned long   Uint32;
typedef float           float32;
typedef long double     float64;
//---------------------------------------------------------------------------
// Include All Peripheral Header Files:
//

//---------------------------------------------------------------------------
// Define Device Init Function Prototype:
//
#include "common.h"

#include "HPI32.H"
#include "FAT32.H"

#include "hal.h"
#include "device.h"
#include "HPI16.h"
#include "FAT16.h"
#include "FAT.H"

#endif  // end of DSP28_DEVICE_H definition

