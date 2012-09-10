#include <avr/io.h>
#include <util/delay.h>
#ifndef F_CPU
#define F_CPU 50000000UL
#endif 
short LED;
char reversed;
short delay = 15;
const char varSpeed = 0;

int main(void) {
	reversed = 0;
	LED = PD1;
	int i;
	// define pd4 as output
	DDRD |= (1 << PD1);
	DDRD |= (1 << PD2);
	DDRD |= (1 << PD3);
	DDRD |= (1 << PD4);
	DDRD |= (1 << PD5);
	while (1) {
		PORTD |= (1 << LED);    // switch on
		for (i = 0; i < delay; i++) {
			_delay_ms(5);
		}
		PORTD &= ~(1 << LED);    // switch off
		nextLED();
 		if (varSpeed == 1) {
			handleDelay();
		}
		
	}
	return 0;
}

void handleDelay() {
	if ((delay < 2) || (delay > 20)) {
		reversed ^= 0x0F;
	}
	if ((reversed & 0x0F) == 0)
		delay++;
	else delay--;
		
}


void nextLED() {
	if ((reversed & 0xF0) == 0) {
		switch (LED) {
		case PD1:
			LED = PD2;
			break;
		case PD2:
			LED = PD3;
			break;
		case PD3:
			LED = PD4;
			break;
		case PD4:
			LED = PD5;
			break;
		case PD5:
			LED = PD4;
			reversed ^= 0xF0;
			break;
		default:
			return;
		}
	}
	else {
		switch (LED) {
		case PD4:
			LED = PD3;
			break;
		case PD3:
			LED = PD2;
			break;

		case PD2:
			LED = PD1;
			break;
		case PD1:
			LED = PD2;
			reversed ^= 0xF0;
			break;
		default:
			return;
		}
	}
}
