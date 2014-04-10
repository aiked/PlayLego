#include <stdlib.h>
#include <assert.h>
#include "AT91SAM7S256.h"
#include "hwinit.h"
#include "pit.h"
#include "aic.h"
#include "display.h"
#include "sound.h"
#include "i2c.h"
#include "input.h"
#include "button.h"
#include "output.h"
#include "led.h"
#include "inputManager.h"

//#include "aclock.h"

int main(void) {

//	LedSwitchOn(2);
	HardwareInit(); // need this to init PIOA clock
	DisplayInit(); 
	PITEnable();
	AICInit();
	SoundInit();
	I2CInit();
//	InputInit();
	ButtonInit();
	OutputInit();

	button_state 	button_val;
	touch_state 	touch_val;
	mic_state			mic_val;
	light_state		light_val;

	while(1) {
		I2CTransfer();
		DisplayErase();

		/* Button Stuff 
		 *	ATTENTION!!!!!!!!!!
		 *	Do !! NOT !! uncomment "For Task 3.4"
		 *	Lego trips as hell
		 *	REAL pain to reset!!
		 */
		button_val = ButtonRead();
		manageButton(button_val);

		touch_val = InputGetSensorValue(PORT_TOUCH);
		manageTouch(touch_val);

		mic_val = InputGetSensorValue(PORT_MIC);
		manageMic(mic_val);

		light_val = InputGetSensorValue(PORT_LIGHT);
		manageLight(light_val);

		DisplayUpdateSync();
	}
/*
	ButtonExit();
	InputExit();
	I2CExit();
	PITInterruptDisable();
	PITDisable();
	SoundExit();
	DisplayExit();
*/

	return 0;
}
