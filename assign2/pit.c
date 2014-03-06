#include "AT91SAM7S256.h"
#include "pit.h"

#define AT91C_PITC_PITDIS      ((unsigned int) 0x0 << 24) // (PITC) Periodic Interval Timer Disabled
#define AT91C_PITC_PITIDIS     ((unsigned int) 0x0 << 25) // (PITC) Periodic Interval Timer Interrupt Disable


/*
 *	Enables the PIT
 */
void PITEnable(void){
				     /*	0x1 << 24     |	     0x1 << 25 */
	AT91C_BASE_PITC->PITC_PIMR = AT91C_PITC_PITEN | AT91C_PITC_PITIEN;
}


/*
 *	Disables the PIT	
 */
void PITDisable(void){
	                             /* 0x0 << 24      |      0x0 << 25 */
        AT91C_BASE_PITC->PITC_PIMR = AT91C_PITC_PITDIS | AT91C_PITC_PITIDIS;
}


/*
 *	Reads the PIT status
 */
ULONG PITRead(void){
	volatile ULONG status;
//	status = AT91C_BASE_PITC->PITC_PIVR;	// Read & Reset
	status = AT91C_BASE_PITC->PITC_PIIR;	// Read Only
	return status;
}
