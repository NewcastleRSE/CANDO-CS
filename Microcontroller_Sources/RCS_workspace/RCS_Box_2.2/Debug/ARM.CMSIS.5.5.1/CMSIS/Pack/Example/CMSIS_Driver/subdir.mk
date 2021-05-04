################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/CAN_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/EMAC_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/GPDMA_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/GPIO_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/I2C_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/I2S_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/MCI_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/SCU_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/SSP_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USART_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USB0_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USB1_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBD0_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBD1_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBH0_LPC18xx.c \
../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBH1_LPC18xx.c 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/CAN_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/EMAC_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/GPDMA_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/GPIO_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/I2C_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/I2S_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/MCI_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/SCU_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/SSP_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USART_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USB0_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USB1_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBD0_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBD1_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBH0_LPC18xx.o \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBH1_LPC18xx.o 

C_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/CAN_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/EMAC_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/GPDMA_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/GPIO_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/I2C_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/I2S_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/MCI_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/SCU_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/SSP_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USART_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USB0_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USB1_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBD0_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBD1_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBH0_LPC18xx.d \
./ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/USBH1_LPC18xx.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/%.o: ../ARM.CMSIS.5.5.1/CMSIS/Pack/Example/CMSIS_Driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/System" -I"C:\Users\ndf30\RCS_workspace\RCS_Box_2.0\ARM.CMSIS.5.5.1\CMSIS/Include" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


