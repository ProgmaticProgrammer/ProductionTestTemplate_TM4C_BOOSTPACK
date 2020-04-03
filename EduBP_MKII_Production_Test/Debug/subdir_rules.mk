################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
EduBP_MKII_Production_Test.cpp: ../EduBP_MKII_Production_Test.ino
	@echo 'Building file: "$<"'
	@echo 'Invoking: Resource Custom Build Step'
	
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ./%.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/Users/Owner/AppData/Local/Energia15/packages/energia/tools/arm-none-eabi-gcc/6.3.1-20170620/bin/arm-none-eabi-gcc-6.3.1.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Dprintf=iprintf -DF_CPU=80000000L -DENERGIA_EK_TM4C123GXL -DENERGIA_ARCH_TIVAC -DENERGIA=23 -DARDUINO=10610 -I"C:/Users/Owner/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/system/driverlib" -I"C:/Users/Owner/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/system/inc" -I"C:/Users/Owner/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/system" -I"C:/Users/Owner/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/cores/tivac" -I"C:/Users/Owner/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/variants/EK-TM4C123GXL" -I"C:/Users/Owner/workspace_v9/EduBP_MKII_Production_Test" -I"C:/Users/Owner/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/libraries/Wire" -I"C:/Users/Owner/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/libraries/SPI" -I"C:/ti/energia-1.8.10E23/libraries/Adafruit_TMP006" -I"C:/ti/energia-1.8.10E23/libraries/OPT3001" -I"C:/Users/Owner/AppData/Local/Energia15/packages/energia/hardware/tivac/1.0.3/libraries/EduBPMKII_Screen" -I"C:/Users/Owner/AppData/Local/Energia15/packages/energia/tools/arm-none-eabi-gcc/6.3.1-20170620/arm-none-eabi/include" -Os -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -w -Wall --param max-inline-insns-single=500 -mabi=aapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -std=gnu++11 -fno-rtti -fno-threadsafe-statics -fno-exceptions $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


