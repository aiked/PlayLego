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

typedef enum {INIT,IDLE,ARMING,ARMED,ALARMED,PANIC} alarm_t;

// Variables for the state of the peripherals 
#define PORT_LED 1
#define PORT_TOUCHFRONT 2

// Motor Related
#define MOTOR_IN_ONE 1
#define MOTOR_IN_TWO 2
#define MOTORSPEED 50
SBYTE motorSpeed;

// TouchFront Related
#define TOUCH_LIMIT 300
unsigned int tchVal;

button_state btnVal;
alarm_t alarmVal;

// Monitor Related
#define MTR_STATE_X 10
#define MTR_STATE_Y 0
#define MTR_TOUCH_X 10
#define MTR_TOUCH_Y 12
#define MTR_BUTTN_X 10
#define MTR_BUTTN_Y 20
#define MTR_MOTOR_X 10
#define MTR_MOTOR_Y 28

/*
 * Timer related
 * TIMER_PANIC_LIMIT to be set as a multiple
 * of the min frequency the PIT interrupt can 
 * get. Min frequency is 0xf4240 or 0.33 seconds
 */
#define TIMER_PANIC_LIMIT 10 * 3 
#define INTERRUPT_FREQUENCY 0xf4240
unsigned int panic_interrupts;

void initAlarm(void);

void manageButton( void );
void manageMotors( void );
void manageTouchFront( void );
void manageMonitor( void );
void manageTimers ( void );

void handler_timer_panic( void );

void armSystem();
