#include "inputManager.h"
#include "display.h"
#include "button.h"
#include <string.h>
#include <stdlib.h>
#include <stdconst.h>

void manageTouch(UWORD in){
	DisplayString(0, 20, (unsigned char*)"Touch:");
	if( in>100 && in<300 )
		DisplayString(50,20, (unsigned char*)"On");
	else
		DisplayString(50,20, (unsigned char*)"Off");
	return;
}

void manageMic(UWORD in){
	DisplayString(0, 30, (unsigned char*)"Mic:");
	if( in<405 )
		DisplayString(50, 30, (unsigned char*)"Quiet");
	else
		DisplayString(50, 30, (unsigned char*)"Loud");
	return;
}

void manageLight(UWORD in){
	DisplayString(0, 50, (unsigned char*)"Mic:");
	if( in>515 && in<550 )
		DisplayString(50, 50, (unsigned char*)"White");
	else if ( in>590 &&in<620 ) 
		DisplayString(50, 50, (unsigned char*)"Red");
	else if ( in>620 &&in<640 ) 
		DisplayString(50, 50, (unsigned char*)"Green");
	else if ( in>640 &&in<680 ) 
		DisplayString(50, 50, (unsigned char*)"Blue");
	else if ( in>680 &&in<800 ) 
		DisplayString(50, 50, (unsigned char*)"Black");
	else
		DisplayString(50, 50, (unsigned char*)"Undef");
	return;
}


void manageButton(button_state button_val ){
	DisplayString(0, 0, (unsigned char*)"Button:");
	switch(button_val){
		case BUTTON_RIGHT:
			DisplayString(50, 0, (unsigned char*)"Right");
			break;
		case BUTTON_LEFT:
			DisplayString(50, 0, (unsigned char*)"Left");
			break;
		case BUTTON_ENTER:
			DisplayString(50, 0, (unsigned char*)"Enter");
			/* For Task 3.4 (trip) */
			// IoToAvr.Power = REPROGRAM;
			break;
		case BUTTON_EXIT:
			DisplayString(50, 0, (unsigned char*)"Exit");
			/* For Task 3.4 (trip) */
			// IoToAvr.Power = POWERDOWN;
			break;
		case BUTTON_NONE:
			DisplayString(50, 0, (unsigned char*)"None");
			break;
		default:
			DisplayString(50, 0, (unsigned char*)"Combo");
			break;
	}
}
