#include "peripherals.h"

#include "display.h"
#include "button.h"

#include <string.h>
#include <stdlib.h>
#include <stdconst.h>

#define DATA_OFFSET_X 50
#define Y_TOUCH 36
#define Y_LIGHT 24
#define Y_BUTTN 0
#define Y_MIC		12
#define Y_MOTOR 48

void printTouch(UWORD in){
	DisplayString(0, Y_TOUCH, (unsigned char*)"Touch:");
	if( in>100 && in<300 )
		DisplayString(DATA_OFFSET_X, Y_TOUCH, (unsigned char*)"On");
	else
		DisplayString(DATA_OFFSET_X, Y_TOUCH, (unsigned char*)"Off");
	return;
}

void printMic(UWORD in){
	DisplayString(0, Y_MIC, (unsigned char*)"Mic:");
	if( in<405 )
		DisplayString(DATA_OFFSET_X, Y_MIC, (unsigned char*)"Quiet");
	else
		DisplayString(DATA_OFFSET_X, Y_MIC, (unsigned char*)"Loud");
	return;
}

void printLight(UWORD in){
	DisplayString(0, Y_LIGHT, (unsigned char*)"Mic:");
	if( in>515 && in<550 )
		DisplayString(DATA_OFFSET_X, Y_LIGHT, (unsigned char*)"White");
	else if ( in>590 &&in<620 ) 
		DisplayString(DATA_OFFSET_X, Y_LIGHT, (unsigned char*)"Red");
	else if ( in>620 &&in<640 ) 
		DisplayString(DATA_OFFSET_X, Y_LIGHT, (unsigned char*)"Green");
	else if ( in>640 &&in<680 ) 
		DisplayString(DATA_OFFSET_X, Y_LIGHT, (unsigned char*)"Blue");
	else if ( in>680 &&in<800 ) 
		DisplayString(DATA_OFFSET_X, Y_LIGHT, (unsigned char*)"Black");
	else
		DisplayString(DATA_OFFSET_X, Y_LIGHT, (unsigned char*)"Undef");
	return;
}


void printButton(button_state button_val ){
	DisplayString(0, Y_BUTTN, (unsigned char*)"Button:");
	switch(button_val){
		case BUTTON_RIGHT:
			DisplayString(DATA_OFFSET_X, Y_BUTTN, (unsigned char*)"Right");
			break;
		case BUTTON_LEFT:
			DisplayString(DATA_OFFSET_X, Y_BUTTN, (unsigned char*)"Left");
			break;
		case BUTTON_ENTER:
			DisplayString(DATA_OFFSET_X, Y_BUTTN, (unsigned char*)"Enter");
			/* For Task 3.4 (trip) */
			// IoToAvr.Power = REPROGRAM;
			break;
		case BUTTON_EXIT:
			DisplayString(DATA_OFFSET_X, Y_BUTTN, (unsigned char*)"Exit");
			/* For Task 3.4 (trip) */
			// IoToAvr.Power = POWERDOWN;
			break;
		case BUTTON_NONE:
			DisplayString(DATA_OFFSET_X, Y_BUTTN, (unsigned char*)"None");
			break;
		default:
			DisplayString(DATA_OFFSET_X, Y_BUTTN, (unsigned char*)"Combo");
			break;
	}
}

void printMotors( SBYTE speed ){
	DisplayString( 0, Y_MOTOR, (unsigned char*)"Motor:" );
	DisplayNum(1, DATA_OFFSET_X, Y_MOTOR, speed);
}

