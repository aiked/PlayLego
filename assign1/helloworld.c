#include "helloworld.h"

void waste_time( UWORD _time ){
	
	UWORD i, limit = _time*S_SEC;

	for(i=0;i<limit;++i){
		DisplayUpdateSync();
	}
}

void hello_world( UWORD times ){
	
	int i;
	UBYTE *msg = "Hello World!";

	for(i=0;i<times;++i){

		/* Part: Clear screen */
		DisplayErase();
		waste_time(1);

		/* Part: Print message to screen */
		DisplayString( 10, 10, msg );
		DisplayNum( 1, 10, 20, i+1 );
		waste_time(1);
	}

}
