################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Device/Source/GCC/startup_LPC18xx.S 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Device/Source/GCC/startup_LPC18xx.o 

S_UPPER_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Device/Source/GCC/startup_LPC18xx.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Device/Source/GCC/%.o: ../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/Device/Source/GCC/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


