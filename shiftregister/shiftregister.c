#include <avr/io.h>
#include <util/delay.h>
#ifndef F_CPU
#define F_CPU 5000000UL
#endif 

// define more useful names
#define G _BV(PD1)
#define RCK _BV(PD2)
#define SCK _BV(PD3)
#define SI _BV(PD4)
#define SCLR _BV(PD5)
#define OUT PORTD

void clear();
void disableOutputs();
void enableOutputs();
void writeByteToRegister(char byte);
void writeCharacterToRegister(char character);
void shortBlank();

int main(void) {

    // Ports:
    //    PD1 ====== ~G (output disable)
    //  | PD2 ====== RCK (register clock)
    //  | PD3 ====== SCK (device clock) 
    //    PD4 ====== SI (serial input) 
    //    PD5 ====== ~SCLR (register clear)

    // declare PD2-5 as outputs
    DDRD |= G | RCK | SCK | SI | SCLR;
    
    clear();

    while (1) {
        writeByteToRegister((char) 0x00);
        _delay_ms(250);
        writeByteToRegister((char) 0x40);
        _delay_ms(250);
        writeByteToRegister((char) 0x80);
        _delay_ms(250);
    }

    // write some actual text to display
    while (0) {
        writeCharacterToRegister(' ');
        _delay_ms(400);

        writeCharacterToRegister('t');
        _delay_ms(400);
        shortBlank();

        writeCharacterToRegister('r');
        _delay_ms(400);
        shortBlank();

        writeCharacterToRegister('o');
        _delay_ms(400);
        shortBlank();

        writeCharacterToRegister('l');
        _delay_ms(400);
        shortBlank();

        writeCharacterToRegister('l');
        _delay_ms(400);
    }

    int i = 0; // code for testing display
    while (0) {
        for (i = 0; i < 8; i++) {
	    writeByteToRegister((char) (1 << i));
	    _delay_ms(900);
        }
    }

    return 0;
}

void shortBlank() {
    writeByteToRegister((char) 0x00);
    _delay_ms(100);
}

void writeCharacterToRegister(char character) {
    char output;
    switch (character) {
	case '!':
	    output = (char) 0xFF;
	    break;
	case 'A':
	    output = (char) 0xEB;
	    break;
	case 'B':
	    output = (char) 0xB3;
	    break;
	case 'C':
	    output = (char) 0xF0;
	    break;
	case 'L':
	    output = (char) 0xB0; 
	    break;
	case 'O':
	    output = (char) 0xFA;
	    break;


	case 'l':
	    output = (char) 0x0A;
	    break;
	case 'o':
	    output = (char) 0x33;
	    break;
	case 'r':
	    output = (char) 0x21;
	    break;
	case 't':
	    output = (char) 0xB1;
	    break;


	case ' ':
	    output = (char) 0x00;
	    break;
	default:
	    output = (char) 0xFF;
	    break;
    }

    writeByteToRegister(output);

}

void writeByteToRegister(char byte) {
    // clear();
    
    // pull SCK line high
    OUT &= ~SCK;
    // set RCK line low
    OUT |= RCK;

    int digit;
    for (digit = 0; digit < 8; digit++) {
        // write bit to register
	
	// set SI line accordingly
	if (((int) byte & (1 << digit)) == 0) {
	    // pull SI line low
	    OUT &= ~SI;
	}
	else {
	    OUT |= SI;
	}
	// toggle clock lines, thereby writing to register
	OUT ^= SCK | RCK;
	// toggle lines again to get ready for the next write operation
	OUT ^= SCK | RCK;
    }

}

void enableOutputs() {
    // the G line, so we need to pull this down to enable outputs
    OUT &= ~G;
}

void disableOutputs() {
    // the G line, so we need to pull this up to disable outputs
    OUT |= G;
}

void clear() {
    // the SCLR line. we pull down and then up again to clear the register
    OUT &= ~SCLR;
    _delay_ms(4);
    OUT |= SCLR;
}




