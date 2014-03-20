#include <stdlib.h>
#include <assert.h>
#include "spi.h"
#include "AT91SAM7S256.h"


int main(void){
	DisplayInit();

	DisplaySetPixel(1,1);
	DisplayUpdateSync();
	return 0;
}
