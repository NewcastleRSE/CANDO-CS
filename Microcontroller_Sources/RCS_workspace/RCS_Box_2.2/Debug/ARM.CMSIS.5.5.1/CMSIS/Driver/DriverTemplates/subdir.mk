################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_CAN.c \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.c \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.c \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_Flash.c \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_I2C.c \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_MCI.c \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_SAI.c \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_SPI.c \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_Storage.c \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_USART.c \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_USBD.c \
../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_USBH.c 

OBJS += \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_CAN.o \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.o \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.o \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_Flash.o \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_I2C.o \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_MCI.o \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_SAI.o \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_SPI.o \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_Storage.o \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_USART.o \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_USBD.o \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_USBH.o 

C_DEPS += \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_CAN.d \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.d \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.d \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_Flash.d \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_I2C.d \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_MCI.d \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_SAI.d \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_SPI.d \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_Storage.d \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_USART.d \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_USBD.d \
./ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/Driver_USBH.d 


# Each subdirectory must supply rules for building sources it contributes
ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/%.o: ../ARM.CMSIS.5.5.1/CMSIS/Driver/DriverTemplates/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/System" -I"C:\Users\ndf30\RCS_workspace\RCS_Box_2.0\ARM.CMSIS.5.5.1\CMSIS/Include" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/PDD" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Sources" -I"C:/Users/ndf30/RCS_workspace/RCS_Box_2.0/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


