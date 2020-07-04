# bmptoylib

Single header C library for creating bmp files. It cannot read or change existing files. 

The library is meant to be small and easy to use. No need for linking just include the header file and it should work (so far only tested on windows 10.) 
Some dimensions will not work due to my lack of understanding of the bmp file format, recommend dimensions (width and height) which are both divisible by 2.
I used a hex editor and created very small bmp files along with googling how the bmp file format works. Please alert me if you notice any problems.  

Some drawing functions are yet to be implemented so are commented out in the source code. I will try and impliment a few more functions and then stop growing the library, as it is meant as a small singler header library which is easy to use and simple. 

The library here should work with all of the functions used in the examples. 

