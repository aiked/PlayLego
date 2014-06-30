#ifndef   _SPI_H_
#define   _SPI_H_

#include <stdconst.h>

void SPIInit(void);
unsigned int SPITxReady(void);
unsigned int SPIRxReady(void);
void SPIWrite(UBYTE *, UBYTE);
void SPIRead(UBYTE *, UBYTE);
void SPIPIOSetData(void);
void SPIPIOClearData(void);

/*
 * Bonus functionality using DMA
 */
void SPIWriteDMA(UBYTE *data, UBYTE length);
void SPIReadDMA(UBYTE *data, UBYTE length);

#endif
