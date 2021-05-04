################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.c \
../ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.c \
../ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.c \
../ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.c \
../ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.c \
../ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.c 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.o \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.o \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.o \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.o \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.o \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.o 

C_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.d \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.d \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15.d \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q15_opt.d \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7.d \
./ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/arm_fully_connected_q7_opt.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/%.o: ../ARM.CMSIS.5.5.1/CMSIS/NN/Source/FullyConnectedFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/System" -I"C:\Users\ndf30\RCS_workspace\RCS_Box_2.0\ARM.CMSIS.5.5.1\CMSIS/Include" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


