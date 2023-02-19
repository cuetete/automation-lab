################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LIB_SRCS += \
../IQmath_fpu32.lib \
../SFO_TI_Build_fpu.lib \
../rts2800_fpu32.lib 

C_SRCS += \
../DSP2833x_GlobalVariableDefs.c \
../F28335_vdc.c \
../pmsm.c 

ASM_SRCS += \
../DLOG4CHC.asm \
../DSP2833x_ADC_cal.asm \
../DSP2833x_usDelay.asm 

CMD_SRCS += \
../28335_RAM_lnk.cmd \
../DSP2833x_Headers_nonBIOS.cmd 

ASM_DEPS += \
./DLOG4CHC.pp \
./DSP2833x_ADC_cal.pp \
./DSP2833x_usDelay.pp 

OBJS += \
./DLOG4CHC.obj \
./DSP2833x_ADC_cal.obj \
./DSP2833x_GlobalVariableDefs.obj \
./DSP2833x_usDelay.obj \
./F28335_vdc.obj \
./pmsm.obj 

C_DEPS += \
./DSP2833x_GlobalVariableDefs.pp \
./F28335_vdc.pp \
./pmsm.pp 

OBJS__QTD += \
".\DLOG4CHC.obj" \
".\DSP2833x_ADC_cal.obj" \
".\DSP2833x_GlobalVariableDefs.obj" \
".\DSP2833x_usDelay.obj" \
".\F28335_vdc.obj" \
".\pmsm.obj" 

ASM_DEPS__QTD += \
".\DLOG4CHC.pp" \
".\DSP2833x_ADC_cal.pp" \
".\DSP2833x_usDelay.pp" 

C_DEPS__QTD += \
".\DSP2833x_GlobalVariableDefs.pp" \
".\F28335_vdc.pp" \
".\pmsm.pp" 

ASM_SRCS_QUOTED += \
"../DLOG4CHC.asm" \
"../DSP2833x_ADC_cal.asm" \
"../DSP2833x_usDelay.asm" 

C_SRCS_QUOTED += \
"../DSP2833x_GlobalVariableDefs.c" \
"../F28335_vdc.c" \
"../pmsm.c" 


