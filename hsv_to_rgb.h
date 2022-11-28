
#ifndef HSV_TO_RGB
#define HSV_TO_RGB


typedef struct 
{

	double r;
	double g;
	double b;


} rgb_t;




typedef struct
{

	double h;
	double s;
	double v;

} hsv_t;




rgb_t hsv_to_rgb(hsv_t in);


#endif // HSV_TO_RGB