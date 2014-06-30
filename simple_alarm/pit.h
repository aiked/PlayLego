#ifndef   PIT
#define   PIT

#include <stdconst.h>
#include "aic.h"


/* Enables PIT */
void      PITEnable(void);

/* Disables PIT */
void      PITDisable(void);

/* Read PIT counters */ 
ULONG     PITRead(void);

/* Read PIT counters & resets them */
ULONG     PITReadReset(void);


void      PITInterruptEnable(ULONG period, void (*handler)(void));


void      PITInterruptDisable(void);


void      PITAckInterrupt(void);

/*
 * Converts PIT ticks(48Mhz/16) into miliseconds
 */
UWORD	  	PITTicks2ms(ULONG ticks);

/*
 * Converts PIT ticks(48Mhz/16) into seconds
 */
UWORD	  	PITTicks2s(ULONG ticks);

/* Produces a busy waiting delay
 * param: ms ~ miliseconds to delay
 * preCond: ms > 0 
 */
void 	  	spindelayms(ULONG ms);

#endif
