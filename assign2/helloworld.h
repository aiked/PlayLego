/* Lego Nxt */
#include "display.h"
#include "led.h"

/* Emulate cycles for one sec */
#define S_SEC 10000

/* 
 * waste_time() is a function to emulate 
 * the standard sleep() function.
 * INPUT: _time
 * OUTPUT: _time * 0.1 sec
 */
void waste_time( UWORD _time );

/*
 * hello_world() prints a "Hello World!"
 * and a number to show at what loop the 
 * function is currently is in.
 * INPUT: Number of times to print the message
 */
void hello_world( UWORD times );

/*
 * snail_hello_world() prints a "Hello World!"
 * and a number to show at what loop the 
 * function is currently is in.
 * INPUT: Number of times to print the message
 * NOTE: the snail edition uses volatile vars
 * and some optimization by the compiler are
 * disabled.
 */
void snail_hello_world( UWORD times );

