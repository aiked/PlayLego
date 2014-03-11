#include "aic.h"


void AICInit(void){
	*AT91C_AIC_IDCR = (unsigned int) 0xFFFFFFFF;
}


void AICInterruptEnable(int which, void (*handler)(void)){

	*AT91C_AIC_IECR = (unsigned int) 0x1 <<  which;
	
	// Set mode(Internal,External) & priority( setting it to sensitive mode )
	switch(which){
		case AT91C_ID_SYS: // Priority 0x7
			AT91C_AIC_SMR[which] = AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE | AT91C_AIC_PRIOR_HIGHEST;
		case AT91C_ID_SSC: // Priority 0x6
			AT91C_AIC_SMR[which] = AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL | ((unsigned int) 0x6);
	}

	// Assign handler function inside vector
	AT91C_AIC_SVR[which] = (int)handler;
}


void AICInterruptDisable(int which){
	*AT91C_AIC_IDCR = (unsigned int) 0x1 <<  which;
}
