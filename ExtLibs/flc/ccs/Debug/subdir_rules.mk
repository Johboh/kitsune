################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
flc.obj: C:/Users/chrisjohnson/Desktop/kitsune/ExtLibs/flc/flc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.5/include" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/ExtLibs/flc" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/extlibs/include" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/driverlib" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/inc" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/simplelink" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/simplelink/Include" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/simplelink/Source" -g --define=cc3200 --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on -mt --preproc_with_compile --preproc_dependency="flc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


