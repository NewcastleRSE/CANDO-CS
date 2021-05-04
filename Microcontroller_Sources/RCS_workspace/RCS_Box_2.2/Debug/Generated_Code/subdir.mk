################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AD1.c \
../Generated_Code/ALGO.c \
../Generated_Code/AS1.c \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/AdcLdd1.c \
../Generated_Code/Cpu.c \
../Generated_Code/DA1.c \
../Generated_Code/DacLdd1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pins1.c \
../Generated_Code/TU1.c \
../Generated_Code/TU2.c \
../Generated_Code/TimeDateLdd1.c \
../Generated_Code/TmDt1.c \
../Generated_Code/WAIT1.c 

OBJS += \
./Generated_Code/AD1.o \
./Generated_Code/ALGO.o \
./Generated_Code/AS1.o \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/Cpu.o \
./Generated_Code/DA1.o \
./Generated_Code/DacLdd1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pins1.o \
./Generated_Code/TU1.o \
./Generated_Code/TU2.o \
./Generated_Code/TimeDateLdd1.o \
./Generated_Code/TmDt1.o \
./Generated_Code/WAIT1.o 

C_DEPS += \
./Generated_Code/AD1.d \
./Generated_Code/ALGO.d \
./Generated_Code/AS1.d \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/AdcLdd1.d \
./Generated_Code/Cpu.d \
./Generated_Code/DA1.d \
./Generated_Code/DacLdd1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pins1.d \
./Generated_Code/TU1.d \
./Generated_Code/TU2.d \
./Generated_Code/TimeDateLdd1.d \
./Generated_Code/TmDt1.d \
./Generated_Code/WAIT1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.2/Static_Code/System" -I"C:\Users\ndf30\RCS_workspace\ARM.CMSIS.5.5.1\CMSIS/Include" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.2/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.2/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.2/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.2/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


