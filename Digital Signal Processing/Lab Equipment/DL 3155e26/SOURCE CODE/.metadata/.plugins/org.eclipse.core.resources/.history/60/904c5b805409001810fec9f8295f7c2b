################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)
CG_TOOL_ROOT := D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"./Debug/Example_2833x_FFT.obj" \
"./Debug/DSP2833x_usDelay.obj" \
"./Debug/DSP2833x_SysCtrl.obj" \
"./Debug/DSP2833x_PieVect.obj" \
"./Debug/DSP2833x_PieCtrl.obj" \
"./Debug/DSP2833x_GlobalVariableDefs.obj" \
"./Debug/DSP2833x_DefaultIsr.obj" \
"./Debug/DSP2833x_CodeStartBranch.obj" \
"./Debug/DSP2833x_ADC_cal.obj" \
-l"rts2800_fpu32.lib" \
"F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/DSP2833x_common/cmd/28335_RAM_lnk.cmd" \
"F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/DSP2833x_headers/cmd/DSP2833x_Headers_nonBIOS.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
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
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
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
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Example_2833x_FFT.out

# Tool invocations
Example_2833x_FFT.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --diag_warning=225 --issue_remarks --float_support=fpu32 --asm_directory="./Debug" --obj_directory="./Debug" -z -m"../Example_2833x_FFT.map" --stack_size=0x200 --warn_sections -i"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/lib" -i"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" -i"F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L30_FFT" -i"F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/DSP2833x_headers/include" --reread_libs --rom_model -o "Example_2833x_FFT.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QTD) "Example_2833x_FFT.out"
	-$(RM) ".\Debug\DSP2833x_ADC_cal.obj" ".\Debug\DSP2833x_CodeStartBranch.obj" ".\Debug\DSP2833x_DefaultIsr.obj" ".\Debug\DSP2833x_GlobalVariableDefs.obj" ".\Debug\DSP2833x_PieCtrl.obj" ".\Debug\DSP2833x_PieVect.obj" ".\Debug\DSP2833x_SysCtrl.obj" ".\Debug\DSP2833x_usDelay.obj" ".\Debug\Example_2833x_FFT.obj" 
	-$(RM) ".\DSP2833x_ADC_cal.pp" ".\DSP2833x_CodeStartBranch.pp" ".\DSP2833x_usDelay.pp" 
	-$(RM) ".\DSP2833x_DefaultIsr.pp" ".\DSP2833x_GlobalVariableDefs.pp" ".\DSP2833x_PieCtrl.pp" ".\DSP2833x_PieVect.pp" ".\DSP2833x_SysCtrl.pp" ".\Example_2833x_FFT.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
