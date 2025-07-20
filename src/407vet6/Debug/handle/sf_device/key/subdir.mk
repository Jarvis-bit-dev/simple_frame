################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../handle/sf_device/key/key.c 

OBJS += \
./handle/sf_device/key/key.o 

C_DEPS += \
./handle/sf_device/key/key.d 


# Each subdirectory must supply rules for building sources it contributes
handle/sf_device/key/%.o handle/sf_device/key/%.su handle/sf_device/key/%.cyclo: ../handle/sf_device/key/%.c handle/sf_device/key/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_app" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_ctl" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_device" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_driver" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_third_party" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_utils" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/test" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_scheduler" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_shell" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_protocol" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_log" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_err" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_device/key" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-handle-2f-sf_device-2f-key

clean-handle-2f-sf_device-2f-key:
	-$(RM) ./handle/sf_device/key/key.cyclo ./handle/sf_device/key/key.d ./handle/sf_device/key/key.o ./handle/sf_device/key/key.su

.PHONY: clean-handle-2f-sf_device-2f-key

