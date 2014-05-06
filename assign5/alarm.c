#include "alarm.h"

void initAlarm(void){
	
	alarmVal = INIT;

	HardwareInit();
	DisplayInit(); 
	PITEnable();
	AICInit();
	SoundInit();
	I2CInit();
	InputInit();
	ButtonInit();
	OutputInit();

	alarmVal = IDLE;
}

void manageButton( button_state btnVal ){

	switch(alarmVal){
		case IDLE: /* IDLE -> WAIT_PASS */
			if ( btnVal == BUTTON_ENTER ){
				alarmVal = ARMING;
				// Call function to enable arming.
			}
			break;

		default:
			break;
	}


}

void manageMotors(void){
	switch(alarmVal){
		case ARMING:
			OutputSetSpeed(MOTOR_IN_ONE, motorSpeed);
			OutputSetSpeed(MOTOR_IN_TWO, motorSpeed);
			break;
		case PANIC:
			OutputSetSpeed(MOTOR_IN_ONE, -motorSpeed);
			OutputSetSpeed(MOTOR_IN_TWO, -motorSpeed);
			break;
	}
	return;
}

void manageTouchFront(void){
	switch(alarmVal){
		case ARMING:
			if(tchVal<TOUCH_LIMIT){
				alarmVal = ARMED;
				LedSwitchOn(PORT_LED);
				OutputSetSpeed(MOTOR_IN_ONE, SPEED_ZERO);
				OutputSetSpeed(MOTOR_IN_TWO, SPEED_ZERO);
			}
			break;
		case ARMED:
			alarmVal = ALARMED;
	}
}
