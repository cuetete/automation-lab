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


# Each subdirectory must supply rules for building sources it contributes
DLOG4CHC.obj: ../DLOG4CHC.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DLOG4CHC.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_ADC_cal.obj: ../DSP2833x_ADC_cal.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_ADC_cal.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_GlobalVariableDefs.obj: ../DSP2833x_GlobalVariableDefs.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_GlobalVariableDefs.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_usDelay.obj: ../DSP2833x_usDelay.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_usDelay.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

F28335_vdc.obj: ../F28335_vdc.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="F28335_vdc.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

pmsm.obj: ../pmsm.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --include_path="F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="pmsm.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


