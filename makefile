#AVR Makefile
# James Stockton


# make file commands
#	all 	- compiles whole program
#	master	- compiles master node program
#	disasm 	- disassembles elf file
#	size 	- shows size of elf file
#	flash	- upload hex to target
#	flash-master	- upload master program
#	fuse	- set fuses of target
#	test	- test programmer connection
#	comms	- python comms script
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
TEST = test

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

#external python scripts
PYTHON = python
SCRIPTS = scripts
COMMS = main.py
BUSMONITOR = bus-monitor.py
SERIAL = COM8



all: $(BUILD)/$(TARGET).hex

master: $(BUILD)/$(TEST).hex

disasm: $(BUILD)/$(TARGET).elf
	$(OBJDUMP) -d $(BUILD)/$(TARGET).elf

size: $(BUILD)/$(TARGET).elf
	$(OBJSIZE) -C $(BUILD)/$(TARGET).elf


flash: all
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -U flash:w:$(BUILD)/$(TARGET).hex

flash-master: master
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -U flash:w:$(BUILD)/$(TEST).hex

fuse:
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -U lfuse:w:$(LF):m -U hfuse:w:$(HF):m -U efuse:w:$(EF):m

test:
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU)


comms:
	$(PYTHON) $(SCRIPTS)/$(COMMS) $(SERIAL)

monitor:
	$(PYTHON) $(SCRIPTS)/$(BUSMONITOR) $(SERIAL)


clean:
	rm -f $(BUILD)/$(TARGET).elf
	rm -f $(BUILD)/$(TARGET).hex
	rm -f $(BUILD)/$(TEST).elf
	rm -f $(BUILD)/$(TEST).hex


$(BUILD)/$(TARGET).elf: $(TARGET).c $(INCLUDES)
	$(CC) -DF_CPU=$(CLK) -mmcu=$(MCU) $(CFLAGS) $(TARGET).c $(INCLUDES) -o $(BUILD)/$(TARGET).elf

$(BUILD)/$(TARGET).hex: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).hex -O ihex


$(BUILD)/$(TEST).elf: $(TEST).c $(INCLUDES)
	$(CC) -DF_CPU=$(CLK) -mmcu=$(MCU) $(CFLAGS) $(TEST).c $(INCLUDES) -o $(BUILD)/$(TEST).elf

$(BUILD)/$(TEST).hex: $(BUILD)/$(TEST).elf
	$(OBJCOPY) $(BUILD)/$(TEST).elf $(BUILD)/$(TEST).hex -O ihex