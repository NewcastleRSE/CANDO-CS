################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mbl.S \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mbl_ns.S \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml.S \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml_fp.S \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml_fp_ns.S \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml_ns.S \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_ca.S \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_cm0.S \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_cm3.S \
../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_cm4f.S 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mbl.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mbl_ns.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml_fp.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml_fp_ns.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml_ns.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_ca.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_cm0.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_cm3.o \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_cm4f.o 

S_UPPER_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mbl.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mbl_ns.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml_fp.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml_fp_ns.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml_ns.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_ca.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_cm0.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_cm3.d \
./ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/irq_cm4f.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/%.o: ../ARM.CMSIS.5.5.1/CMSIS/RTOS2/RTX/Source/GCC/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


