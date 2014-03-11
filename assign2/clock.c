#include "clock.h"


ULONG hh = 0;
ULONG mm = 0;
ULONG ss = 0;
// Interrupt counter
UBYTE in = 0;

void DisplayTime_PIT(void){

	++in;

	if(in == 3){

		in = 0;
		++ss;

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
