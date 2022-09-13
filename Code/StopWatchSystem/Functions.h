/*
 * Functions.h
 *
 *  Created on: Sep 10, 2022
 *      Author: Omar Anwar
 */
typedef unsigned char uc_4t;

void TIMER1_INIT_CTC_MODE (void);  //Timer1 initialization function prototype.

void SEGMENTS_INIT (void); //7-segments initialization function prototype.

void DISPLAY (uc_4t); //Display function prototype. --> it takes the number that should be displayed.

void RESET_PUSH_BUTTON_INT0 (void); //Reset push button on INT0 initialization function prototype.

void PAUSE_PUSH_BUTTON_INT1 (void); //Pause push button on INT1 initialization function prototype.

void RESUME_PUSH_BUTTON_INT2 (void); // Resume push button on INT2 initialization function prototype.


