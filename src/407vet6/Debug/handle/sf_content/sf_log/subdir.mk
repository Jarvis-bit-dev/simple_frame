################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../handle/sf_content/sf_log/sf_log.c 

OBJS += \
./handle/sf_content/sf_log/sf_log.o 

C_DEPS += \
./handle/sf_content/sf_log/sf_log.d 


# Each subdirectory must supply rules for building sources it contributes
handle/sf_content/sf_log/%.o handle/sf_content/sf_log/%.su handle/sf_content/sf_log/%.cyclo: ../handle/sf_content/sf_log/%.c handle/sf_content/sf_log/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_app" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_ctl" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_device" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_driver" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_third_party" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_utils" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/test" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_scheduler" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_shell" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_protocol" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_log" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-handle-2f-sf_content-2f-sf_log

clean-handle-2f-sf_content-2f-sf_log:
	-$(RM) ./handle/sf_content/sf_log/sf_log.cyclo ./handle/sf_content/sf_log/sf_log.d ./handle/sf_content/sf_log/sf_log.o ./handle/sf_content/sf_log/sf_log.su

.PHONY: clean-handle-2f-sf_content-2f-sf_log

