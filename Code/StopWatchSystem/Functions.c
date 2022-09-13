/*
 * Functions.c
 *
 *  Created on: Sep 10, 2022
 *      Author: Omar Anwar
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Functions.h"


void TIMER1_INIT_CTC_MODE (void){
	/*** Timer1 configurations
	 * 1. Non PWM
	 * 2. Toggle OC1A on compare match
	 * 3. CTC (Timer1 Compare Mode).
	 * 4. Prescaler = 1024.
	 ***/

	TCCR1A = (1<<COM1A0) | (1<<FOC1A);
	TCCR1B = (1<<CS10) | (1<<CS12) | (1<<WGM12);


	TCNT1 = 0; // Timer1 Initial value.

	OCR1A = 977; //Set Timer1 compare value.

	/*** Enable interrupts.
	 * 1. Activate I-bit SREG (7)
	 * 2. Activate MIE TIMSK (OCIE1A)
	 */

	SREG = (1<<7); // I-bit Activated
	TIMSK |= (1<<OCIE1A);

}

void SEGMENTS_INIT (void){
	DDRC = (DDRC & 0XF0) | 0X0F;
	/*
	 * Common anode 7-segment acts high with logic low (0).
	 */
	PORTC = PORTC & 0XF0;
	DDRA = 0x3F;

	PORTA = 0xff;


}

void DISPLAY (uc_4t number){

	PORTC = number;
}

void RESET_PUSH_BUTTON_INT0 (void){
	DDRD &= ~(1<<PD2);
	PORTD |= (1<<PD2);  // Activate internal pull-up resistor.

	MCUCR |= (1<<ISC01); //The falling edge of INT0 generates an interrupt request.

	GICR |= (1<<INT0); //External Interrupt Request 0 Enable.
}

void PAUSE_PUSH_BUTTON_INT1 (void){
	DDRD &= ~(1<<PD3);

	MCUCR |= (1<<ISC10) | (1<<ISC11); //The rising edge of INT1 generates an interrupt request.

	GICR |= (1<<INT1); //External Interrupt Request 1 Enable.

}

void RESUME_PUSH_BUTTON_INT2 (void){
	DDRB &= ~(1<<PB2);
	PORTB |= (1<<PB2);  // Activate internal pull-up resistor.

	MCUCSR &= ~(1<<ISC2); //The falling edge of INT0 generates an interrupt request.

	GICR |= (1<<INT2); //External Interrupt Request 0 Enable.
}

