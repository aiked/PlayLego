#include <stdconst.h>
#include "AT91SAM7S256.h"
#include "led.h"

#define DIGIA0 (23) // Port 1 pin 5 (yellow)
#define DIGIA1 (18) // Port 1 pin 6 (blue)
#define DIGIB0 (28) // Port 2 pin 5
#define DIGIB1 (19) // Port 2 pin 6
#define DIGIC0 (29) // Port 3 pin 5
#define DIGIC1 (20) // Port 3 pin 6
#define DIGID0 (30) // Port 4 pin 5
#define DIGID1 (2)  // Port 4 pin 6

// use LED(port, 0)/LED(port, 1) to turn led off/on
void LED(UBYTE port, UBYTE state) {
	ULONG lport;
  	switch(port){
	case 0: lport = (1<<DIGIA0); break;
	case 1:
	case 2:
	case 3:
	default:
        }
	*AT91C_PIOA_PER = lport;
	*AT91C_PIOA_OER = lport;
	if(state == 0) { ;}  /* set correct PIO pin to 0 */
	else { ; } /* set correct PIO pin to 1 */
}

void LedSwitchOn(UBYTE port){ LED(port, 1); }
void LedSwitchOff(UBYTE port){ LED(port, 0); }
