#include <stdlib.h>
#include "lib/bmp_io.h"
#include "lib/bmp_transform.h"
// произвольный угол поворота
int main() {
    char* filename = "/home/maximyarosh/lab6/llp-lab-6-master/src/RS01.bmp";
    BMP_File* bmpFile = readBMP(filename);
    if(bmpFile == NULL) {
        exit(1);
    }

    char* newFilename_1 = "/home/maximyarosh/lab6/llp-lab-6-master/src/RS01_10.bmp";
    BMP_File* newBMP_1 = rotate(bmpFile, 10);
    writeBMP(newBMP_1, newFilename_1);
    free(newBMP_1);

    char* newFilename_2 = "/home/maximyarosh/lab6/llp-lab-6-master/src/RS01_45.bmp";
    BMP_File* newBMP_2 = rotate(bmpFile, 45);
    writeBMP(newBMP_2, newFilename_2);
    free(newBMP_2);

    char* newFilename_3 = "/home/maximyarosh/lab6/llp-lab-6-master/src/RS01_80.bmp";
    BMP_File* newBMP_3 = rotate(bmpFile, 80);
    writeBMP(newBMP_3, newFilename_3);
    free(newBMP_3);

    char* newFilename_4 = "/home/maximyarosh/lab6/llp-lab-6-master/src/RS01_100.bmp";
    BMP_File* newBMP_4 = rotate(bmpFile, 100);
    writeBMP(newBMP_4, newFilename_4);
    free(newBMP_4);

    char* newFilename_5 = "/home/maximyarosh/lab6/llp-lab-6-master/src/RS01_135.bmp";
    BMP_File* newBMP_5 = rotate(bmpFile, 135);
    writeBMP(newBMP_5, newFilename_5);
    free(newBMP_5);

    char* newFilename_6 = "/home/maximyarosh/lab6/llp-lab-6-master/src/RS01_170.bmp";
    BMP_File* newBMP_6 = rotate(bmpFile, 170);
    writeBMP(newBMP_6, newFilename_6);
    free(newBMP_6);

    free(bmpFile);
    return 0;
}
