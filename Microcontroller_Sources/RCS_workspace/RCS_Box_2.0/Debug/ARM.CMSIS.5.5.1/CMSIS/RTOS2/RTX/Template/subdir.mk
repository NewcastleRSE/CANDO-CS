################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Events.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/MemPool.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/MsgQueue.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Mutex.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Semaphore.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Thread.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Timer.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/main.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/svc_user.c 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Events.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/MemPool.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/MsgQueue.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Mutex.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Semaphore.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Thread.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Timer.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/main.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/svc_user.o 

C_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Events.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/MemPool.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/MsgQueue.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Mutex.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Semaphore.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Thread.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/Timer.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/main.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/svc_user.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/%.o: ../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Template/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/System" -I"C:\Users\ndf30\RCS_workspace\RCS_Box_2.0\ARM.CMSIS.5.5.1\CMSIS/Include" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


