################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ff.obj: C:/Users/chrisjohnson/Desktop/kitsune/third_party/fatfs/src/ff.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me -O1 --opt_for_speed=0 --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.5/include" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/third_party/fatfs/src/" -g --define=cc3200 --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="ff.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


