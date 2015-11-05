/*
 *  Written in AVR Studio 5 / AVR Studio 6
 *  Compiler: AVR GNU C Compiler (GCC)
 *
 *  Author: AVR Tutorials
 *  Website: www.AVR-Tutorials.com
*/
 
#include <avr/io.h>
#include <avr/interrupt.h>
 
#define F_CPU 4000000UL
#include <util/delay.h>

int count;

// Interrupt Service Routine for external interrupt 0 (pin 4 on 328p)
ISR(INT0_vect){
    // flip the bits that need to be flipped on this iteration
    PORTB ^= 1;                  // 0b00000001
    if(count%2) PORTB ^= 1<<1;   // 0b00000010
    if(count%3) PORTB ^= 1<<2;   // 0b00000100
    if(count%4) PORTB ^= 1<<3;   // 0b00001000
    if(count%5) PORTB ^= 1<<4;   // 0b00010000
    if(count%6) PORTB ^= 1<<5;   // 0b00100000
    if(count%7) PORTB ^= 1<<6;   // 0b01000000

    count++;
    count %= 420; // our least common multiple
}

int main(void)
{
    DDRB = 0x80; // set all pins on port b except b7 to output; 0b01111111

	DDRD = 1<<PD2;		// Set PD2 as input (Using for interupt INT0)
	PORTD = 1<<PD2;		// Enable PD2 pull-up resistor
 
    EICRA |= 1<<ISC00 | 1<<ISC01; // Set interrupt 0 to trigger on rising edge
    EIMSK |= 1<<INT0;
 
	sei();				//Enable Global Interrupt
	return(0);
}
