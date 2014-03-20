#include "clock.h"

void DisplayDigitalClock(UBYTE cx, UBYTE cy, UBYTE hh, UBYTE mm, UBYTE ss){
	DisplayNum(cx, cy, hh/10);
	DisplayNum(cx+6, cy, hh%10);

	DisplayChar(cx+11, cy, ':');

	DisplayNum(cx+15, cy, mm/10);
	DisplayNum(cx+20, cy, mm%10);

	DisplayChar(cx+25, cy, ':');

	DisplayNum(cx+29, cy, ss/10);
	DisplayNum(cx+35, cy, ss%10);

	}

void DisplayAnalogClock(UBYTE cx, UBYTE cy, UBYTE r, UBYTE hh, UBYTE mm, UBYTE ss){
		AclockDisplayFrame(cx, cy, r);
		AclockDisplayHand(cx, cy, r, MIN_SEC2DEG(ss), SEC);
		AclockDisplayHand(cx, cy, r, MIN_SEC2DEG(mm), MIN);
		AclockDisplayHand(cx, cy, r, HOUR2DEG(hh), HOUR);
		AclockDisplayFrameSymbol(cx, cy, r, 0);
}
