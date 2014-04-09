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
//	*AT91C_PITC_PIMR |= AT91C_PITC_PITEN;
	AICInit();
	SoundInit();
	I2CInit();
//	InputInit();
	ButtonInit();
	OutputInit();

	while(1) {
		I2CTransfer();
		DisplayString(0, 0, "pass");
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
