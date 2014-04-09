#include "i2c.h"
#include "arm2avr.h"
#include "output.h"


void
OutputInit(void)
{
	UBYTE i;

	IoToAvr.Power = NORMAL_OP;
	IoToAvr.PwmFreq = 4;
	IoToAvr.OutputMode = 0;
	IoToAvr.InputPower = 1;
	for(i = 0; i < 4; i++)
		IoToAvr.PwmValue[i] = 0;
}


void
OutputExit(void)
{
	return;
}


void OutputSetSpeed(UBYTE MotorNr, SBYTE Speed)
{
	// TO DO CODE
}

