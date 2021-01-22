//Write an OpenMP program to convert a color image to black and white image. Demonstrate the performance of different scheduling techniques for varying chunk values.


#include<stdio.h>
#include<omp.h>
#include<gd.h>
#include<stdlib.h>
void main(int argc, char *argv[])
{
    char *inputfile = "dice.png";
    //argv[0];
    char* outputfile = "output.png";

    FILE *fp1 = fopen(inputfile, "r");
    gdImagePtr image = gdImageCreateFromPng(fp1);

    int colour, red, green, blue, combined;

    #pragma omp parallel for num_threads(8) private(colour, red, green, blue, combined)
   
        for(int x = 0; x < gdImageSX(image); x++)
        {
            #pragma omp critical
            {
               for(int y = 0; y < gdImageSY(image); y++)
            {
                colour = gdImageGetPixel(image, x, y);
                red = gdImageRed(image, colour);
                blue = gdImageBlue(image, colour);
                green = gdImageGreen(image, colour);
                combined = 0.3*red+0.6*green+0.1*blue;
                colour = gdImageColorAllocate(image, combined, combined, combined);
                gdImageSetPixel(image, x, y, colour);
            }
            }
        }
   
    FILE *fp2 = fopen(outputfile, "w");
    gdImagePng(image, fp2);
    //gdDestroyImage(image);
}



