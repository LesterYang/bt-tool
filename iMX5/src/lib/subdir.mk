################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/dbus-common.c \
../src/lib/helpers.c \
../src/lib/marshallers.c \
../src/lib/sdp.c 

OBJS += \
./src/lib/dbus-common.o \
./src/lib/helpers.o \
./src/lib/marshallers.o \
./src/lib/sdp.o 

C_DEPS += \
./src/lib/dbus-common.d \
./src/lib/helpers.d \
./src/lib/marshallers.d \
./src/lib/sdp.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/%.o: ../src/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	/opt/freescale/usr/local/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-gcc -I/Space/ltib2/ltib/rootfs/usr/include -I/Space/ltib2/ltib/rootfs/usr/include/dbus-1.0 -I"/mnt/hgfs/Win_7/workspace-cpp2/bt-tool/include" -I/Space/ltib2/ltib/rootfs/usr/include/glib-2.0 -I/Space/ltib2/ltib/rootfs/usr/lib/dbus-1.0/include -O0 -g3 -Wall -c -fmessage-length=0  -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


