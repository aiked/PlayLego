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

	enum button_t button_val;

	while(1) {
		I2CTransfer();
		DisplayErase();

		/* Button Stuff */
		button_val = ButtonRead();
		DisplayString(0, 0, "Button Pressed:");
		switch(button_val)
			{
			case BUTTON_RIGHT:
				DisplayString(0, 10, "Right");
				break;
			case BUTTON_LEFT:
				DisplayString(0, 10, "Left");
				break;
			case BUTTON_ENTER:
				DisplayString(0, 10, "Enter");
				break;
			case BUTTON_EXIT:
				DisplayString(0, 10, "Exit");
				break;
			case BUTTON_NONE:
				DisplayString(0, 10, "None");
				break;
			default:
				DisplayString(0, 10, "Combo");
				break;
			}

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
