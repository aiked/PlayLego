/*
 * AIC
 * Advanced Interrupt Controller
 * Info: /papers/AT91SAM7S_preliminary.pdf @ 183 page
 */

#ifndef   AIC
#define   AIC

#include <stdconst.h>
#include "AT91SAM7S256.h"


/*
 * Initialize AIC by disabling all interrupts
 */
void      AICInit(void);

/*
 * Enable an interrupt by changing AIC_IECR
 * preCond: 0 <= which <= 31
 * preCond: (*handler) != NULL
 * param: which ~ The number of interrupt to enable
 * param: (*handler) ~ handler function to be called during interrupt
 */
void      AICInterruptEnable(int which, void (*handler)(void));

/*
 * Disable an interrupt by changing AIC_IDCR
 * preCond: 0 <= which <= 31
 * param: which ~ The number of interrupt to disable
 */
void      AICInterruptDisable(int which);

#endif
