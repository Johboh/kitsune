################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
nanopb/pb_decode.obj: C:/Users/chrisjohnson/Desktop/kitsune/kitsune/nanopb/pb_decode.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me -O1 --opt_for_speed=0 --fp_mode=relaxed --include_path="C:/Users/chrisjohnson/Desktop/kitsune/third_party/fatfs/src" --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.5/include" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/driverlib/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/ExtLibs/Include/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/third_party/FreeRTOS/source/portable/CCS/ARM_CM3/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/third_party/FreeRTOS/source/include/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/third_party/FreeRTOS/source/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/oslib/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/driverlib/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/simplelink/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/simplelink/Source/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/simplelink/Include/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/inc/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/kitsune/common" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/kitsune/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/kitsune/nanopb" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/kitsune/protobuf" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/kitsune/main/" -g --no_intrinsics --gcc --define=ccs --define=ARM --define=CC3200_ES_1_2_1 --define=USE_FREERTOS --define=cc3200 --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="nanopb/pb_decode.pp" --obj_directory="nanopb" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

nanopb/pb_encode.obj: C:/Users/chrisjohnson/Desktop/kitsune/kitsune/nanopb/pb_encode.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me -O1 --opt_for_speed=0 --fp_mode=relaxed --include_path="C:/Users/chrisjohnson/Desktop/kitsune/third_party/fatfs/src" --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.5/include" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/driverlib/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/ExtLibs/Include/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/third_party/FreeRTOS/source/portable/CCS/ARM_CM3/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/third_party/FreeRTOS/source/include/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/third_party/FreeRTOS/source/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/oslib/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/driverlib/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/simplelink/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/simplelink/Source/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/simplelink/Include/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/inc/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/kitsune/common" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/kitsune/" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/kitsune/nanopb" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/kitsune/protobuf" --include_path="C:/Users/chrisjohnson/Desktop/kitsune/kitsune/main/" -g --no_intrinsics --gcc --define=ccs --define=ARM --define=CC3200_ES_1_2_1 --define=USE_FREERTOS --define=cc3200 --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="nanopb/pb_encode.pp" --obj_directory="nanopb" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


