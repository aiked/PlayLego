#include "alarm.h"

void initAlarm(void){
	
	alarmVal = INIT;

	HardwareInit();
	DisplayInit(); 
	AICInit();
	PITEnable();
	SoundInit();
	I2CInit();
	InputInit();
	ButtonInit();
	OutputInit();

	LED(PORT_LED,0);
	alarmVal = IDLE;
}

void manageButton(){

	switch(alarmVal){
		case IDLE:
			if ( btnVal == BUTTON_ENTER ){
				alarmVal = ARMING;
			}
			break;
		case ALARMED_FW:
			if ( btnVal == BUTTON_LEFT ){
				alarmVal = IDLE;
				LED(PORT_LED, 0);
			}
			break;
		case ALARMED_RW:
			if ( btnVal == BUTTON_LEFT ){
				alarmVal = IDLE;
				LED(PORT_LED, 0);
			}
			break;
		default: break;
	}
}

void manageMotors(void){
	switch(alarmVal){
		case IDLE:
			motorSpeed = SPEED_ZERO; break;
		case ARMING:
			motorSpeed = MOTORSPEED; break;
		case ARMED:
			motorSpeed = SPEED_ZERO; break;
		case ALARMED_FW:
			motorSpeed = MOTORSPEED; break;
		case ALARMED_RW:
			motorSpeed = -MOTORSPEED; break;
		default: break;
	}
	
	OutputSetSpeed(MOTOR_IN_ONE, motorSpeed);
	OutputSetSpeed(MOTOR_IN_TWO, motorSpeed);
}

void manageTouch(void){
	switch(alarmVal){
		case ARMING:
				if(tchFrontVal<TOUCH_LIMIT){
				alarmVal = ARMED;
				LED(PORT_LED, 1);
			}
			break;
		case ARMED:
			if(tchFrontVal>TOUCH_LIMIT){
				alarmVal = ALARMED_RW;
			}
			break;
		case ALARMED_RW:
			if(tchBackVal<TOUCH_LIMIT){
				alarmVal = ALARMED_FW;
				LED(PORT_LED,1);
			}
			break;
		case ALARMED_FW:
			if(tchFrontVal<TOUCH_LIMIT){
				alarmVal = ALARMED_RW;
				LED(PORT_LED,1);
			}
			break;
		default: break;
	}
}


void manageMonitor(void){
	
	// State Print
	unsigned char *msg_state;
	switch(alarmVal){
		case INIT: msg_state = (unsigned char*)"State: INIT"; break;
		case IDLE: msg_state = (unsigned char*)"State: IDLE"; break;
		case ARMING: msg_state = (unsigned char*)"State: ARMING"; break;
		case ARMED: msg_state = (unsigned char*)"State: ARMDED"; break;
		case ALARMED_FW: msg_state = (unsigned char*)"State: ALARM_FW"; break;
		case ALARMED_RW: msg_state = (unsigned char*)"State: ALARM_RW"; break;
	}

	// Touch Front Print
	unsigned char *msg_touch_front;
	if( tchFrontVal < TOUCH_LIMIT ){
		msg_touch_front = (unsigned char*)"Touch Fr: ON";
	}
	else{
		msg_touch_front = (unsigned char*)"Touch Fr: OFF";
	}

	// Touch Back Print
	unsigned char *msg_touch_back;
	if( tchBackVal < TOUCH_LIMIT ){
		msg_touch_back = (unsigned char*)"Touch Ba: ON";
	}
	else{
		msg_touch_back = (unsigned char*)"Touch Ba: OFF";
	}

	// Button Print
	unsigned char* msg_buttn;
	switch(btnVal){
		case BUTTON_NONE: msg_buttn = (unsigned char*)"Button: NONE"; break;
		case BUTTON_LEFT: msg_buttn = (unsigned char*)"Button: LEFT"; break;
		case BUTTON_ENTER: msg_buttn = (unsigned char*)"Button: ENTER"; break;
		case BUTTON_RIGHT: msg_buttn = (unsigned char*)"Button: RIGHT"; break;
		case BUTTON_EXIT: msg_buttn = (unsigned char*)"Button: EXIT"; break;
	}

	// Motor Print
	unsigned char* msg_motor;
	if(motorSpeed == SPEED_ZERO)
		msg_motor = (unsigned char*)"MOTOR: STOP";
	else if( motorSpeed == MOTORSPEED )
		msg_motor = (unsigned char*)"MOTOR: FW";
	else if( motorSpeed == -MOTORSPEED )
		msg_motor = (unsigned char*)"MOTOR: RW";

	//
	unsigned char* msg_timer = "Timer: ";

	DisplayString(MTR_STATE_X, MTR_STATE_Y, msg_state);
	DisplayString(MTR_TOUCH_FR_X, MTR_TOUCH_FR_Y, msg_touch_front);
	DisplayString(MTR_TOUCH_BA_X, MTR_TOUCH_BA_Y, msg_touch_back);
	DisplayString(MTR_BUTTN_X, MTR_BUTTN_Y, msg_buttn);
	DisplayString(MTR_MOTOR_X, MTR_MOTOR_Y, msg_motor);

	return;
}
