#include <avr/io.h>
//#define F_CPU 1000000UL  // 1 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h> /*Watchdog timer handling*/

#define OUT_PORT 	PORTD

#define OUT_LAMP 		5
#define OUT_STRONG		4
#define OUT_MID			3
#define OUT_WEAK		2

#define IN_LAMP 		0
#define IN_STRONG		1
#define IN_MID			2
#define IN_WEAK			3
#define BUTT			6


int main(void)            
{

	// PORTD -> Output -> LOW LEVEL
	DDRD |= (1<<OUT_WEAK | 1<<OUT_MID | 1<<OUT_STRONG | 1<<OUT_LAMP);		
	PORTD = 0x00;

	
	DDRB |= (1<<BUTT);
	

    while(1) {              
		//wdt_reset();

		// Pins for buttons set is 0 in Input mode
		DDRB &= ~(1<<IN_LAMP | 1<<IN_STRONG | 1<<IN_MID | 1<<IN_WEAK);
		PORTB &= ~(1<<IN_LAMP | 1<<IN_STRONG | 1<<IN_MID | 1<<IN_WEAK);
		
		// Pin for BUTT set is 1 in Output mode
		PORTB |= (1<<BUTT);

		_delay_ms(2);

		// Read pin of LAMP
		if(PINB & (1<<IN_LAMP)) {
			_delay_ms(25);
			while(PINB & (1<<IN_LAMP));
			PORTD ^= (1<< OUT_LAMP);
		}
		
		// Read pins of motor
		if(PINB & (1<<IN_STRONG)) {
			_delay_ms(25);
			while(PINB & (1<<IN_STRONG));
			PORTD &= ~(1<<OUT_MID);
			PORTD &= ~(1<<OUT_WEAK);
			_delay_ms(20);
			PORTD ^= (1<< OUT_STRONG);
		}

		if(PINB & (1<<IN_MID)) {
			_delay_ms(25);
			while(PINB & (1<<IN_MID));
			PORTD &= ~(1<<OUT_STRONG);
			PORTD &= ~(1<<OUT_WEAK);
			_delay_ms(20);
			PORTD ^= (1<< OUT_MID);
		}

		if(PINB & (1<<IN_WEAK)) {
			_delay_ms(25);
			while(PINB & (1<<IN_WEAK));
			PORTD &= ~(1<<OUT_MID);
			PORTD &= ~(1<<OUT_STRONG);
			_delay_ms(20);
			PORTD ^= (1<< OUT_WEAK);
		}
	

		// Operating to LED 
		if(PIND & (1<<OUT_LAMP)) {
			DDRB |= (1<<IN_LAMP);
			PORTB &= ~(1<<BUTT);
			PORTB |= (1<<IN_LAMP);		
		}

		if(PIND & (1<<OUT_STRONG)) {
			DDRB |= (1<<IN_STRONG);
			PORTB &= ~(1<<BUTT);
			PORTB |= (1<<IN_STRONG);		
		}

		if(PIND & (1<<OUT_MID)) {
			DDRB |= (1<<IN_MID);
			PORTB &= ~(1<<BUTT);
			PORTB |= (1<<IN_MID);		
		}

		if(PIND & (1<<OUT_WEAK)) {
			DDRB |= (1<<IN_WEAK);
			PORTB &= ~(1<<BUTT);
			PORTB |= (1<<IN_WEAK);		
		}
		
		_delay_ms(100);
	
	}
	
		
} 
