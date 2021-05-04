################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_delay.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_evflags.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_evr.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_kernel.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_lib.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_memory.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_mempool.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_msgqueue.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_mutex.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_semaphore.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_system.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_thread.c \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_timer.c 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_delay.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_evflags.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_evr.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_kernel.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_lib.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_memory.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_mempool.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_msgqueue.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_mutex.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_semaphore.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_system.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_thread.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_timer.o 

C_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_delay.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_evflags.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_evr.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_kernel.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_lib.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_memory.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_mempool.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_msgqueue.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_mutex.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_semaphore.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_system.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_thread.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/rtx_timer.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/%.o: ../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/System" -I"C:\Users\ndf30\RCS_workspace\RCS_Box_2.0\ARM.CMSIS.5.5.1\CMSIS/Include" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


