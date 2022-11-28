
#include <stdio.h>
#include "hsv_to_rgb.h"


rgb_t hsv_to_rgb(hsv_t in)
{

	double hh, p, q, t, ff;
	long i;
	rgb_t out;

	if (in.s <= 0.0) {

		out.r = in.v;
		out.g = in.v;
		out.b = in.v;

		return out;

	}


	hh = in.h;

	if (hh >= 360.0) {

		hh = 0.0;

	}

	hh /= 60.0;

	i = (long)hh;

	ff = hh - i;

	p = in.v * (1.0 - in.s);
	q = in.v * (1.0 - (in.s * ff));
	t = in.v * (1.0 - (in.s * (1.0 - ff)));

	switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;

}
