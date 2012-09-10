#include <avr/io.h>
#include <util/delay.h>
#ifndef F_CPU
#define F_CPU 50000000UL
#endif 
char reversed;
short delay = 5;


int main(void) {
	reversed = 0;
	int i;
	// define pd4 as output
	DDRD |= (1 << PD4);
	DDRD |= (1 << PD5);
	PORTD |= (1 << PD5);
	while (1) {
		PORTD ^= (1 << PD5);    // switch on
		_delay_ms(1);
		PORTD ^= (1 << PD5);
		for (i = 0; i < delay; i++) {
			_delay_ms(1);
		}
		PORTD ^= (1 << PD5);    // switch off
 		_delay_ms(1);
		PORTD ^= (1 << PD5);
		//for (i = 0; i < delay; i++) {
		//	_delay_ms(1);
		//}

		handleDelay();
		
	}
	return 0;
}

void handleDelay() {
	if ((delay < 1) || (delay > 20)) {
		reversed ^= 0x0F;
	}
	if ((reversed & 0x0F) == 0)
		delay++;
	else delay--;
		
}

