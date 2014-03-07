#include "AT91SAM7S256.h"
#include "pit.h"

#define PIV_1_SEC               3000000  // 1 sec for 48 MHz


/*
 *	Enables the PIT
 */
void PITEnable(void){
				     /*	0x1 << 24     |	     0x1 << 25 */
	AT91C_BASE_PITC->PITC_PIMR = AT91C_PITC_PITEN | AT91C_PITC_PITIEN | PIV_1_SEC;
}


/*
 *	Disables the PIT	
 */
void PITDisable(void){
	AT91C_BASE_PITC->PITC_PIMR &= ~AT91C_PITC_PITIEN;
	volatile ULONG status;
	status = AT91C_BASE_PITC->PITC_PIVR;    // Read & Reset on read
}


/*
 *	Reads the PIT counters
 */
ULONG PITRead(void){
//      return AT91C_BASE_PITC->PITC_PIVR;    // Read & Reset
        return AT91C_BASE_PITC->PITC_PIIR;    // Read Only
}


/*
 *      Ticks to ms
 */
UWORD PITTicks2ms(ULONG ticks){
  return ticks / 3000;
}


/*
 *      Converts ticks to seconds
 */
UWORD PITTicks2s(ULONG ticks){
	return ticks / 3000000;
}


/*
 *      Delay for XX ms
 */
void spindelayms(ULONG ms){
	PITEnable();
  while(1){
    if(PITTicks2ms(PITRead()) >= ms){
			PITDisable();
			break; 
			}
	}
}

