################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ConnectionChanel.cpp \
../src/Logic.cpp \
../src/MDSMessage.cpp \
../src/MessageTransmission.cpp \
../src/SlaveManager.cpp \
../src/TransportManager.cpp \
../src/main.cpp 

CPP_DEPS += \
./src/ConnectionChanel.d \
./src/Logic.d \
./src/MDSMessage.d \
./src/MessageTransmission.d \
./src/SlaveManager.d \
./src/TransportManager.d \
./src/main.d 

OBJS += \
./src/ConnectionChanel.o \
./src/Logic.o \
./src/MDSMessage.o \
./src/MessageTransmission.o \
./src/SlaveManager.o \
./src/TransportManager.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/ConnectionChanel.d ./src/ConnectionChanel.o ./src/Logic.d ./src/Logic.o ./src/MDSMessage.d ./src/MDSMessage.o ./src/MessageTransmission.d ./src/MessageTransmission.o ./src/SlaveManager.d ./src/SlaveManager.o ./src/TransportManager.d ./src/TransportManager.o ./src/main.d ./src/main.o

.PHONY: clean-src

