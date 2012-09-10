#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 1000000UL
#endif 
#include <util/delay.h>
#include "USI_TWI_Master.h"
#include "USI_TWI_Master.c"

#define HMC_READ_ADDRESS 0x3D 
#define HMC_WRITE_ADDRESS 0x3C 

// register addresses
#define HMC_REG_CONF_A 0x00
#define HMC_REG_CONF_B 0x01
#define HMC_REG_MODE 0x02
#define HMC_REG_X1 0x03 // registers 1 and 2 are MSB and LSB, respectively
#define HMC_REG_X2 0x04
#define HMC_REG_Z1 0x05
#define HMC_REG_Z2 0x06
#define HMC_REG_Y1 0x07
#define HMC_REG_Y2 0x08
#define HMC_REG_STATUS 0x09
#define HMC_REG_ID_A 0x0A
#define HMC_REG_ID_B 0x0B
#define HMC_REG_ID_C 0x0C
unsigned char buffer[8];

//function prototypes
void debug_LED(void);
void blinkOutput(char[], int, int);

int main(void) {
	DDRD |= _BV(PD5) | _BV(PD4);
	PORTD &= ~(_BV(PD5) | _BV(PD4));
	_delay_ms(200);
	USI_TWI_Master_Initialise();

	debug_LED();
	
	buffer[0] = (char) HMC_WRITE_ADDRESS;
	buffer[1] = (char) HMC_REG_MODE;
	buffer[2] = (char) 0x00;
	char success;
	success = USI_TWI_Start_Read_Write(buffer, 3);

	//if (success == 0) { // escapes if transmission failed
	//	return 0;
	//}

	debug_LED();
	
	// blinkOutput(buffer, 2, 3);

	return 0;
}

void blinkOutput(char buffer[], int msgStart, int msgLength) {
	// blink both for a while to show we're about to output the data
	PORTD |= _BV(PD5) | _BV(PD4);
	_delay_ms(700);
	PORTD &= ~(_BV(PD4) | _BV(PD5));
	_delay_ms(300);
	int i,j;
	for (i = msgStart; i < msgLength; i++) {
		for (j = 0; j < buffer[i]; j++) {
			PORTD |= _BV(PD5);
			_delay_ms(100);
			PORTD &= ~_BV(PD5);
			_delay_ms(100);
		}	
		// blink red LED to show we're going for the next buffer cell
		PORTD |= _BV(PD4);
		_delay_ms(700);
		PORTD &= ~_BV(PD4);
		_delay_ms(300);
	}
	// blink both again to show we're done.
	PORTD |= _BV(PD5) | _BV(PD4);
	_delay_ms(700);
	PORTD &= ~(_BV(PD4) | _BV(PD5));


}

void debug_LED() {

	int error = USI_TWI_Get_State_Info();
	if (error != 0) {
		// illuminate error light.
		int i;
		for (i = 0; i < error; i++) {
			PORTD ^= _BV(PD4);
			_delay_ms(300);
			PORTD ^= _BV(PD4);
			_delay_ms(200);
		}
	}	
	else {
		// illuminate "OK" light.
		PORTD |= _BV(PD5);
		_delay_ms(300);
		PORTD &= ~_BV(PD5);
	}
}



