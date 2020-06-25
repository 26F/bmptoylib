

/*
bmptoylib

simple bmp drawing functions (creation only; of bmp files)
with drawing functions for basic shapes
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const int headersize = 54;

// used by createBMPfile and saveBMPfile
int needpadding = 0;
int spacing = 0;

// parameters
int scrolling = 0;

// header data, leave as is.
unsigned char bmpheader[] = {
							 0x42, 0x4D, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	                         0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 
	                         0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 
	                         0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 
	                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	                        };


typedef unsigned char RGBpixel[3]; 

// RGB canvas struct
typedef struct rgbc {
	int failed;
	int width;
	int height;
	RGBpixel * RGBdata;
} RGBcanvas;

void setScrolling(int onoff) {
	scrolling = onoff;
}

RGBcanvas createRGBcanvas(int width, int height, RGBpixel rgbp) {
	RGBcanvas rgbcanvas;
	rgbcanvas.width = width;
	rgbcanvas.height = height;
	rgbcanvas.failed = 0;
	rgbcanvas.RGBdata = (RGBpixel *)malloc(width * height * sizeof(RGBpixel));

	if (rgbcanvas.RGBdata == NULL) {
		rgbcanvas.failed = 1;
		return rgbcanvas;
	}
	int c;
	for (c = 0; c < width * height; c++) {
		rgbcanvas.RGBdata[c][0] = rgbp[0];
		rgbcanvas.RGBdata[c][1] = rgbp[1];
		rgbcanvas.RGBdata[c][2] = rgbp[2];
	}
	return rgbcanvas;
}

void setRGBpixel(RGBcanvas * rgbcanvas, int x, int y, RGBpixel rgbp) {
	if (x > rgbcanvas->width-1) {
		x = (scrolling) ? x % rgbcanvas->width : rgbcanvas->width-1;
	}
	if (x < 0) { 
		x = (scrolling) ? rgbcanvas->width-1 - (abs(x) % rgbcanvas->width) : 0; 
	}

	if (y > rgbcanvas->height-1) {
		y = (scrolling) ? y % rgbcanvas->height : rgbcanvas->height-1;
	}
	if (y < 0) { 
		y = (scrolling) ? rgbcanvas->height-1 - (abs(y) % rgbcanvas->height) : 0; 
	}
	y = rgbcanvas->height-1 - y;

	rgbcanvas->RGBdata[(rgbcanvas->width * y) + x][0] = rgbp[0];
	rgbcanvas->RGBdata[(rgbcanvas->width * y) + x][1] = rgbp[1];
	rgbcanvas->RGBdata[(rgbcanvas->width * y) + x][2] = rgbp[2];
}

void line(RGBcanvas * rgbcanvas, float x, float y, float x1, float y1, RGBpixel rgbp) {
	float dy = y1 - y;
	float dx = x1 - x;
	int  itr = (abs(dy) > abs(dx)) ? abs(dy) : abs(dx);
	int c;
	dy /= itr;
	dx /= itr;
	for (c = 0; c < itr; c++) {
		setRGBpixel(rgbcanvas, x,y, rgbp);
		x += dx;
		y += dy;
	}
}

void thickline(RGBcanvas * rgbcanvas, float x, float y, float x1, float y1, int thickness, RGBpixel rgbp) {
	int c;
	for (c = 0; c < thickness; c++) {
		line(rgbcanvas, x + c, y + c, x1 + c, y1 + c, rgbp);
		line(rgbcanvas, x - c, y - c, x1 + c, y1 + c, rgbp);
		line(rgbcanvas, x - c, y - c, x1 - c, y1 - c, rgbp);
		line(rgbcanvas, x + c, y + c, x1 - c, y1 - c, rgbp);
	}
}

void circle(RGBcanvas * rgbcanvas, float x, float y, float radius, RGBpixel rgbp) {
	if (radius == 0.0) {
		radius = 1.0;
	}
	float c = 0;
	int Xp, Xn, Yp, Yn;
	float degreestorad = (M_PI / 180);
	float xaddp, xaddn, yaddp, yaddn;
	float radians;
	while (c < 90) {
		radians = c * (degreestorad);
		xaddp = radius  * sin(radians);
		xaddn = -radius * sin(radians);
		yaddp = radius  * cos(radians);
		yaddn = -radius * cos(radians);
		Xp = (int)(xaddp + x);
		Xn = (int)(xaddn + x);
		Yp = (int)(yaddp + y);
		Yn = (int)(yaddn + y);

		setRGBpixel(rgbcanvas, Xp, Yp, rgbp);
		setRGBpixel(rgbcanvas, Xp, Yn, rgbp);
		setRGBpixel(rgbcanvas, Xn, Yn, rgbp);
		setRGBpixel(rgbcanvas, Xn, Yp, rgbp);
		
		c += (1 / radius);
	}
}

void thickcircle(RGBcanvas * rgbcanvas, int x, int y, float radius, int thickness, RGBpixel rgbp) {
	int c;
	for (c = 0; c < thickness; c++) {
		circle(rgbcanvas, x, y, radius - c, rgbp);
	}
}

void fillcircle(RGBcanvas * rgbcanvas, int x, int y, float radius, RGBpixel rgbp) {
	if (radius == 0.0) {
		radius = 1.0;
	}

	float c = 0;
	float degreestorad = (M_PI / 180);
	float radians;
	float xadd, yaddp, yaddn;
	int X, Yp, Yn;
	while (c < 360) {
		radians = c * degreestorad;
		xadd = radius   * sin(radians);
		yaddp = radius  * cos(radians);
		yaddn = -radius * cos(radians);

		X  = (int)(xadd + x);
		Yp = (int)(yaddp + y);
		Yn = (int)(yaddn + y);

		line(rgbcanvas, X, Yp, X, Yn, rgbp);
		
		c += 0.01; //(1 / radius);
	}


}

FILE * createBMPfile(int width, int height, const char * filename) {
	int imagedatasize = (width * height * 3);
	if (width % 4 != 0) {
		imagedatasize = (width * height * 3) + height;
		needpadding = 1;
		spacing = width - 1;
	}
	
	int filesize = imagedatasize + headersize;

	// load hex data into bmpheader
	bmpheader[2] = (filesize & 0xFF);
	bmpheader[3] = (filesize >> 8) & 0xFF;
	bmpheader[18] = (width & 0xFF);
	bmpheader[19] = (width >> 8) & 0xFF;
	bmpheader[22] = height & 0xFF;
	bmpheader[23] = (height >> 8) & 0xFF;
	bmpheader[34] = (imagedatasize & 0xFF);
	bmpheader[35] = (imagedatasize >> 8) & 0xFF;

	FILE * bmpf = fopen(filename, "wb");
	if (bmpf == NULL) {
		return 0;
	}
	return bmpf;
}

void WriteBMPfile(FILE * f) {
	int c;
	for (c = 0; c < headersize; c++) {
		fputc(bmpheader[c], f);
	}
}

// save and close the file
void saveBMPfile(FILE * f, RGBcanvas * rgbcanvas) {
	WriteBMPfile(f);
	int c;
	int k = 0;
	int npixels = rgbcanvas->width * rgbcanvas->height;
	for (c = 0; c < npixels; c++) {
		fputc(rgbcanvas->RGBdata[c][2], f);
		fputc(rgbcanvas->RGBdata[c][1], f);
		fputc(rgbcanvas->RGBdata[c][0], f);
		if (needpadding && k % spacing == 0 && k != 0) {
			fputc(0, f);
			k = -1;
		}
		k++; 
	}
}

void freeRGBcanvas(RGBcanvas * rgbcanvas) {
	free(rgbcanvas->RGBdata);
}