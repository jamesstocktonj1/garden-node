#AVR Makefile
# James Stockton


# make file commands
#	all 	- compiles whole program
#	disasm 	- disassembles elf file
#	size 	- shows size of elf file
#	flash	- upload hex to target
#	fuse	- set fuses of target
#	clean	- deletes compiled files

# avr constants
MCU = atmega168
CLK = 8000000

# compiler constants
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
OBJSIZE = avr-size

# compiler flags
CFLAGS = -Wall -Os
#CFLAGS = -Wall -Os- Wl -u vfprintf -lprintf_flt -lm
TARGET = main

# build and source folders
BUILD = build
SOURCE = src
INCLUDES = $(wildcard $(SOURCE)/*.c)

# programmer constant
AVRDUDE = avrdude 
PROGRAMMER = usbasp

# fuses
LF = 0xe2
HF = 0xdf
EF = 0xf9



all: $(BUILD)/$(TARGET).hex

disasm: $(BUILD)/$(TARGET).elf
	$(OBJDUMP) -d $(BUILD)/$(TARGET).elf

size: $(BUILD)/$(TARGET).elf
	$(OBJSIZE) -C $(BUILD)/$(TARGET).elf

flash: all
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -U flash:w:$(BUILD)/$(TARGET).hex

fuse:
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -U lfuse:w:$(LF):m -U hfuse:w:$(HF):m -U efuse:w:$(EF):m

clean:
	rm -f $(BUILD)/$(TARGET).elf
	rm -f $(BUILD)/$(TARGET).hex


$(BUILD)/$(TARGET).elf: $(TARGET).c $(INCLUDES)
	$(CC) -DF_CPU=$(CLK) -mmcu=$(MCU) $(CFLAGS) $(TARGET).c $(INCLUDES) -o $(BUILD)/$(TARGET).elf

$(BUILD)/$(TARGET).hex: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).hex -O ihex