#ifndef   _BUTTON_H_
#define   _BUTTON_H_

#include <stdconst.h>

#include "arm2avr.h"

typedef enum button_t {
  BUTTON_NONE,
  BUTTON_LEFT,
  BUTTON_ENTER,
  BUTTON_RIGHT,
  BUTTON_EXIT 
} button_state;

void   ButtonInit(void);
void   ButtonExit(void);
button_state ButtonRead(void);

#endif
