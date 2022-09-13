/*
 * main.c
 *
 *  Created on: Sep 10, 2022
 *      Author: Omar Anwar
 */
#include "Functions.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uc_4t sec = 0;
uc_4t min = 0;
uc_4t hrs = 0;

ISR(TIMER1_COMPA_vect){
	/*
	 * For System Clock = 1Mhz and prescaler F_CPU/1024.
	 * Timer frequency will be around 977hz, Ttimer = 1.024ms
	 * For compare value equals to 977 the timer will generate compare match interrupt every 1 second.
	 * Compare interrupt will be generated every 1 second, so we count a second every interrupt.
	 */
	sec++;
	if (sec == 60) {
		sec = 0;
		min++;
	}
	if (min == 60) {
		sec = 0;
		min = 0;
		hrs++;
	}
	if (hrs == 12) {
		sec = 0;
		min = 0;
		hrs = 0;
	}

}

ISR (INT0_vect){
	//	Reset Interrupt
	sec = 0;
	min = 0;
	hrs = 0;
}

ISR (INT1_vect){
	// Pause Interrupt
	TIMSK &= ~(1<<OCIE1A);  // Disable Timer1 interrupt to avoid counting seconds.
}

ISR (INT2_vect){
	// Resume Interrupt
	TIMSK |= (1<<OCIE1A); // Enable Timer1 interrupt to continue counting.
}

int main(void){
/* Components Initializations:
 * 1. Timer1 interrupt compare mode.
 * 2. 6 7-Segments.
 * 3. Push button on PD2 with the internal pull-up resistor is configured External Interrupt INT0 with falling edge.
 * (Stop Watch time Reset)
 * 4. Push button on PD3 with the external pull-down resistor is configured External Interrupt INT1 with rising edge.
 * (Stop Watch time Pause)
 * 5. Push button on PB2 with the internal pull-up resistor is configured External Interrupt INT2 with falling edge.
 * (Stop Watch time Resume)
 */
	TIMER1_INIT_CTC_MODE();  // --> 1
	SEGMENTS_INIT(); // --> 2
	RESET_PUSH_BUTTON_INT0(); // --> 3
	PAUSE_PUSH_BUTTON_INT1(); // --> 4
	RESUME_PUSH_BUTTON_INT2(); // --> 5

	while(1){

		PORTA = (1<<0); // choose First 7-segment to display.
		DISPLAY(sec % 10); // First digit in seconds counter.
		_delay_ms(3);

		PORTA = (1<<1); // choose Second 7-segment to display.
		DISPLAY(sec / 10); // Second digit in seconds counter.
		_delay_ms(3);

		PORTA = (1<<2); // choose Third 7-segment to display.
		DISPLAY(min % 10); // First digit in minutes counter.
		_delay_ms(3);

		PORTA = (1<<3); // choose Fourth 7-segment to display.
		DISPLAY(min / 10); // Second digit in minutes counter.
		_delay_ms(3);

		PORTA = (1<<4); // choose Fifth 7-segment to display.
		DISPLAY(hrs % 10); // First digit in hours counter.
		_delay_ms(3);

		PORTA = (1<<5); // choose Sixth 7-segment to display.
		DISPLAY(hrs / 10); // Second digit in hours counter.
		_delay_ms(3);

	}
}




