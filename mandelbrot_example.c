
#include <stdio.h>
#include "bmptoylib.c"

const int WIDTH = 1920;
const int HEIGHT = 1080;
const unsigned int ITERATIONS = 256;

const double zoom = 0.0025;
const double camera2Dx = -WIDTH  / 2;
const double camera2Dy = -HEIGHT / 2;

unsigned char bouncingmodulus(unsigned char n) {
	if (n <= 254) {
		return n;
	}
	if (n > 254) {
		return 255 - (n % 255);
	}
}

int main() {
	int x, y;
	unsigned int i;
	double zx, zy, cx, cy, temp;

	RGBcanvas canvas = createRGBcanvas(WIDTH, HEIGHT, (RGBpixel){0,0,0});
	
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			cx = ((double)x + camera2Dx) * zoom;
			cy = ((double)y + camera2Dy) * zoom;
			zx = 0;
			zy = 0;
			i  = 0;
			while (zx * zx + zy * zy < 4.0 && i < ITERATIONS) {
				temp = zx * zx - zy * zy + cx;
				zy = 2 * zx * zy + cy;
				zx = temp;
				i++;
			}
			i *= 30;
			setRGBpixel(&canvas, x, y, (RGBpixel){bouncingmodulus(i), 
				bouncingmodulus(i + 20), bouncingmodulus( i + 50)});
		}
	}

	FILE * bmpf = createBMPfile(WIDTH, HEIGHT, "cool.bmp");
	saveBMPfile(bmpf, &canvas);
	freeRGBcanvas(&canvas);
	fclose(bmpf);

	return 0;
}