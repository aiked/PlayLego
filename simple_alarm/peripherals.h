#ifndef _PERIPHERALS_H
#define _PERIPHERALS_H

#include <stdconst.h>
#include "button.h"
#include "arm2avr.h"

typedef enum sensor_light_states_t{
	L_WHITE,
	L_BLACK,
	L_RED,
	L_GREEN,
	L_BLUE,
} light_state;

typedef enum sensor_touch_states_t{
	L_TOUCH,
	L_NO_TOUCH
} touch_state;

typedef enum sensor_mic_states_t{
	L_DUPSTEP,// noise on
	L_CLASSIC	// noise off
} mic_state;

void printTouch( UWORD in );
void printMic( UWORD in );
void printLight( UWORD in );
void printButton( button_state button_val );
void printMotors( SBYTE speed );

void handleMotors( UBYTE motorNr,button_state btn_val );

#endif
