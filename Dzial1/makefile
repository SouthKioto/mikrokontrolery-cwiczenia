MCU   = atmega328p
F_CPU = 16000000UL
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra

all: build/main.hex

build/main.elf: src/main.c
	mkdir -p build
	avr-gcc $(CFLAGS) $< -o $@

build/main.hex: build/main.elf
	avr-objcopy -O ihex -R .eeprom $< $@

clean:
	rm -rf build

.PHONY: all clean
