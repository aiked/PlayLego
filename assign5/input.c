#include "input.h"
#include "arm2avr.h"
#include "i2c.h"

void InputInit(){
	return;
}

void InputExit(){
	return;
}

UWORD InputGetSensorValue(UBYTE port){
	return IoFromAvr.AdValue[port];
}
