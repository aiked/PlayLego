#include "aic.h"


void AICInit(void){
	AT91C_BASE_AIC->AIC_IDCR = (unsigned int) 0xFFFFFFFF;
}


void AICInterruptEnable(int which, void (*handler)(void)){
	AT91C_BASE_AIC->AIC_IECR = (unsigned int) 0x1 <<  which;
	
	// Set mode(Internal,External) & priority( setting it to sensitive mode )
	AT91C_BASE_AIC->AIC_SMR[which] = AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE | AT91C_AIC_PRIOR_HIGHEST;


//	AT91C_BASE_AIC->AIC_SMR[which] = 7;
//	AT91C_BASE_AIC->AIC_SMR[which] |= 0x11 << 4;


	// Assign handler function inside vector
	AT91C_BASE_AIC->AIC_SVR[which] = (int)handler;
}


void AICInterruptDisable(int which){
	AT91C_BASE_AIC->AIC_IDCR = (unsigned int) 0x1 <<  which;
}
