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


#define max(a,b) \
    ({ typeof (a) _a = (a); \
       typeof (b) _b = (b); \
       _a > _b ? _a : _b; })


/*
 * Alarm has a series of states 
 * INIT: all peripherals are initiliazed.
 * IDLE: Usually the state after INIT when the system does nothing.
 * ARMING: When the password is inserted the system starts moving
 * until it finds a door to stop and to got ARMED state.
 */

typedef enum {INIT,IDLE,ARMING,ARMED,ALARMED_FW,ALARMED_RW} alarm_t;

// Variables for the state of the peripherals 
#define PORT_LED 2
#define PORT_TOUCHFRONT 1
#define PORT_TOUCHBACK 0
// Motor Related
#define MOTOR_IN_ONE 0
#define MOTOR_IN_TWO 1
#define MOTORSPEED 70
SBYTE motorSpeed;

// TouchFront Related
#define TOUCH_LIMIT 300
unsigned int tchFrontVal;
unsigned int tchBackVal;

button_state btnVal;
alarm_t alarmVal;

// Monitor Related
#define MTR_STATE_X 10
#define MTR_STATE_Y 0
#define MTR_TOUCH_FR_X 10
#define MTR_TOUCH_FR_Y 12
#define MTR_TOUCH_BA_X 10
#define MTR_TOUCH_BA_Y 20
#define MTR_BUTTN_X 10
#define MTR_BUTTN_Y 28
#define MTR_MOTOR_X 10
#define MTR_MOTOR_Y 36

void initAlarm(void);

void manageButton( void );
void manageMotors( void );
void manageTouch( void );
void manageMonitor( void );


