#include "aclock.h"

void AclockDisplayFrame(UBYTE cx, UBYTE cy, UBYTE r){

	int x = 0;
	int y = r;
	int p = 1-r;

	DisplaySetPixel( cx+x, cy-y );
	DisplaySetPixel( cx+y, cy-x );
	DisplaySetPixel( cx+x, cy+y );
	DisplaySetPixel( cx+y, cy+x );
	DisplaySetPixel( cx-x, cy+y );
	DisplaySetPixel( cx-y, cy+x );
	DisplaySetPixel( cx-x, cy-y );
	DisplaySetPixel( cx-y, cy-x );

	for(x=0;y>x;++x){
		if(p<0)
       		p += 2*x + 1;
    	else{
       		p += 2*(x-y) + 3;
       		--y;
      	}

		DisplaySetPixel( cx+x, cy-y );
		DisplaySetPixel( cx+y, cy-x );
		DisplaySetPixel( cx+x, cy+y );
		DisplaySetPixel( cx+y, cy+x );
		DisplaySetPixel( cx-x, cy+y );
		DisplaySetPixel( cx-y, cy+x );
		DisplaySetPixel( cx-x, cy-y );
		DisplaySetPixel( cx-y, cy-x );
	}
}

void AclockDisplayHand(UBYTE cx, UBYTE cy, UBYTE r, UWORD angle, Time_Mode_t mode){
	
	UBYTE i;
	// Final points
	double x, y;
	// Direction Factor
	double dir, idir;
	
	x = cx + cos( (90-angle)*PI/180 )*r;
	y = cy - sin( (90-angle)*PI/180 )*r;
	dir = (double)((y-cy)/(x-cx));
	idir = (double)((x-cx)/(y-cy));


	if(x-cx>0){
		for(i=cx;i<x;++i){ 
			if((mode==HOUR)&&(i<(x+cx)/2)) { DisplaySetPixel(i, (dir*(i-cx))+cy); } 
			if(mode==MIN){ DisplaySetPixel(i, dir*(i-cx)+cy); }
			if((mode==SEC)&&(i%4>1)){ DisplaySetPixel(i, (dir*(i-cx))+cy); }
		}
	}
	else{
		for(i=x;i<cx;++i){ 
			if((mode==HOUR)&&(i>(x+cx)/2)){ DisplaySetPixel(i, (dir*(i-x))+y); } 
			if(mode==MIN){ DisplaySetPixel(i, dir*(i-x)+y); }
			if((mode==SEC)&&(i%4>1)){ DisplaySetPixel(i, (dir*(i-x))+y); }
		}
	}

	if(y-cy>0){
		for(i=cy;i<y;++i){ 
			if((mode==HOUR)&&(i<(y+cy)/2)){ DisplaySetPixel( (idir*(i-cy))+cx, i); } 
			if(mode==MIN){ DisplaySetPixel( (idir*(i-cy))+cx, i); }
			if((mode==SEC)&&(i%4>1)){ DisplaySetPixel( (idir*(i-cy))+cx, i); }
		} 
	}
	else{
		for(i=y;i<cy;++i){ 
			if((mode==HOUR)&&(i>(y+cy)/2)){ DisplaySetPixel((idir*(i-y))+x, i); } 
			if(mode==MIN){ DisplaySetPixel((idir*(i-y))+x, i); }
			if((mode==SEC)&&(i%4>1)){ DisplaySetPixel((idir*(i-y))+x, i); }
		} 
	}
}

void AclockDisplayFrameSymbol(UBYTE cx, UBYTE cy, UBYTE r, UWORD hh){
	// Display Numeric Legend
	DisplayNum(cx-6, cy-r-8, 12);
	DisplayNum(cx+r+2, cy-3, 3);
	DisplayNum(cx-2, cy+r+2, 6);
	DisplayNum(cx-r-6, cy-3, 9);
}
