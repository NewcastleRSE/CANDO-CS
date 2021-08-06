################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/ControllerFunctions.c \
../ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_f32.c \
../ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q15.c \
../ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q31.c \
../ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_f32.c \
../ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q15.c \
../ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q31.c \
../ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_f32.c \
../ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_q31.c 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/ControllerFunctions.o \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_f32.o \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q15.o \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q31.o \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_f32.o \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q15.o \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q31.o \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_f32.o \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_q31.o 

C_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/ControllerFunctions.d \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_f32.d \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q15.d \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_init_q31.d \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_f32.d \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q15.d \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_pid_reset_q31.d \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_f32.d \
./ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/arm_sin_cos_q31.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/%.o: ../ARM.CMSIS.5.5.1/CMSIS/DSP/Source/ControllerFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/System" -I"C:\Users\ndf30\RCS_workspace\RCS_Box_2.0\ARM.CMSIS.5.5.1\CMSIS/Include" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


