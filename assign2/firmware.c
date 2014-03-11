#include <stdlib.h>
#include <assert.h>
#include "AT91SAM7S256.h"
#include "sound.h"
#include "clock.h"


UWORD hours = 0;
UWORD minutes = 0;
UWORD seconds = 0;
UWORD interrupts = 0;
 
void pit_handler(void){

	++interrupts;

	if((interrupts % 3) == 0){
		++seconds;

		// Reset seconds
		if(seconds == 60){
			seconds = 0;
			++minutes;
		}
		
		// Reset minutes
		if(minutes == 60){
			minutes = 0;
			++hours;
		}

		// Reset hours
		if(hours == 24){
			hours = 0;
		}

	DisplayPrintTime(hours ,minutes ,seconds); 
	}
	
	PITAckInterrupt();
}


int main(void){

	AICInit();
	SoundInit();
	
	DisplayInit();
	DisplayOn(1);
	
	//DisplayPrintTimeBusy();
	PITInterruptEnable(0xF4240 , pit_handler);

	ULONG pattern[] = {0xFF00FF00};
	
	while(1){
		// Beep every 10 seconds
		if ((seconds % 10) == 0){
			SoundAsync(pattern, sizeof(pattern)/sizeof(ULONG), 100, 10);
		}
	}

	// cleanup here
	SoundExit();
	PITDisable();
	PITInterruptDisable();
	DisplayExit();

	return 0;
}
