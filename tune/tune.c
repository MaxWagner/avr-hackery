#include <avr/io.h>
#include <util/delay.h>
#ifndef F_CPU
#define F_CPU 8000000UL
#endif 
char reversed;
char delay = 5;
char i;
char j;

int main(void) {
	reversed = 0;
	DDRD |= (1 << PD4);
	DDRD |= (1 << PD5);
	while (1) {
		_delay_ms(100);
		delay = 30;
		playHalfASecond();
		_delay_ms(100);
		delay = 15;
		playHalfASecond();
		_delay_ms(100);
		delay = 10;
		playHalfASecond();
		_delay_ms(100);
		delay = 6;
		playHalfASecond();
		_delay_ms(100);
		delay = 5;
		playHalfASecond();
		_delay_ms(100);
		delay = 2;
		playHalfASecond();
	}
	return 0;
}

void playHalfASecond() {
	PORTD |= (1 << PD5);
	PORTD &= ~(1 << PD4);
	for (i = 0; i < (500 - 2) / (2 * delay); i++) {
		PORTD ^= (1 << PD5);    // switch on
		PORTD ^= (1 << PD4);
		
		_delay_ms(1);

		PORTD ^= (1 << PD5);    // switch on
		PORTD ^= (1 << PD4);

		for (j = 0; j < delay; j++) {
			_delay_ms(1);
		}
		PORTD ^= (1 << PD5);    // switch off
		PORTD ^= (1 << PD4);

		_delay_ms(1);

		PORTD ^= (1 << PD5);    // switch on
		PORTD ^= (1 << PD4);

		for (j = 0; j < delay; j++) {
			_delay_ms(1);
		}

		PORTD ^= (1 << PD5);    // switch off
		PORTD ^= (1 << PD4);

		_delay_ms(1);

		PORTD ^= (1 << PD5);    // switch on
		PORTD ^= (1 << PD4);
	}
	PORTD &= ~(1 << PD4);
	PORTD &= ~(1 << PD5);
}

