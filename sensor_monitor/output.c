#include "i2c.h"
#include "arm2avr.h"
#include "output.h"


void
OutputInit(void)
{
	UBYTE i;

	IoToAvr.Power = NORMAL_OP;
	IoToAvr.PwmFreq = 8;
		for(i = 0; i < 4; ++i){
		IoToAvr.PwmValue[i] = 0;
		}
	IoToAvr.OutputMode = 0;
	IoToAvr.InputPower = 1;
}



void
OutputExit(void)
{
	return;
}


void OutputSetSpeed(UBYTE MotorNr, SBYTE Speed){
	
	if(Speed == 0){
		IoToAvr.OutputMode |= ( 1 << MotorNr );
		IoToAvr.PwmValue[MotorNr] = SPEED_ZERO; 
	}
	else{
		IoToAvr.OutputMode &= ( 0x07 & (~(1 << MotorNr)) );

		if(Speed > MAX_SPEED_FW){
			IoToAvr.PwmValue[MotorNr] = MAX_SPEED_FW;
		}
		else if(Speed < MAX_SPEED_RW){
			IoToAvr.PwmValue[MotorNr] = MAX_SPEED_RW;
		}
		else{
			IoToAvr.PwmValue[MotorNr] = Speed;
		}
	}

}
