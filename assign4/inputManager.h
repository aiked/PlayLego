#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include <stdconst.h>
#include "button.h"

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

void manageTouch( UWORD in );
void manageMic( UWORD in );
void manageLight( UWORD in );
void manageButton( button_state button_val );

#endif
