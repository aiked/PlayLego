#include <stdlib.h>
#include <assert.h>

// Lego Nxt include
#include "display.h"

#define S_MSG 100
#define TIMES 100
#define SCREEN_CYCLE 17 /*Display Cycle is 17ms */

void emulate_time( UWORD _time ){
	
	UWORD i;
	UWORD limit = _time * 50000;

	for( i=0; i<limit;++i ){
		DisplayUpdateSync();
	}
}

void hello_world(void) {
	
	int i;
	UBYTE *msg = malloc(S_MSG * sizeof(char));
	msg = "Hello world";	

	DisplayInit();
	DisplayOn(1);

	for(i=0;i<TIMES;++i){

		/* Part: empty screen */
		DisplayErase();
		emulate_time(1);

		/* Part where message is shown */
		DisplayString( 10, 10, msg );
		DisplayNum( 1, 10, 20, i+1 );		
		emulate_time(1);	
	}

	free(msg);
}

int main(void)
{
	
	hello_world();
	return 0;
}
