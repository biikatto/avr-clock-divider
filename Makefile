# Target
TARGET=clock_divider
# Choose our compiler
CC=avr-gcc
# Specify the microcontroller target
MCU=atmega328p
# Compiler flags
CFLAGS=-g -mmcu=$(MCU) -Wall -Os -c
# Linker flags
LFLAGS=-g -mmcu=$(MCU) -o $(TARGET).out -Wl,-Map,$(TARGET).map
# AVR object copy utility
ACOPY=avr-objcopy
# Copy flags
ACFLAGS=-R .eeprom -O ihex

# AVR utility
AVR=avrdude
# Programmer
PROG=usbtiny
# AVR utility flags
AVRFLAGS=-c $(PROG) -p $(MCU) -U

$(TARGET):
	$(CC) $(CFLAGS) $(TARGET).c
	$(CC) $(LFLAGS) $(TARGET).o
	$(ACOPY) $(AFLAGS) $(TARGET).out $(TARGET).hex

flash: all
	$(AVR) $(AVRFLAGS) flash:w:$(TARGET).hex

all: $(TARGET)
