#include <stdlib.h>
#include <assert.h>
#include "AT91SAM7S256.h"
#include "pit.h"
#include "aic.h"
#include "display.h"

#define D_CLK_X 58
#define D_CLK_Y 47

#define A_CLK_X 28
#define A_CLK_Y 31
#define A_CLK_R 20

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

		DisplayErase();

		DisplayAnalogClock( A_CLK_X, A_CLK_Y, A_CLK_R, hours, minutes, seconds );
		DisplayDigitalClock( D_CLK_X, D_CLK_Y, hours, minutes, seconds );
		
		DisplayUpdateSync();
	}
	
	PITAckInterrupt();
}


int main(void){

	AICInit();
	
	DisplayInit();
		
	PITInterruptEnable(0xF4240 , pit_handler);

	return 0;
}
