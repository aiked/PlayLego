#include "clock.h"
#include "sound.h"

volatile ULONG hh = 0;
volatile ULONG mm = 0;
volatile ULONG ss = 0;
// Interrupt counter
volatile UBYTE in = 0;

ULONG pattern[] = {0xF0000F00};

void DisplayTime_PIT(void){

	++in;

	if(in==3){

		in = 0;
		++ss;

		SoundAsync(pattern, sizeof(pattern)/sizeof(ULONG), 100, 10);
	
		// Reset sec
		if(ss == 60){
			++mm;
			ss = 0;
		}

		// Reset min
		if(mm == 60){
			++hh;
			mm = 0;
		}

		// Reset hours
		if(hh == 24){
			hh = 0; 
		}

		DisplayPrintTime(hh, mm, ss);
	}

	PITAckInterrupt();		
}
