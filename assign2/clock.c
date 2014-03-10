#include <clock.h>

volatile ULONG hh = 0;
volatile ULONG mm = 0;
volatile ULONG ss = 0;
// Interrupt counter
volatile UBYTE in = 0;

void DisplayTime_PIT(void){

		PITAckInterrupt();		

		++in;

		if(in==3){

			in=0;
			++ss;
		
			if( ss==5 ){
				PITInterruptDisable();
			}
			
			// Reset sec
			if(ss == 60){
				++mm;
				ss = 0;
			}

			// Reset min
			if(mm == 60){
				++hh;
				mm = 0;
			}

			// Reset hours
			if(hh == 24){
				hh = 0; 
			}
			DisplayPrintTime(hh, mm, ss);
		}
}
