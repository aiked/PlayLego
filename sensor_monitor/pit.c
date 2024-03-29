#include "AT91SAM7S256.h"
#include "pit.h"


#define PIV_1_SEC 3000000

void PITEnable(void){
	*AT91C_PITC_PIMR |= AT91C_PITC_PITEN;
}


void PITDisable(void){
	*AT91C_PITC_PIMR &= ~AT91C_PITC_PITIEN;
	*AT91C_PITC_PIVR;    
}


ULONG PITRead(void){
  return *AT91C_PITC_PIIR;    
}


ULONG PITReadReset(void){
	return *AT91C_PITC_PIVR;
}


void PITInterruptEnable(ULONG period, void (*handler)(void)){
	*AT91C_PITC_PIMR = AT91C_PITC_PITEN | AT91C_PITC_PITIEN | period;
	AICInterruptEnable( AT91C_ID_SYS, handler);
}


void PITInterruptDisable(void){
	*AT91C_PITC_PIMR &= ~AT91C_PITC_PITIEN;
	*AT91C_PITC_PIVR;
	AICInterruptDisable( AT91C_ID_SYS );
}

void PITAckInterrupt(void){
	PITReadReset();
	*AT91C_AIC_EOICR = 0x1;
}

/*
UWORD PITTicks2ms(ULONG ticks){
  return ticks / 3000;
}


UWORD PITTicks2s(ULONG ticks){
	return ticks / 3000000;
}


void spindelayms(ULONG ms){
	
	*AT91C_PITC_PIMR = AT91C_PITC_PITEN | AT91C_PITC_PITIEN;
	*AT91C_PITC_PIMR |= PIV_1_SEC;

	while(1){
		if(( (*AT91C_PITC_PIIR)/3000) > ms){
			PITDisable();
			return; 
		}
	}
}
*/
