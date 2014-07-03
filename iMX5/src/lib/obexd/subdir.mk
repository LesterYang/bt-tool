################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/obexd/obexagent.c \
../src/lib/obexd/obexclient.c \
../src/lib/obexd/obexclient_file_transfer.c \
../src/lib/obexd/obexclient_session.c \
../src/lib/obexd/obexclient_transfer.c \
../src/lib/obexd/obexmanager.c \
../src/lib/obexd/obexsession.c \
../src/lib/obexd/obextransfer.c 

OBJS += \
./src/lib/obexd/obexagent.o \
./src/lib/obexd/obexclient.o \
./src/lib/obexd/obexclient_file_transfer.o \
./src/lib/obexd/obexclient_session.o \
./src/lib/obexd/obexclient_transfer.o \
./src/lib/obexd/obexmanager.o \
./src/lib/obexd/obexsession.o \
./src/lib/obexd/obextransfer.o 

C_DEPS += \
./src/lib/obexd/obexagent.d \
./src/lib/obexd/obexclient.d \
./src/lib/obexd/obexclient_file_transfer.d \
./src/lib/obexd/obexclient_session.d \
./src/lib/obexd/obexclient_transfer.d \
./src/lib/obexd/obexmanager.d \
./src/lib/obexd/obexsession.d \
./src/lib/obexd/obextransfer.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/obexd/%.o: ../src/lib/obexd/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	/opt/freescale/usr/local/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-gcc -I/Space/ltib2/ltib/rootfs/usr/include -I/Space/ltib2/ltib/rootfs/usr/include/dbus-1.0 -I"/mnt/hgfs/Win_7/workspace-cpp2/bt-tool/include" -I/Space/ltib2/ltib/rootfs/usr/include/glib-2.0 -I/Space/ltib2/ltib/rootfs/usr/lib/dbus-1.0/include -O0 -g3 -Wall -c -fmessage-length=0  -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


