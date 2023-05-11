# bmptoylib

Single header C library for creating bmp files for beginner C programmers. It cannot read or change existing files. 

The library is meant to be small and easy to use. No need for linking just include the .c file and it should work. 
Use even image dimensions (width and height) which are both divisible by 2.

I used a hex editor and created very small bmp files along with googling how the bmp file format works. Please alert me if you notice any problems.  

I was going to implement heaps more drawing functions but have decided to just keep the library simple so that programmers can use it as a base to build off of.

The code is free and without license. 

Building: 

gcc -Wall -Werror -Wfatal-errors example.c

on linux you may need -lm as in

gcc -Wall -Werror -Wfatal-errors example.c -lm

the example code illustrates how to use the library.

You will need to have the file called bmptoylib.c in the same folder as example.c or you main.c file.
