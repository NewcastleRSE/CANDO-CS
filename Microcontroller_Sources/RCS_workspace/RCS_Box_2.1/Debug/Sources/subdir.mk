################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/Phase_Shift_Algorithm.c \
../Sources/SW_Info.c \
../Sources/main.c 

OBJS += \
./Sources/Events.o \
./Sources/Phase_Shift_Algorithm.o \
./Sources/SW_Info.o \
./Sources/main.o 

C_DEPS += \
./Sources/Events.d \
./Sources/Phase_Shift_Algorithm.d \
./Sources/SW_Info.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.1/Static_Code/System" -I"C:\Users\ndf30\RCS_workspace\ARM.CMSIS.5.5.1\CMSIS/Include" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.1/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.1/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.1/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.1/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


