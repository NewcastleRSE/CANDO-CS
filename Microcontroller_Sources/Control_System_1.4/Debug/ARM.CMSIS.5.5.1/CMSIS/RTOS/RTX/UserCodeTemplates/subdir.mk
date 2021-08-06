################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/MailQueue.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/MemPool.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/MsgQueue.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Mutex.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Semaphore.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Thread.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Timer.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/main.c 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/MailQueue.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/MemPool.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/MsgQueue.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Mutex.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Semaphore.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Thread.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Timer.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/main.o 

C_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/MailQueue.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/MemPool.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/MsgQueue.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Mutex.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Semaphore.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Thread.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/Timer.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/main.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/%.o: ../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/UserCodeTemplates/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/System" -I"C:\Users\ndf30\RCS_workspace\RCS_Box_2.0\ARM.CMSIS.5.5.1\CMSIS/Include" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


