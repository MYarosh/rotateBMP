#ifndef LLP_LAB_5_6__BMP_TRANSFORM_H
#define LLP_LAB_5_6__BMP_TRANSFORM_H

#include "bmp_struct.h"

void printInformationBMP(BMP_File *bmp);

BMP_File* rotate(BMP_File *bmpFile, int angelOfDegrees);
RGBQuad* getPixel(BMP_File *bmp, int x, int y);
BMP_File* copyEmptyBMP(BMP_File *bmpFile);

#endif //LLP_LAB_5_6__BMP_TRANSFORM_H
