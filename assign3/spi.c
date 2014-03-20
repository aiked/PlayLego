#include "AT91SAM7S256.h"
#include  "spi.h"

#define SPI_BITRATE 2000000

void SPIInit(void) {
	*AT91C_PMC_PCER             = (1L << AT91C_ID_SPI);   /* Enable MCK clock     */
	// map the multiplexed pins of PIO to SPI
	*AT91C_PIOA_PER             = AT91C_PIO_PA12;         /* Enable A0 on PA12    */
	*AT91C_PIOA_OER             = AT91C_PIO_PA12;
	*AT91C_PIOA_CODR            = AT91C_PIO_PA12;
	*AT91C_PIOA_PDR             = AT91C_PA14_SPCK;        /* Enable SPCK on PA14  */
	*AT91C_PIOA_ASR             = AT91C_PA14_SPCK;
	*AT91C_PIOA_ODR             = AT91C_PA14_SPCK;
	*AT91C_PIOA_OWER            = AT91C_PA14_SPCK;
	*AT91C_PIOA_MDDR            = AT91C_PA14_SPCK;
	*AT91C_PIOA_PPUDR           = AT91C_PA14_SPCK;
	*AT91C_PIOA_IFDR            = AT91C_PA14_SPCK;
	*AT91C_PIOA_CODR            = AT91C_PA14_SPCK;
	*AT91C_PIOA_IDR             = AT91C_PA14_SPCK;
	*AT91C_PIOA_PDR             = AT91C_PA13_MOSI;        /* Enable mosi on PA13  */
	*AT91C_PIOA_ASR             = AT91C_PA13_MOSI;
	*AT91C_PIOA_ODR             = AT91C_PA13_MOSI;
	*AT91C_PIOA_OWER            = AT91C_PA13_MOSI;
	*AT91C_PIOA_MDDR            = AT91C_PA13_MOSI;
	*AT91C_PIOA_PPUDR           = AT91C_PA13_MOSI;
	*AT91C_PIOA_IFDR            = AT91C_PA13_MOSI;
	*AT91C_PIOA_CODR            = AT91C_PA13_MOSI;
	*AT91C_PIOA_IDR             = AT91C_PA13_MOSI;
	*AT91C_PIOA_PDR             = AT91C_PA10_NPCS2;       /* Enable npcs0 on PA11  */
	*AT91C_PIOA_BSR             = AT91C_PA10_NPCS2;
	*AT91C_PIOA_ODR             = AT91C_PA10_NPCS2;
	*AT91C_PIOA_OWER            = AT91C_PA10_NPCS2;
	*AT91C_PIOA_MDDR            = AT91C_PA10_NPCS2;
	*AT91C_PIOA_PPUDR           = AT91C_PA10_NPCS2;
	*AT91C_PIOA_IFDR            = AT91C_PA10_NPCS2;
	*AT91C_PIOA_CODR            = AT91C_PA10_NPCS2;
	*AT91C_PIOA_IDR             = AT91C_PA10_NPCS2;
	// init the SPI
	*AT91C_SPI_CR               = AT91C_SPI_SWRST;        /* Soft reset           */
	*AT91C_SPI_CR               = AT91C_SPI_SPIEN;        /* Enable spi           */
	*AT91C_SPI_MR               = AT91C_SPI_MSTR  | AT91C_SPI_MODFDIS | (0xB << 16);
	AT91C_SPI_CSR[2]              = ((OSC / SPI_BITRATE) << 8) | AT91C_SPI_CPOL;

	return;
}

unsigned int SPITxReady(void){
	return (unsigned int)(*AT91C_SPI_SR & AT91C_SPI_TXEMPTY);
}


unsigned int SPIRxReady(void){
	return (unsigned int)(*AT91C_SPI_SR & AT91C_SPI_RDRF);
}


void SPIPIOSetData(void){
	*AT91C_PIOA_SODR = AT91C_PIO_PA12;
}


void SPIPIOClearData(void){
	*AT91C_PIOA_CODR = AT91C_PIO_PA12;
}


void SPIWrite(UBYTE *data, UBYTE length){
	UBYTE i;

	for(i=0;i<length;++i){
		while(!SPITxReady()){ ; }
		*AT91C_SPI_TDR = data[i];
	}
}

/*
void SPIRead(UBYTE *data, UBYTE length){
	UBYTE i;

	for(i=0;i<length;++i){
		while(!SPIRxReady()){ ; }
		// SPI_RD is used to cover the 4 ms bytes of register ??
		data[i] = (*AT91C_SPI_RDR & AT91C_SPI_RD); 
	}
}
*/

void SPIWriteDMA(UBYTE *data, UBYTE length){
	
	// Loop until Transmit is possible
	while(!SPITxReady()){ ; }

	*AT91C_SPI_PTCR = AT91C_PDC_TXTEN;
	*AT91C_SPI_TPR = (unsigned int)data;
	*AT91C_SPI_TCR = (unsigned int)length;
}


/*
void SPIReadDMA(UBYTE *data, UBYTE length){
	
	// Loop until Receive is possible
	while(!SPIRxREADY()){ ; }

	*AT91C_SPI_RNCR = AT91C_PDC_TXTEN;
	*AT91C_SPI_RPR = (unsigned int)data;
	*AT91C_SPI_RCR = (unsigned int)length;
}
*/