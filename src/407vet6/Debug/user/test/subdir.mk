################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/test/test.c 

OBJS += \
./user/test/test.o 

C_DEPS += \
./user/test/test.d 


# Each subdirectory must supply rules for building sources it contributes
user/test/%.o user/test/%.su user/test/%.cyclo: ../user/test/%.c user/test/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/user/test" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-user-2f-test

clean-user-2f-test:
	-$(RM) ./user/test/test.cyclo ./user/test/test.d ./user/test/test.o ./user/test/test.su

.PHONY: clean-user-2f-test

