################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bt-adapter.c \
../src/bt-agent.c \
../src/bt-audio.c \
../src/bt-device.c \
../src/bt-input.c \
../src/bt-monitor.c \
../src/bt-network.c \
../src/bt-obex.c \
../src/bt-serial.c \
../src/bt-tool.c \
../src/qsiFunc.c 

OBJS += \
./src/bt-adapter.o \
./src/bt-agent.o \
./src/bt-audio.o \
./src/bt-device.o \
./src/bt-input.o \
./src/bt-monitor.o \
./src/bt-network.o \
./src/bt-obex.o \
./src/bt-serial.o \
./src/bt-tool.o \
./src/qsiFunc.o 

C_DEPS += \
./src/bt-adapter.d \
./src/bt-agent.d \
./src/bt-audio.d \
./src/bt-device.d \
./src/bt-input.d \
./src/bt-monitor.d \
./src/bt-network.d \
./src/bt-obex.d \
./src/bt-serial.d \
./src/bt-tool.d \
./src/qsiFunc.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	/opt/freescale/usr/local/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-gcc -I/Space/ltib2/ltib/rootfs/usr/include -I/Space/ltib2/ltib/rootfs/usr/include/dbus-1.0 -I"/mnt/hgfs/Win_7/workspace-cpp2/bt-tool/include" -I/Space/ltib2/ltib/rootfs/usr/include/glib-2.0 -I/Space/ltib2/ltib/rootfs/usr/lib/dbus-1.0/include -O0 -g3 -Wall -c -fmessage-length=0  -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


