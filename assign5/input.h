#ifndef   _INPUT_H
#define   _INPUT_H

#include <stdconst.h>

typedef enum input_port_layout_t{
	PORT_LIGHT=0,
	PORT_MIC=1,
	PORT_TOUCH=2
} port_type;

void InputInit(void);
void InputExit(void);
UWORD InputGetSensorValue(UBYTE port);

#endif
