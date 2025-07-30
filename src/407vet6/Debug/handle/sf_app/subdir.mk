################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../handle/sf_app/entry.c 

OBJS += \
./handle/sf_app/entry.o 

C_DEPS += \
./handle/sf_app/entry.d 


# Each subdirectory must supply rules for building sources it contributes
handle/sf_app/%.o handle/sf_app/%.su handle/sf_app/%.cyclo: ../handle/sf_app/%.c handle/sf_app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/proj/simple_frame/src/407vet6/handle" -I"D:/proj/simple_frame/src/407vet6/handle/sf_app" -I"D:/proj/simple_frame/src/407vet6/handle/sf_content" -I"D:/proj/simple_frame/src/407vet6/handle/sf_ctl" -I"D:/proj/simple_frame/src/407vet6/handle/sf_device" -I"D:/proj/simple_frame/src/407vet6/handle/test" -I"D:/proj/simple_frame/src/407vet6/handle/sf_content/sf_scheduler" -I"D:/proj/simple_frame/src/407vet6/handle/sf_content/sf_shell" -I"D:/proj/simple_frame/src/407vet6/handle/sf_content/sf_protocol" -I"D:/proj/simple_frame/src/407vet6/handle/sf_content/sf_log" -I"D:/proj/simple_frame/src/407vet6/handle/sf_content/sf_err" -I"D:/proj/simple_frame/src/407vet6/handle/sf_device/key" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-handle-2f-sf_app

clean-handle-2f-sf_app:
	-$(RM) ./handle/sf_app/entry.cyclo ./handle/sf_app/entry.d ./handle/sf_app/entry.o ./handle/sf_app/entry.su

.PHONY: clean-handle-2f-sf_app

