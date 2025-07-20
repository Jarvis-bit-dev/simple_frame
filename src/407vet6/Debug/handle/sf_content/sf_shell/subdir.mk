################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../handle/sf_content/sf_shell/function_register.c \
../handle/sf_content/sf_shell/shell_logic.c \
../handle/sf_content/sf_shell/var_register.c 

OBJS += \
./handle/sf_content/sf_shell/function_register.o \
./handle/sf_content/sf_shell/shell_logic.o \
./handle/sf_content/sf_shell/var_register.o 

C_DEPS += \
./handle/sf_content/sf_shell/function_register.d \
./handle/sf_content/sf_shell/shell_logic.d \
./handle/sf_content/sf_shell/var_register.d 


# Each subdirectory must supply rules for building sources it contributes
handle/sf_content/sf_shell/%.o handle/sf_content/sf_shell/%.su handle/sf_content/sf_shell/%.cyclo: ../handle/sf_content/sf_shell/%.c handle/sf_content/sf_shell/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_app" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_ctl" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_device" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_driver" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_third_party" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_utils" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/test" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_scheduler" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_shell" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_protocol" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_log" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_content/sf_err" -I"C:/Users/Jarvis/Desktop/simple_frame/src/407vet6/handle/sf_device/key" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-handle-2f-sf_content-2f-sf_shell

clean-handle-2f-sf_content-2f-sf_shell:
	-$(RM) ./handle/sf_content/sf_shell/function_register.cyclo ./handle/sf_content/sf_shell/function_register.d ./handle/sf_content/sf_shell/function_register.o ./handle/sf_content/sf_shell/function_register.su ./handle/sf_content/sf_shell/shell_logic.cyclo ./handle/sf_content/sf_shell/shell_logic.d ./handle/sf_content/sf_shell/shell_logic.o ./handle/sf_content/sf_shell/shell_logic.su ./handle/sf_content/sf_shell/var_register.cyclo ./handle/sf_content/sf_shell/var_register.d ./handle/sf_content/sf_shell/var_register.o ./handle/sf_content/sf_shell/var_register.su

.PHONY: clean-handle-2f-sf_content-2f-sf_shell

