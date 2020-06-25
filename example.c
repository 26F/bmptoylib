
#include "bmptoylib.c"
#include <stdio.h>

#define img_width  640
#define img_height 480

int main() {

	setScrolling(1);

	RGBpixel bgcolor = {0,0,0};
	RGBcanvas rgbcanvas = createRGBcanvas(img_width, img_height, bgcolor);
	RGBpixel color = {255, 255, 255};

	//setRGBpixel(&rgbcanvas, img_width / 2, img_height / 2, color);

	//circle(&rgbcanvas, img_width / 2, img_height / 2, 1000 * c, (RGBpixel){c * 25, c * 25, c * 25});
	thickcircle(&rgbcanvas, img_width / 2, img_height / 2, 40, 40, color);
	//fillcircle(&rgbcanvas, img_width / 2, img_height / 2, 150, color);

	line(&rgbcanvas, 0, 0, img_width, img_height, (RGBpixel){255, 0, 0});
	//thickline(&rgbcanvas, 0, 0, img_width, img_height, 20, (RGBpixel){255, 0, 0});
	

	FILE * bmpf = createBMPfile(img_width, img_height, "cool.bmp");

	saveBMPfile(bmpf, &rgbcanvas);
	freeRGBcanvas(&rgbcanvas);
	fclose(bmpf);

	return 0;
}