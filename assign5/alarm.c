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

void manageButton(){

	switch(alarmVal){
		case IDLE:
			if ( btnVal == BUTTON_ENTER ){
				alarmVal = ARMING;
			}
			break;
		case ALARMED:
			if ( btnVal == BUTTON_ENTER ){
				PITInterruptDisable();
				alarmVal = IDLE;
				panic_interrupts = 0;
			}
			break;
		default: break;
	}


}

void manageMotors(void){
	switch(alarmVal){
		case ARMING:
			motorSpeed = MOTORSPEED; break;
		case PANIC:
			motorSpeed = -MOTORSPEED; break;
		case ARMED:
			motorSpeed = SPEED_ZERO; break;
		default: break;
	}
	
	OutputSetSpeed(MOTOR_IN_ONE, motorSpeed);
	OutputSetSpeed(MOTOR_IN_TWO, motorSpeed);
	
	return;
}

void manageTouchFront(void){
	switch(alarmVal){
		case ARMING:
			if(tchVal<TOUCH_LIMIT){
				alarmVal = ARMED;
				LED(PORT_LED, 1);
			}
			break;
		case ARMED:
			if(tchVal>TOUCH_LIMIT){
				alarmVal = ALARMED;
				panic_interrupts = 0;
				PITInterruptEnable( INTERRUPT_FREQUENCY, handler_timer_panic );
			}
			break;
		default: break;
	}
}

void manageTimers( void ){
	switch(alarmVal){
		case ALARMED:
			if( panic_interrupts == TIMER_PANIC_LIMIT ){
				alarmVal = PANIC;
			}
			break;
		case PANIC:
			if( panic_interrupts % 3 == 0 )
				LED(PORT_LED,1);
			else
				LED(PORT_LED,0);
			break;
		default: break;
	}
}

void handler_timer_panic(void){
	++panic_interrupts;
	PITAckInterrupt();
}

void manageMonitor(void){
	
	// State Print
	unsigned char *msg_state;
	switch(alarmVal){
		case INIT: msg_state = (unsigned char*)"State: INIT"; break;
		case IDLE: msg_state = (unsigned char*)"State: IDLE"; break;
		case ARMING: msg_state = (unsigned char*)"State: ARMING"; break;
		case ARMED: msg_state = (unsigned char*)"State: ARMDED"; break;
		case ALARMED: msg_state = (unsigned char*)"State: ALARMED"; break;
		case PANIC: msg_state = (unsigned char*)"State: PANIC"; break;
	}

	// Touch Print
	unsigned char *msg_touch;
	if( tchVal < TOUCH_LIMIT ){
		msg_touch = (unsigned char*)"Touch: ON";
	}
	else{
		msg_touch = (unsigned char*)"Touch: OFF";
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

	DisplayString(MTR_STATE_X, MTR_STATE_Y, msg_state);
	DisplayString(MTR_TOUCH_X, MTR_TOUCH_Y, msg_touch);
	DisplayString(MTR_BUTTN_X, MTR_BUTTN_Y, msg_buttn);
	DisplayString(MTR_MOTOR_X, MTR_MOTOR_Y, msg_motor);

	return;
}
