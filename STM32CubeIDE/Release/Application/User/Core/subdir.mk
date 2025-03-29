################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/TouchGFXProjects/App/Core/Src/MB1642ButtonController.cpp 

C_SRCS += \
C:/TouchGFXProjects/App/Core/Src/MB1642DataReader.c \
C:/TouchGFXProjects/App/Core/Src/MB1642DisplayDriver.c \
../Application/User/Core/clovece_nezlob_se.c \
C:/TouchGFXProjects/App/Core/Src/main.c \
../Application/User/Core/milis.c \
C:/TouchGFXProjects/App/Core/Src/stm32g0xx_hal_msp.c \
C:/TouchGFXProjects/App/Core/Src/stm32g0xx_it.c \
../Application/User/Core/syscalls.c \
../Application/User/Core/sysmem.c \
../Application/User/Core/ws2812b.c 

C_DEPS += \
./Application/User/Core/MB1642DataReader.d \
./Application/User/Core/MB1642DisplayDriver.d \
./Application/User/Core/clovece_nezlob_se.d \
./Application/User/Core/main.d \
./Application/User/Core/milis.d \
./Application/User/Core/stm32g0xx_hal_msp.d \
./Application/User/Core/stm32g0xx_it.d \
./Application/User/Core/syscalls.d \
./Application/User/Core/sysmem.d \
./Application/User/Core/ws2812b.d 

OBJS += \
./Application/User/Core/MB1642ButtonController.o \
./Application/User/Core/MB1642DataReader.o \
./Application/User/Core/MB1642DisplayDriver.o \
./Application/User/Core/clovece_nezlob_se.o \
./Application/User/Core/main.o \
./Application/User/Core/milis.o \
./Application/User/Core/stm32g0xx_hal_msp.o \
./Application/User/Core/stm32g0xx_it.o \
./Application/User/Core/syscalls.o \
./Application/User/Core/sysmem.o \
./Application/User/Core/ws2812b.o 

CPP_DEPS += \
./Application/User/Core/MB1642ButtonController.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/MB1642ButtonController.o: C:/TouchGFXProjects/App/Core/Src/MB1642ButtonController.cpp Application/User/Core/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Core/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/MB1642DataReader.o: C:/TouchGFXProjects/App/Core/Src/MB1642DataReader.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Core/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/MB1642DisplayDriver.o: C:/TouchGFXProjects/App/Core/Src/MB1642DisplayDriver.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Core/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/%.o Application/User/Core/%.su Application/User/Core/%.cyclo: ../Application/User/Core/%.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Core/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/main.o: C:/TouchGFXProjects/App/Core/Src/main.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Core/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/stm32g0xx_hal_msp.o: C:/TouchGFXProjects/App/Core/Src/stm32g0xx_hal_msp.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Core/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/stm32g0xx_it.o: C:/TouchGFXProjects/App/Core/Src/stm32g0xx_it.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Core/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc -I../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Core

clean-Application-2f-User-2f-Core:
	-$(RM) ./Application/User/Core/MB1642ButtonController.cyclo ./Application/User/Core/MB1642ButtonController.d ./Application/User/Core/MB1642ButtonController.o ./Application/User/Core/MB1642ButtonController.su ./Application/User/Core/MB1642DataReader.cyclo ./Application/User/Core/MB1642DataReader.d ./Application/User/Core/MB1642DataReader.o ./Application/User/Core/MB1642DataReader.su ./Application/User/Core/MB1642DisplayDriver.cyclo ./Application/User/Core/MB1642DisplayDriver.d ./Application/User/Core/MB1642DisplayDriver.o ./Application/User/Core/MB1642DisplayDriver.su ./Application/User/Core/clovece_nezlob_se.cyclo ./Application/User/Core/clovece_nezlob_se.d ./Application/User/Core/clovece_nezlob_se.o ./Application/User/Core/clovece_nezlob_se.su ./Application/User/Core/main.cyclo ./Application/User/Core/main.d ./Application/User/Core/main.o ./Application/User/Core/main.su ./Application/User/Core/milis.cyclo ./Application/User/Core/milis.d ./Application/User/Core/milis.o ./Application/User/Core/milis.su ./Application/User/Core/stm32g0xx_hal_msp.cyclo ./Application/User/Core/stm32g0xx_hal_msp.d ./Application/User/Core/stm32g0xx_hal_msp.o ./Application/User/Core/stm32g0xx_hal_msp.su ./Application/User/Core/stm32g0xx_it.cyclo ./Application/User/Core/stm32g0xx_it.d ./Application/User/Core/stm32g0xx_it.o ./Application/User/Core/stm32g0xx_it.su ./Application/User/Core/syscalls.cyclo ./Application/User/Core/syscalls.d ./Application/User/Core/syscalls.o ./Application/User/Core/syscalls.su ./Application/User/Core/sysmem.cyclo ./Application/User/Core/sysmem.d ./Application/User/Core/sysmem.o ./Application/User/Core/sysmem.su ./Application/User/Core/ws2812b.cyclo ./Application/User/Core/ws2812b.d ./Application/User/Core/ws2812b.o ./Application/User/Core/ws2812b.su

.PHONY: clean-Application-2f-User-2f-Core

