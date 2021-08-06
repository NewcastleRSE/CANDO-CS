################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/ADC_MCB1800.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Audio_UDA1380.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Buttons_MCB1800.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/EEPROM_24LC128.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/GLCD_Fonts.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/GLCD_MCB1800.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Joystick_MCB1800.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/LED_MCB1800.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Thermometer_LM75.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Touch_STMPE811.c 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/ADC_MCB1800.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Audio_UDA1380.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Buttons_MCB1800.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/EEPROM_24LC128.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/GLCD_Fonts.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/GLCD_MCB1800.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Joystick_MCB1800.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/LED_MCB1800.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Thermometer_LM75.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Touch_STMPE811.o 

C_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/ADC_MCB1800.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Audio_UDA1380.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Buttons_MCB1800.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/EEPROM_24LC128.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/GLCD_Fonts.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/GLCD_MCB1800.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Joystick_MCB1800.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/LED_MCB1800.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Thermometer_LM75.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/Touch_STMPE811.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/%.o: ../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Boards/Keil/MCB1800/Common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/System" -I"C:\Users\ndf30\RCS_workspace\RCS_Box_2.0\ARM.CMSIS.5.5.1\CMSIS/Include" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


