################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/bluez/adapter.c \
../src/lib/bluez/agent.c \
../src/lib/bluez/audio.c \
../src/lib/bluez/device.c \
../src/lib/bluez/input.c \
../src/lib/bluez/manager.c \
../src/lib/bluez/network.c \
../src/lib/bluez/network_server.c \
../src/lib/bluez/serial.c 

OBJS += \
./src/lib/bluez/adapter.o \
./src/lib/bluez/agent.o \
./src/lib/bluez/audio.o \
./src/lib/bluez/device.o \
./src/lib/bluez/input.o \
./src/lib/bluez/manager.o \
./src/lib/bluez/network.o \
./src/lib/bluez/network_server.o \
./src/lib/bluez/serial.o 

C_DEPS += \
./src/lib/bluez/adapter.d \
./src/lib/bluez/agent.d \
./src/lib/bluez/audio.d \
./src/lib/bluez/device.d \
./src/lib/bluez/input.d \
./src/lib/bluez/manager.d \
./src/lib/bluez/network.d \
./src/lib/bluez/network_server.d \
./src/lib/bluez/serial.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/bluez/%.o: ../src/lib/bluez/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	/opt/freescale/usr/local/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-gcc -DHAVE_CONFIG_H -I"/mnt/hgfs/Win_7/workspace-cpp/test-bt-tool/include" -I/Space/ltib2/ltib/rootfs/usr/include -O0 -g3 -Wall -std=gnu99 -c -fmessage-length=0 -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=softfp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


