#include <stdlib.h>

#include "i2c.h"
#include "button.h"


void
ButtonInit(void)
{
	IoFromAvr.Buttons = BUTTON_NONE; 
}


void
ButtonExit(void)
{
	return;
}


enum button_t
ButtonRead(void)
{
	UWORD val = IoFromAvr.Buttons;

 DisplayNum(1, 0, 10, val);
        DisplayUpdateSync();


	if(val == 0)
		return BUTTON_NONE;
	else if((val > 0x187) && (val < 0x1A6))
		return BUTTON_RIGHT;
	else if((val > 0x070) && (val < 0x08F))
		return BUTTON_LEFT;
	else if((val > 0x7F0) && (val < 0x80F))
		return BUTTON_ENTER;
	else if((val > 0x3E4) && (val < 0x40F))
		return BUTTON_EXIT;
	else if((val > 0x0A4) && (val < 0x0C8))
		return BUTTON_RIGHT | BUTTON_LEFT;
	else if((val > 0x985) && (val < 0x9A5))
		return BUTTON_RIGHT | BUTTON_ENTER;
	else if((val > 0x3C9) && (val < 0x3E4))
		return BUTTON_RIGHT | BUTTON_EXIT;
	else if((val > 0x86E) && (val < 0x87F))
		return BUTTON_LEFT | BUTTON_ENTER;
	else if((val > 0x3A0) && (val < 0x3C8))
		return BUTTON_LEFT | BUTTON_EXIT;
	else if((val > 0xBF0) && (val < 0xC0E))
		return BUTTON_ENTER | BUTTON_EXIT;
	else if((val > 0xBC0) && (val < 0xBEF))
		return BUTTON_RIGHT | BUTTON_ENTER | BUTTON_EXIT;
	else if((val > 0xB80) && (val < 0xBBF))
		return BUTTON_LEFT | BUTTON_ENTER | BUTTON_EXIT;
	else if((val > 0x8A6) && (val < 0x3A0))
		return BUTTON_RIGHT | BUTTON_LEFT | BUTTON_ENTER;
	else if((val > 0x360) && (val < 0x3A0))
		return BUTTON_RIGHT | BUTTON_LEFT | BUTTON_EXIT;
	else if((val > 0xB50) && (val < 0xB7F))
		return BUTTON_RIGHT | BUTTON_LEFT | BUTTON_ENTER | BUTTON_EXIT;
	else
		return BUTTON_NONE;
}

