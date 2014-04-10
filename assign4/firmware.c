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
#include "peripherals.h"

//#include "aclock.h"

int main(void) {

//	LedSwitchOn(2);
	HardwareInit(); // need this to init PIOA clock
	DisplayInit(); 
	PITEnable();
	AICInit();
	SoundInit();
	I2CInit();
	InputInit();
	ButtonInit();
	OutputInit();

	button_state 	button_val;
	touch_state 	touch_val;
	mic_state			mic_val;
	light_state		light_val;

	UBYTE					motorNr;
	SBYTE					motor_speed;

	motorNr = 1;
	motor_speed = 50;

	OutputSetSpeed(motorNr, motor_speed);

	while(1) {
		I2CTransfer();
		DisplayErase();

		/* Button Stuff 
		 *	ATTENTION!!!!!!!!!!
		 *	Do !! NOT !! uncomment "For Task 3.4"
		 *	Lego trips as hell
		 *	REAL pain to reset!!
		 */

		/*
		 * from: michath
		 * bitches be tripping
		 */

		button_val = ButtonRead();
		printButton(button_val);

		touch_val = InputGetSensorValue(PORT_TOUCH);
		printTouch(touch_val);

		mic_val = InputGetSensorValue(PORT_MIC);
		printMic(mic_val);

		light_val = InputGetSensorValue(PORT_LIGHT);
		printLight(light_val);

		printMotors(motor_speed);

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
