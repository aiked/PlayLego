#include "assert.h"
#include "AT91SAM7S256.h"
#include "display.h"
#include "spi.h"

#define	DISPLAY_HEIGHT	64	// Y pixels
#define	DISPLAY_WIDTH	100	// X pixels
#define	DISP_LINES	8	// (DISPLAY_HEIGHT/8)
#define	G_WIDTH		6	// Char width
#define G_HEIGHT	8	// Char height


static struct {
	UBYTE DataArray[DISPLAY_HEIGHT / 8][DISPLAY_WIDTH];
} IOMapDisplay;


UBYTE DisplayInitCommands[] =
{
	0xEB, // [0]  LCD bias: 1/9=0xEB
	0x2F, // [1]  pump control: set build-in=0x2F
	0xA4, // [2]  all pixels: off=0xA4, on=0xA5
	0xA6, // [3]  inverse: off=0xA6, on=0xA7
	0x40, // [4]  set scroll line: 0=0x40-63=0x7F
	0x81, // [5]  set Vbias potentiometer (2-byte command): 0x81 
	0x5A, // [6]  -"-	             : on=0x5A, off=0x00
	0xC4, // [7]  LCD mapping: regular=0xC4, row-mirror=bit 2,
	      //      col-mirror=bit 3, e.g. col-mirror=0xC2
	0x27, // [8]  set temp comp.: -0.20%/C=0x27
	0x29, // [9]  panel loading: <=15nF=0x28, >15nF=0x29
	0xA0, // [10] framerate: 76fps=0xA0, 95fps=0xA1
	0x88, // [11] RAM address control: no wrap around+no autoincremet=0x88
	0x23, // [12] set multiplex rate: 1:65=0x23
	0xAF  // [13] set display: on=0xAF, off=0xAE
};


typedef struct{
	UBYTE   ItemPixelsX;
	UBYTE   ItemPixelsY;
	UBYTE   Data[];
} __attribute__((__packed__)) FONT, ICON;


UBYTE DisplayLineString[DISP_LINES][3] =
{
	{ 0xB0, 0x10, 0x00 },
	{ 0xB1, 0x10, 0x00 },
	{ 0xB2, 0x10, 0x00 },
	{ 0xB3, 0x10, 0x00 },
	{ 0xB4, 0x10, 0x00 },
	{ 0xB5, 0x10, 0x00 },
	{ 0xB6, 0x10, 0x00 },
	{ 0xB7, 0x10, 0x00 }
};


const ICON Font = {
 	// each character is 6x8 pixels represented as 6 bytes, where each byte is a "column" of 8 pixels
	0x06,      // Graphics Width
 	0x08,      // Graphics Height
  	{
	/* 32 first non-printable characters */
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x00,0x00,0x00,0x00,0x00,
  	/* rest printable characters */
	0x00,0x00,0x00,0x00,0x00,0x00,	0x00,0x06,0x5F,0x06,0x00,0x00,	0x07,0x03,0x00,0x07,0x03,0x00,
	0x24,0x7E,0x24,0x7E,0x24,0x00,	0x24,0x2B,0x6A,0x12,0x00,0x00,	0x63,0x13,0x08,0x64,0x63,0x00,
	0x30,0x4C,0x52,0x22,0x50,0x00,	0x00,0x07,0x03,0x00,0x00,0x00,	0x00,0x3E,0x41,0x00,0x00,0x00,
	0x00,0x41,0x3E,0x00,0x00,0x00,	0x08,0x3E,0x1C,0x3E,0x08,0x00,	0x08,0x08,0x3E,0x08,0x08,0x00,
	0x80,0x60,0x60,0x00,0x00,0x00,	0x08,0x08,0x08,0x08,0x08,0x00,	0x00,0x60,0x60,0x00,0x00,0x00,
	0x20,0x10,0x08,0x04,0x02,0x00, 	0x3E,0x51,0x49,0x45,0x3E,0x00,	0x00,0x42,0x7F,0x40,0x00,0x00,
	0x62,0x51,0x49,0x49,0x46,0x00,	0x22,0x49,0x49,0x49,0x36,0x00,	0x18,0x14,0x12,0x7F,0x10,0x00,
	0x2F,0x49,0x49,0x49,0x31,0x00,	0x3C,0x4A,0x49,0x49,0x30,0x00,	0x01,0x71,0x09,0x05,0x03,0x00,
	0x36,0x49,0x49,0x49,0x36,0x00,	0x06,0x49,0x49,0x29,0x1E,0x00,	0x00,0x6C,0x6C,0x00,0x00,0x00,
	0x00,0xEC,0x6C,0x00,0x00,0x00,	0x08,0x14,0x22,0x41,0x00,0x00,	0x24,0x24,0x24,0x24,0x24,0x00,
	0x00,0x41,0x22,0x14,0x08,0x00,	0x02,0x01,0x59,0x09,0x06,0x00,	0x3E,0x41,0x5D,0x55,0x1E,0x00,
	0x7E,0x11,0x11,0x11,0x7E,0x00,	0x7F,0x49,0x49,0x49,0x36,0x00,	0x3E,0x41,0x41,0x41,0x22,0x00,
	0x7F,0x41,0x41,0x41,0x3E,0x00,	0x7F,0x49,0x49,0x49,0x41,0x00,	0x7F,0x09,0x09,0x09,0x01,0x00,
	0x3E,0x41,0x49,0x49,0x7A,0x00,	0x7F,0x08,0x08,0x08,0x7F,0x00,	0x00,0x41,0x7F,0x41,0x00,0x00,
	0x30,0x40,0x40,0x40,0x3F,0x00,	0x7F,0x08,0x14,0x22,0x41,0x00,	0x7F,0x40,0x40,0x40,0x40,0x00,
	0x7F,0x02,0x04,0x02,0x7F,0x00,	0x7F,0x02,0x04,0x08,0x7F,0x00,	0x3E,0x41,0x41,0x41,0x3E,0x00,
	0x7F,0x09,0x09,0x09,0x06,0x00,	0x3E,0x41,0x51,0x21,0x5E,0x00,	0x7F,0x09,0x09,0x19,0x66,0x00,
	0x26,0x49,0x49,0x49,0x32,0x00,	0x01,0x01,0x7F,0x01,0x01,0x00,	0x3F,0x40,0x40,0x40,0x3F,0x00,
	0x1F,0x20,0x40,0x20,0x1F,0x00,	0x3F,0x40,0x3C,0x40,0x3F,0x00,	0x63,0x14,0x08,0x14,0x63,0x00,
	0x07,0x08,0x70,0x08,0x07,0x00,	0x71,0x49,0x45,0x43,0x00,0x00,	0x00,0x7F,0x41,0x41,0x00,0x00,
	0x02,0x04,0x08,0x10,0x20,0x00,	0x00,0x41,0x41,0x7F,0x00,0x00,	0x04,0x02,0x01,0x02,0x04,0x00,
	0x80,0x80,0x80,0x80,0x80,0x00,  0x00,0x02,0x05,0x02,0x00,0x00,	0x20,0x54,0x54,0x54,0x78,0x00,
	0x7F,0x44,0x44,0x44,0x38,0x00,	0x38,0x44,0x44,0x44,0x28,0x00,	0x38,0x44,0x44,0x44,0x7F,0x00,
	0x38,0x54,0x54,0x54,0x08,0x00,	0x08,0x7E,0x09,0x09,0x00,0x00,	0x18,0x24,0xA4,0xA4,0xFC,0x00,
	0x7F,0x04,0x04,0x78,0x00,0x00,	0x00,0x00,0x7D,0x40,0x00,0x00,	0x40,0x80,0x84,0x7D,0x00,0x00,
	0x7F,0x10,0x28,0x44,0x00,0x00,	0x00,0x00,0x7F,0x40,0x00,0x00,	0x7C,0x04,0x18,0x04,0x78,0x00,
	0x7C,0x04,0x04,0x78,0x00,0x00,	0x38,0x44,0x44,0x44,0x38,0x00,	0xFC,0x44,0x44,0x44,0x38,0x00,
	0x38,0x44,0x44,0x44,0xFC,0x00,	0x44,0x78,0x44,0x04,0x08,0x00,	0x08,0x54,0x54,0x54,0x20,0x00,
	0x04,0x3E,0x44,0x24,0x00,0x00,	0x3C,0x40,0x20,0x7C,0x00,0x00,	0x1C,0x20,0x40,0x20,0x1C,0x00,
	0x3C,0x60,0x30,0x60,0x3C,0x00,	0x6C,0x10,0x10,0x6C,0x00,0x00,	0x9C,0xA0,0x60,0x3C,0x00,0x00,
	0x64,0x54,0x54,0x4C,0x00,0x00,	0x08,0x3E,0x41,0x41,0x00,0x00,	0x00,0x00,0x77,0x00,0x00,0x00,
	0x00,0x41,0x41,0x3E,0x08,0x00,	0x02,0x01,0x02,0x01,0x00,0x00,	0x10,0x20,0x40,0x38,0x07,0x00
	}
};


/****** API ******/

void DisplayInit(void){
	SPIInit();
	DisplayErase();
}


void DisplayExit(void){
	DisplayInitCommands[6] 	= 0x00;
	DisplayInitCommands[13] = 0xAE; 
}


void DisplayUpdateSync(void){

        UBYTE i;
        UBYTE *pImage = (UBYTE*)IOMapDisplay.DataArray;

        DisplayWrite(COMMAND, (UBYTE*) DisplayInitCommands, sizeof(DisplayInitCommands));

        for(i = 0; i < DISP_LINES; ++i){
                while(!DisplayWrite(COMMAND, (UBYTE*) DisplayLineString[i], 3)){ ; }
                while(!DisplayWrite(DATA, (UBYTE*) &pImage[i*DISPLAY_WIDTH], DISPLAY_WIDTH)){ ; }
        }
}


void DisplaySetPixel(UBYTE X, UBYTE Y){
	assert(X <= DISPLAY_WIDTH);
	assert(Y <= DISPLAY_HEIGHT);
	IOMapDisplay.DataArray[ 0 ][(Y / 8) * DISPLAY_WIDTH + X] |= (1 << (Y % 8));
}


void DisplayClrPixel(UBYTE X, UBYTE Y){
	assert(X <= DISPLAY_WIDTH);
	assert(Y <= DISPLAY_HEIGHT);
	IOMapDisplay.DataArray[0][(Y / 8) * DISPLAY_WIDTH + X] &= ~(1 << (Y % 8));	
}


void DisplayLineX(UBYTE X1, UBYTE X2, UBYTE Y){
	UBYTE x;

	for(x = X1; x < X2; x++)
		IOMapDisplay.DataArray[0][Y * DISPLAY_WIDTH + x] |= (1 << (Y % 8));
}


void DisplayLineY(UBYTE X, UBYTE Y1, UBYTE Y2){
	UBYTE y;

	for(y = Y1; y < Y2; y++)
		IOMapDisplay.DataArray[0][(y / 8) * DISPLAY_WIDTH + X] |= (1 << (y % 8));
}


void DisplayErase(void){
	UBYTE x, y;

	for(x = 0; x < 100; x++){
		for(y = 0; y < 64; y++){
			DisplayClrPixel(x, y);
		}
	}
}


void DisplayChar(UBYTE X, UBYTE Y, UBYTE Char){

	const ICON *ass3_Font = &Font;
	UBYTE *char_matrix = (UBYTE*)&ass3_Font->Data[G_WIDTH * Char];

	UBYTE x, y;
	for(x = 0; x < G_WIDTH; ++x){
	      for(y = 0; y < G_HEIGHT; ++y){
			if((char_matrix[x] & (0x1<<y)) == (0x1<<y))
				DisplaySetPixel(X+x, Y+y);
	      }
	}
}


void DisplayNum(UBYTE X,UBYTE Y,ULONG Num){

}


void DisplayString(UBYTE X,UBYTE Y,UBYTE *pString){

}


UBYTE DisplayWrite( UBYTE type, UBYTE *data, UWORD length  ){
	if ( SPITxReady() ){
		switch(type){
			case COMMAND:
				SPIPIOClearData();
				break;
			case DATA:
				SPIPIOSetData();
				break;
		}
		// SPIWrite(data, length);
		SPIWriteDMA(data, length);
		return true;
	}
	return false;
}


void DisplayDigitalClock(UBYTE cx, UBYTE cy, UBYTE hh, UBYTE mm, UBYTE ss){
	DisplayNum(cx, cy, hh/10);
	DisplayNum(cx+6, cy, hh%10);

	DisplayChar(cx+11, cy, ':');

	DisplayNum(cx+15, cy, mm/10);
	DisplayNum(cx+21, cy, mm%10);

	DisplayChar(cx+26, cy, ':');

	DisplayNum(cx+30, cy, ss/10);
	DisplayNum(cx+36, cy, ss%10);
}


void DisplayAnalogClock(UBYTE cx, UBYTE cy, UBYTE r, UBYTE hh, UBYTE mm, UBYTE ss){
	AclockDisplayFrame(cx, cy, r);
//	AclockDisplayHand(cx, cy, r, MIN_SEC2DEG(ss), SEC);
//	AclockDisplayHand(cx, cy, r, MIN_SEC2DEG(mm), MIN);
//	AclockDisplayHand(cx, cy, r, HOUR2DEG(hh), HOUR);
	AclockDisplayFrameSymbol(cx, cy, r, 0);
}
