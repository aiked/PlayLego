#include "AT91SAM7S256.h"
#include  <stdconst.h>
#include  <string.h>
#include  <assert.h>
#include  "i2c.h"
#include  "arm2avr.h"
#include  "aic.h"

#define BYTES_TO_TX     sizeof(IOTOAVR)
#define BYTES_TO_RX     sizeof(IOFROMAVR)
#define TIMEOUT         2100
#define I2CClk          400000L
#define TIME400KHz      (((OSC/16L)/(I2CClk * 2)) + 1)
#define CLDIV           (((OSC/I2CClk)/2)-3)
#define DEVICE_ADR      0x01
#define COPYRIGHTSTRING "Let's samba nxt arm in arm, (c)LEGO System A/S"
#define COPYRIGHTSTRINGLENGTH 46
const   UBYTE CopyrightStr[] = {"\xCC"COPYRIGHTSTRING};
#define MAX(x,y) (((x)>(y))?(x):(y))
#define piir (*AT91C_PITC_PIIR & AT91C_PITC_CPIV)
#define pimr (*AT91C_PITC_PIMR & AT91C_PITC_CPIV)
#define DISABLEI2cIrqs *AT91C_TWI_IDR = 0x000001C7

// User defines
#define S_BUF 100
#define MSTR_MOD_RD ((unsigned int) 0x01 << 12)
#define MSTR_MOD_WR ((unsigned int) 0x00 << 12)

// extern at arm2avr.h
IOTOAVR IoToAvr;
IOFROMAVR IoFromAvr;

// send/receive state machine variables
static enum state_t {
	Init,
	TxWait,
	Tx,
	Rx,
	RxWait
};

static ULONG I2Ctimer;
static enum state_t volatile State;

// For I2C_transfer to know to Init() or not 
static UBYTE st_Init = 0;

// Buffers for ToAvr & FromAvr
UBYTE buf_Tx[S_BUF];
UBYTE buf_Rx[S_BUF];

// Counters
unsigned int SumBytes; 
unsigned int CntBytes;


/* ------ Supporting Functions ------------- */

UBYTE chkSum( UBYTE *buf, UBYTE len ){
	UBYTE i, retval=0;
	for(i=0;i<len;++i){ retval += buf[i]; }
	return ~retval;
}

inline
I2cDoTime(void)
{
	I2Ctimer = piir;
}


inline int
I2CheckTime(void)
{
	if(TIMEOUT < ((piir - I2Ctimer) & AT91C_PITC_CPIV))
		{
		return TRUE;
		}
	else
		{
		return FALSE;
		}
}

/* ------------- Functions -------------------------------*/

__ramfunc void I2cHandler(void) {
	
	if( (State=TxWait) && ( (*AT91C_TWI_SR & AT91C_TWI_TXRDY)!=0 )){
		
		*AT91C_TWI_THR = buf_Tx[CntBytes];
		++CntBytes;

		// Last byte of stream
		if( CntBytes==SumBytes-1 ){
			*AT91C_TWI_CR = AT91C_TWI_STOP;
		}

		// Stream is complete
		if( CntBytes==SumBytes ){
			State = Rx;
			*AT91C_TWI_IDR |= AT91C_TWI_TXRDY;
			return;
		}

	}
	else if ( (State=Rx) && ( (*AT91C_TWI_SR & AT91C_TWI_RXRDY)!=0 )){

		buf_Rx[CntBytes] = *AT91C_TWI_RHR;
		++CntBytes;

		// Last byte of stream
		if( CntBytes==SumBytes-1 ){
			*AT91C_TWI_CR = AT91C_TWI_STOP;
		}

		// Stream is complete
		if( CntBytes==SumBytes ){
			memcpy( &IoFromAvr, buf_Rx, sizeof(IoFromAvr) );
			State = Tx;
			*AT91C_TWI_IDR |= AT91C_TWI_RXRDY;
			return;
		}

	}
}


void DataTxInit(UBYTE *buf, UBYTE len) {

	SumBytes = len+1;
	CntBytes = 0;

	memcpy( buf_Tx, buf, len );
	buf_Tx[len] = chkSum(buf,len);

	AICInterruptEnable( AT91C_ID_TWI ,(void*)I2cHandler );

	*AT91C_TWI_MMR = ( (DEVICE_ADR<<16) | MSTR_MOD_WR );
	*AT91C_TWI_CR  = AT91C_TWI_MSEN | AT91C_TWI_START;
	*AT91C_TWI_IER |= AT91C_TWI_TXRDY; 

	return;
}  


void DataRxInit(UBYTE *buf, UBYTE len) {

	SumBytes = len+1;
	CntBytes = 0;

	AICInterruptEnable( AT91C_ID_TWI ,(void*)I2cHandler);

	*AT91C_TWI_MMR = ( (DEVICE_ADR<<16) | MSTR_MOD_RD );
	*AT91C_TWI_CR  = AT91C_TWI_MSEN | AT91C_TWI_START;
	*AT91C_TWI_IER |= AT91C_TWI_RXRDY; 

	return;
}


void I2CTransfer(void) {

	// Init the I2C
	if (st_Init){	
		DataTxInit((UBYTE*)CopyrightStr, sizeof(CopyrightStr));
		State   = TxWait;
		st_Init = 0;
		// Init the time
	}
	
	if (I2CheckTime()){
		switch(State){
			case Tx:
				DataTxInit( (UBYTE*) &IoToAvr, BYTES_TO_TX);
				State = TxWait;
				break;
			case Rx:
				DataRxInit( (UBYTE*) &IoFromAvr, BYTES_TO_RX);
				State = RxWait;
				break;
			default:
				return;
		}
	}

	return;
}


void I2CCtrl (enum power_t p) {
	IoToAvr.Power = p;
	return;
}

#define WAITClk(t) {			\
	  ULONG pit = piir + (t);	\
          if (pit >= pimr) pit -= pimr;	\
          while (piir < pit){;}		\
        }

void I2CInit(void) { 
  //
  // disable I2C on PIO
  // this is called also during an error, so interrupts etc may be enabled
  //
  *AT91C_AIC_IDCR = (1L<<AT91C_ID_TWI);			/* disable AIC irq  */
  DISABLEI2cIrqs;                      			/* disable TWI irq  */
  *AT91C_PMC_PCER  = (1L<<AT91C_ID_TWI);		/* enable TWI Clock */
  *AT91C_PIOA_OER  = AT91C_PA4_TWCK;  		  	/* SCL is output    */
  *AT91C_PIOA_ODR  = AT91C_PA3_TWD;			/* SDA is input     */
  *AT91C_PIOA_MDER = (AT91C_PA4_TWCK | AT91C_PA3_TWD);  /* open drain       */
  *AT91C_PIOA_PPUDR = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* no pull up       */
  // 
  // synch I2C clocks using PIO
  // generate a 400KHz pulse on SCK and wait until both SCK and SDA are high, 
  // which means the slave ticks with this clock
  //
  *AT91C_PIOA_PER  = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* enable PIO control for these pins */
  while(((*AT91C_PIOA_PDSR & AT91C_PA3_TWD) == 0) || ((*AT91C_PIOA_PDSR & AT91C_PA4_TWCK) == 0)){
      *AT91C_PIOA_CODR = AT91C_PA4_TWCK; /* drive SCL Low  */
      WAITClk(TIME400KHz);
      *AT91C_PIOA_SODR = AT91C_PA4_TWCK; /* drive SCL High */
      WAITClk(TIME400KHz);
  }
  // 
  // init I2C on PIO
  //
  *AT91C_TWI_CR    =  AT91C_TWI_SWRST;			/* this has to happen before the rest */
  *AT91C_PIOA_PDR   = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* disable PIO control for these pins */
  *AT91C_PIOA_ASR   = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* select peripheral A = TWI */
  *AT91C_TWI_CWGR   = (CLDIV | (CLDIV << 8));           /* 400KHz clock    */
  *AT91C_AIC_ICCR   = (1L<<AT91C_ID_TWI);               /* clear AIC irq   */
  AT91C_AIC_SVR[AT91C_ID_TWI] = (unsigned int)I2cHandler;
  AT91C_AIC_SMR[AT91C_ID_TWI] = ((AT91C_AIC_PRIOR_HIGHEST) | (AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED));
  *AT91C_AIC_IECR   = (1L<<AT91C_ID_TWI);               /* Enables AIC irq */

  IoToAvr.Power     = 0;

	// Theory michath
	//st_i2c = Init;

  return;
}

void I2CExit(void) {
  DISABLEI2cIrqs;
  *AT91C_AIC_IDCR   = (1L<<AT91C_ID_TWI);               /* Disable AIC irq  */
  *AT91C_AIC_ICCR   = (1L<<AT91C_ID_TWI);               /* Clear AIC irq    */
  *AT91C_PMC_PCDR   = (1L<<AT91C_ID_TWI);               /* Disable clock    */
  *AT91C_PIOA_MDER  = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* Open drain       */
  *AT91C_PIOA_PPUDR = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* no pull up       */
  *AT91C_PIOA_PER   = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* Disable peripheal*/
}
