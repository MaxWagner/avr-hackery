MCU=attiny2313
AVRDUDEMCU=t2313
CC=/usr/bin/avr-gcc
CFLAGS=-g -Os -Wall -mcall-prologues -mmcu=$(MCU)
OBJ2HEX=/usr/bin/avr-objcopy
AVRDUDE=/usr/bin/avrdude
TARGET=circle

program : $(TARGET).hex
	$(AVRDUDE) -c usbtiny -B 3 -p $(AVRDUDEMCU) -U flash:w:$(TARGET).hex

%.obj : %.o
	$(CC) $(CFLAGS) $< -o $@

%.hex : %.obj
	$(OBJ2HEX) -R .eeprom -O ihex -R .fuse -R .lock $< $@

clean :
	rm -f *.hex *.obj *.o
