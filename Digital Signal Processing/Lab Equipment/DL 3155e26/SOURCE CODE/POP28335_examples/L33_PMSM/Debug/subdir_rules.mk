################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
DLOG4CHC.obj: ../DLOG4CHC.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"/bin/cl2000" --silicon_version=28 -g --include_path="/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DLOG4CHC.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_ADC_cal.obj: ../DSP2833x_ADC_cal.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"/bin/cl2000" --silicon_version=28 -g --include_path="/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_ADC_cal.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_GlobalVariableDefs.obj: ../DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"/bin/cl2000" --silicon_version=28 -g --include_path="/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_GlobalVariableDefs.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_usDelay.obj: ../DSP2833x_usDelay.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"/bin/cl2000" --silicon_version=28 -g --include_path="/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="DSP2833x_usDelay.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

F28335_vdc.obj: ../F28335_vdc.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"/bin/cl2000" --silicon_version=28 -g --include_path="/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="F28335_vdc.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

pmsm.obj: ../pmsm.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"/bin/cl2000" --silicon_version=28 -g --include_path="/include" --include_path="F:/work/include/Math_headers_v4" --include_path="F:/work/include/DSP2833x_common/includee" --include_path="F:/work/include/DSP2833x_common/sources" --include_path="F:/work/include/DSP2833x_headers/include" --include_path="F:/work/include/DSP2833x_headers/source" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="pmsm.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


