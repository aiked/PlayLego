#ifndef _ACLOCK_H_
#define _ACLOCK_H_

#include <math.h>
#include "display.h"

typedef enum { HOUR, MIN, SEC } Time_Mode_t;

#define PI 3.1415926

#define HOUR2DEG(in) in*30
#define MIN_SEC2DEG(in) in*6

void AclockDisplayFrame(UBYTE cx, UBYTE cy, UBYTE r);

//void AclockDisplayHand(UBYTE cx, UBYTE cy, UBYTE r, UWORD hh);
void AclockDisplayHand(UBYTE cx, UBYTE cy, UBYTE r, UWORD angle, Time_Mode_t mode);
void AclockDisplayFrameSymbol(UBYTE cx, UBYTE cy, UBYTE r, UWORD hh);

#endif
