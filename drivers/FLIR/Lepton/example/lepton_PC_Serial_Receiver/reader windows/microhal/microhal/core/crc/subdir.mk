################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/pawel/Pulpit/microide_test/microide/git/microhal-port-stm32f4xx/microhal/core/crc/crc16.cpp \
/home/pawel/Pulpit/microide_test/microide/git/microhal-port-stm32f4xx/microhal/core/crc/crc7.cpp 

OBJS += \
./microhal/microhal/core/crc/crc16.o \
./microhal/microhal/core/crc/crc7.o 

CPP_DEPS += \
./microhal/microhal/core/crc/crc16.d \
./microhal/microhal/core/crc/crc7.d 


# Each subdirectory must supply rules for building sources it contributes
microhal/microhal/core/crc/crc16.o: /home/pawel/Pulpit/microide_test/microide/git/microhal-port-stm32f4xx/microhal/core/crc/crc16.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -Os -ffunction-sections -fdata-sections -fno-builtin -Wall -Wextra  -g3 $(MICROHAL_CONFIGURATION_DEFINES) -DSTM32F407xx -DHSE_VALUE=8000000 -DSTM32F40_41xxx -DARM_MATH_CM4 -D__MICROHAL -DVENDOR_STMICROELECTRONICS -DMCU_TYPE_STM32F4XX -DMICROHAL_DIAGNOSTIC_LOG_LEVEL=Debug -DMICROHAL_DIAGNOSTIC_TEXT_VISIBLE -D__FPU_PRESENT -D__USES_CXX -DMICROHAL_HOSTCOMM_MAXPACKETSIZE=10000 -I"/home/pawel/Pulpit/microide_test/microide/git/microhal-port-stm32f4xx/third-party/gsl" -I"/home/pawel/Pulpit/microide_test/microide/git/microhal-port-stm32f4xx/components/hostComm/source" -I"/home/pawel/Pulpit/microide_test/microide/git/microhal-port-stm32f4xx/microhal/core" -std=c++1y -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Weffc++ -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

microhal/microhal/core/crc/crc7.o: /home/pawel/Pulpit/microide_test/microide/git/microhal-port-stm32f4xx/microhal/core/crc/crc7.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -Os -ffunction-sections -fdata-sections -fno-builtin -Wall -Wextra  -g3 $(MICROHAL_CONFIGURATION_DEFINES) -DSTM32F407xx -DHSE_VALUE=8000000 -DSTM32F40_41xxx -DARM_MATH_CM4 -D__MICROHAL -DVENDOR_STMICROELECTRONICS -DMCU_TYPE_STM32F4XX -DMICROHAL_DIAGNOSTIC_LOG_LEVEL=Debug -DMICROHAL_DIAGNOSTIC_TEXT_VISIBLE -D__FPU_PRESENT -D__USES_CXX -DMICROHAL_HOSTCOMM_MAXPACKETSIZE=10000 -I"/home/pawel/Pulpit/microide_test/microide/git/microhal-port-stm32f4xx/third-party/gsl" -I"/home/pawel/Pulpit/microide_test/microide/git/microhal-port-stm32f4xx/components/hostComm/source" -I"/home/pawel/Pulpit/microide_test/microide/git/microhal-port-stm32f4xx/microhal/core" -std=c++1y -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Weffc++ -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

