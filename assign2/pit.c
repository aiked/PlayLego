#include "AT91SAM7S256.h"
#include "pit.h"

#define PIV_1_SEC               3000000  // 1 sec for 48 MHz


void PITEnable(void){
				     /*	0x1 << 24     |	     0x1 << 25 */
	AT91C_BASE_PITC->PITC_PIMR = AT91C_PITC_PITEN | AT91C_PITC_PITIEN | PIV_1_SEC;
}


void PITDisable(void){
	AT91C_BASE_PITC->PITC_PIMR &= ~AT91C_PITC_PITIEN;
	volatile ULONG status;
	status = AT91C_BASE_PITC->PITC_PIVR;    
}


ULONG PITRead(void){
        return AT91C_BASE_PITC->PITC_PIIR;    
}


ULONG PITReadReset(void){
	volatile ULONG retval = AT91C_BASE_PITC->PITC_PIVR;
	return retval;
}


void      PITInterruptEnable(ULONG period, void (*handler)(void)){
	AICInterruptEnable( AT91C_ID_SYS ,handler);
	PITEnable();

}


void      PITInterruptDisable(void){
	

}


UWORD PITTicks2ms(ULONG ticks){
  return ticks / 3000;
}


UWORD PITTicks2s(ULONG ticks){
	return ticks / 3000000;
}


void spindelayms(ULONG ms){
	PITEnable();
  while(1){
    if(  (AT91C_BASE_PITC->PITC_PIIR/3000)>ms){
			PITDisable();
			return; 
		}
	}
}

