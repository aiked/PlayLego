#include <stdlib.h>
#include <assert.h>
#include "AT91SAM7S256.h"
#include "sound.h"
#include "clock.h"

/*
#if using PIT interrupts
void pit_handler(void){
	// do your thing here
	// update time on display every second
}
#endif
*/


int main(void){

	AICInit();
	
	DisplayInit();
	SoundInit();
	DisplayOn(1);
	
	//DisplayPrintTimeBusy();
	PITInterruptEnable( 0xF4240 , DisplayTime_PIT );

	/*
	ULONG pattern[] = {0xFF00FF00};
  //
  // init here 
  //
  SoundSync(pattern, sizeof(pattern)/sizeof(ULONG), 100, 10);

  while ( 1 ) {
    // update time on display every second
    if (ten seconds elapsed) {
      SoundAsync(pattern, sizeof(pattern)/sizeof(ULONG), 100, 10);
    }
  }

  //
  // cleanup here
  //
	*/

	return 0;
}
