

#include "bmptoylib.c"
#include <stdio.h>
#include <time.h>

#define img_width  1920
#define img_height 1080

void randomizecolor(RGBpixel rgbp) {
	rgbp[0] = rand() % 256;
	rgbp[1] = rand() % 256;
	rgbp[2] = rand() % 256;
}

int main() {
	// init random
	srand(time(0));

	// can set scrolling so that large images wrap around (like astroids scroll. Applies to all drawing types below) 
	setScrolling(0);

	//RGBpixel (simply an array which holds [0], [1], [2], R, G, B values respectively.)
	// background color
	RGBpixel bgcolor = {0,0,0};
	
	//RGBcanvas is what we draw to. We initialize with width, height, and a background color
	RGBcanvas rgbcanvas = createRGBcanvas(img_width, img_height, bgcolor);
	
	// we create an RGBpixel to use as forground color. Note that this is just an array so 
	// color[0] = R, color[1] = G, color[2] = B
	RGBpixel color = {255, 255, 255};

	int n;
	for (n = 0; n < 5; n++) {
		// draw a filled circle
		randomizecolor(color);
		fillcircle(&rgbcanvas, rand() % img_width, rand() % img_height, rand() % 100, color);	
		
		// draw a filled rectangle
		randomizecolor(color);
		fillrect(&rgbcanvas, rand() % img_width, rand() % img_height, rand() % img_width, rand() % img_height, color);
		
		// draw circle with desired thickness.
		randomizecolor(color);
		thickcircle(&rgbcanvas, rand() % img_width, rand() % img_height, rand() % 100, rand() % 25, color);
		
		// draw a rectangle 
		randomizecolor(color);
		rect(&rgbcanvas, rand() % img_width, rand() % img_height, rand() % img_width, rand() % img_height, 
			color);

		// draw a circle
		randomizecolor(color);
		circle(&rgbcanvas, rand() % img_width, rand() % img_height, rand() % 100, color);
		
		// draw a line
		randomizecolor(color);
		 line(&rgbcanvas, rand() % img_width, rand() % img_height, rand() % img_width, rand() % img_height, 
			 color);

		//quadrilateral
	 	randomizecolor(color);
	 	quad(&rgbcanvas, rand() % img_width, rand() % img_height, rand() % img_width, rand() % img_height, 
	 	             rand() % img_width, rand() % img_height, rand() % img_width, rand() % img_height, 
	 	             color);

		//draw pixels
		int k;
		for (k = 0; k < 100; k++) {
			randomizecolor(color);
			color[0] = k * 24;
			color[0] %= 256;
			setRGBpixel(&rgbcanvas, rand() % img_width, rand() % img_height, color);
		}
	}


	FILE * bmpf = createBMPfile(img_width, img_height, "example.bmp");

	saveBMPfile(bmpf, &rgbcanvas);
	freeRGBcanvas(&rgbcanvas);
	fclose(bmpf);

	return 0;
}
