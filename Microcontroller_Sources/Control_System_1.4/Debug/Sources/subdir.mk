################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/ASIC.c \
../Sources/Events.c \
../Sources/IO.c \
../Sources/LED_Calibration.c \
../Sources/LTC2624.c \
../Sources/Phase_Shift_Algorithm.c \
../Sources/SW_Info.c \
../Sources/main.c 

OBJS += \
./Sources/ASIC.o \
./Sources/Events.o \
./Sources/IO.o \
./Sources/LED_Calibration.o \
./Sources/LTC2624.o \
./Sources/Phase_Shift_Algorithm.o \
./Sources/SW_Info.o \
./Sources/main.o 

C_DEPS += \
./Sources/ASIC.d \
./Sources/Events.d \
./Sources/IO.d \
./Sources/LED_Calibration.d \
./Sources/LTC2624.d \
./Sources/Phase_Shift_Algorithm.d \
./Sources/SW_Info.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"D:/RCS_workspace/Control_System_1.4/Static_Code/System" -I"D:\RCS_workspace\ARM.CMSIS.5.5.1\CMSIS/Include" -I"D:/RCS_workspace/Control_System_1.4/Static_Code/PDD" -I"D:/RCS_workspace/Control_System_1.4/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"D:/RCS_workspace/Control_System_1.4/Sources" -I"D:/RCS_workspace/Control_System_1.4/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


