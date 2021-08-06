################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/Mutex.cpp \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/RtosTimer.cpp \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/Semaphore.cpp \
../ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/Thread.cpp 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/Mutex.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/RtosTimer.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/Semaphore.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/Thread.o 

CPP_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/Mutex.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/RtosTimer.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/Semaphore.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/Thread.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/%.o: ../ARM.CMSIS.5.5.1/CMSIS/RTOS/Template/CPP/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/System" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Generated_Code" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


