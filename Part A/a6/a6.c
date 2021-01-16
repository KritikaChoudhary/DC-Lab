//Write an OpenMP program to convert a color image to black and white image. Demonstrate the performance of different scheduling techniques for varying chunk values.

#include<stdio.h>
#include<omp.h>
#include<gd.h>
#include<stdlib.h>
void main(int argc, char *argv[])
{
    char *inputfile = argv[0];
    char* outputfile = argv[1];

    FILE *fp1 = fopen(inputfile, "r");
    gdImagePtr image = gdImageCreateFromPng(fp1);

    int colour, red, green, blue;

    #pragma omp parallel for num_threads(8) private(colour, red, green, blue)
    {
        for(int x = 0; x < gdImageSX(image); x++)
        {
            #pragma omp critical
            {
               for(int y = 0; y < gdImageSY(image); y++)
            {
                colour = gdImageGetPixel(image, x, y);
                red = 255 - gdImageRed(image, colour);
                blue = 255 - gdImageBlue(image, colour);
                green = 255 - gdImageGreen(image, colour);
                colour = gdImageColourAllocate(image, red, green, blue);
                gdImageSetPixel(image, x, y, colour);
            }
            }
        }
    }
    FILE *fp2 = fopen(outputfile, "w");
    gdImagePng(image, fp2);
    gdDestroyImage(image);
}
