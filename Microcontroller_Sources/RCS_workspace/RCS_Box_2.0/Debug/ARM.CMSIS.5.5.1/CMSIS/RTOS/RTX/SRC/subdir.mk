################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/HAL_CM.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_CMSIS.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Event.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_List.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Mailbox.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_MemBox.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Memory.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Mutex.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Robin.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Semaphore.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_System.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Task.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Time.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Timer.c 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/HAL_CM.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_CMSIS.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Event.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_List.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Mailbox.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_MemBox.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Memory.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Mutex.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Robin.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Semaphore.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_System.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Task.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Time.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Timer.o 

C_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/HAL_CM.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_CMSIS.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Event.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_List.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Mailbox.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_MemBox.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Memory.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Mutex.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Robin.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Semaphore.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_System.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Task.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Time.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/rt_Timer.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/%.o: ../ARM.CMSIS.5.5.1/CMSIS/RTOS/RTX/SRC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/System" -I"C:\Users\ndf30\RCS_workspace\RCS_Box_2.0\ARM.CMSIS.5.5.1\CMSIS/Include" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


