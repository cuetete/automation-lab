################################################################################
# Automatically-generated file. Do not edit!
################################################################################

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"./pmsm.obj" \
"./F28335_vdc.obj" \
"./DSP2833x_usDelay.obj" \
"./DSP2833x_GlobalVariableDefs.obj" \
"./DSP2833x_ADC_cal.obj" \
"./DLOG4CHC.obj" \
"../28335_RAM_lnk.cmd" \
"../DSP2833x_Headers_nonBIOS.cmd" \
"../IQmath_fpu32.lib" \
"../SFO_TI_Build_fpu.lib" \
"../rts2800_fpu32.lib" \

-include ../makefile.init

RM := DEL /F

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: PmSensored.out

# Tool invocations
PmSensored.out: $(GEN_CMDS) $(CMD_SRCS) $(LIB_SRCS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	"F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --diag_warning=225 --large_memory_model --float_support=fpu32 -z -m"PmSensored.map" --stack_size=800 --heap_size=0x1000 --warn_sections -i"F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"F:/program files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --reread_libs --rom_model -o "PmSensored.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QTD) "PmSensored.out"
	-$(RM) ".\DLOG4CHC.obj" ".\DSP2833x_ADC_cal.obj" ".\DSP2833x_GlobalVariableDefs.obj" ".\DSP2833x_usDelay.obj" ".\F28335_vdc.obj" ".\pmsm.obj" 
	-$(RM) ".\DLOG4CHC.pp" ".\DSP2833x_ADC_cal.pp" ".\DSP2833x_usDelay.pp" 
	-$(RM) ".\DSP2833x_GlobalVariableDefs.pp" ".\F28335_vdc.pp" ".\pmsm.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
