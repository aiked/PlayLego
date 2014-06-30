#include <stdlib.h>

#include "AT91SAM7S256.h"
#include "hwinit.h"
#include "i2c.h"
#include "pit.h"
#include "aic.h"
#include "display.h"
#include "sound.h"
#include "button.h"
#include "input.h"
#include "output.h"
#include "led.h"

/*
 * Alarm has a series of states 
 * INIT: all peripherals are initiliazed.
 * IDLE: Usually the state after INIT when the system does nothing.
 * ARMING: When the password is inserted the system starts moving
 * until it finds a door to stop and to got ARMED state.
 */

#typedef enum {INIT,IDLE,ARMING,ARMED,ALARMED,PANIC,} alarm_t;

// Variables for the state of the peripherals 
#define PORT_LED 1
#define PORT_TOUCHFRONT 2

// Motor Related
#define MOTOR_IN_ONE 1
#define MOTOR_IN_TWO 2
SBYTE motorSpeed = 50;

// TouchFront Related
#define TOUCH_LIMIT 300
touch_state tchVal;

button_state btnVal;
alarm_state alarmVal;

void initAlarm(void);

void manageButton( button_state btnVal );
void manageMotors( void );
void manageTouchFront( void );

void armSystem();
