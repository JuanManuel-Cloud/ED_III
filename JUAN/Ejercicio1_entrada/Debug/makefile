################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Ejercicio1_entrada.axf

# Tool invocations
Ejercicio1_entrada.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/juanmagil/MEGA/Facultad/ED3/ED_III/JUAN/CMSISv2p00_LPC17xx/Debug" -Xlinker -Map="Ejercicio1_entrada.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "Ejercicio1_entrada_Debug.ld" -o "Ejercicio1_entrada.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Ejercicio1_entrada.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Ejercicio1_entrada.axf"; # arm-none-eabi-objcopy -v -O binary "Ejercicio1_entrada.axf" "Ejercicio1_entrada.bin" ; # checksum -p LPC1769 -d "Ejercicio1_entrada.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
