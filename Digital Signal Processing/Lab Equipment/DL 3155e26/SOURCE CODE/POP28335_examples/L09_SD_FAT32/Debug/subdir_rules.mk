################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Debug/DEVICE.obj: ../DEVICE.C $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="DEVICE.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/DSP2833x_ADC_cal.obj: ../DSP2833x_ADC_cal.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="DSP2833x_ADC_cal.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/DSP2833x_CodeStartBranch.obj: ../DSP2833x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="DSP2833x_CodeStartBranch.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/DSP2833x_DefaultIsr.obj: ../DSP2833x_DefaultIsr.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="DSP2833x_DefaultIsr.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/DSP2833x_GlobalVariableDefs.obj: ../DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="DSP2833x_GlobalVariableDefs.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/DSP2833x_PieCtrl.obj: ../DSP2833x_PieCtrl.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="DSP2833x_PieCtrl.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/DSP2833x_PieVect.obj: ../DSP2833x_PieVect.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="DSP2833x_PieVect.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/DSP2833x_Spi.obj: ../DSP2833x_Spi.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="DSP2833x_Spi.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/DSP2833x_SysCtrl.obj: ../DSP2833x_SysCtrl.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="DSP2833x_SysCtrl.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/DSP2833x_Xintf.obj: ../DSP2833x_Xintf.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="DSP2833x_Xintf.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/DSP2833x_usDelay.obj: ../DSP2833x_usDelay.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="DSP2833x_usDelay.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/Fat16.obj: ../Fat16.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="Fat16.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/Fat32.obj: ../Fat32.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="Fat32.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/HAL.obj: ../HAL.C $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="HAL.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/HPI16.obj: ../HPI16.C $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="HPI16.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/HPI32.obj: ../HPI32.C $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="HPI32.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/SD_FAT32.obj: ../SD_FAT32.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="SD_FAT32.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/SD_SPI_Erase.obj: ../SD_SPI_Erase.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="SD_SPI_Erase.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/SD_SPI_Initialization.obj: ../SD_SPI_Initialization.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="SD_SPI_Initialization.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/SD_SPI_Read.obj: ../SD_SPI_Read.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="SD_SPI_Read.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/SD_SPI_Registers.obj: ../SD_SPI_Registers.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="SD_SPI_Registers.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/SD_SPI_Transmission.obj: ../SD_SPI_Transmission.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="SD_SPI_Transmission.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/SD_SPI_Write.obj: ../SD_SPI_Write.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="SD_SPI_Write.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/Udisc.obj: ../Udisc.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="Udisc.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Debug/fat.obj: ../fat.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/bin/cl2000" -v28 -mt -ml -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/ti/ccsv4/tools/compiler/c2000/include" --include_path="/packages/ti/xdais" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_headers/include" --include_path="F:/project/EE_OEM/DL 3155E26/DISK/SOURCE CODE/POP28335_examples/L09_SD_FAT32/../../DSP2833x_common/include" --quiet --diag_warning=225 --issue_remarks --output_all_syms --asm_directory="./Debug" --obj_directory="./Debug" --preproc_with_compile --preproc_dependency="fat.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


