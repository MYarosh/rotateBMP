#include "bmp_transform.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

void printInformationBMP(BMP_File *bmpFile) {
    BitMapFileHeader header = bmpFile->fileHeader;
    printf("File Header: \n");
    printf("\tSignature %d (0x%x)\n", header.bfType, header.bfType);
    printf("\tFileSize %d (0x%x)\n", header.bfFileSize, header.bfFileSize);
    printf("\tReserved_1 %d (0x%x)\n", header.bfReserved1, header.bfReserved1);
    printf("\tDataOffset %d (0x%x)\n", header.bfOffBits, header.bfOffBits);

#ifdef BIT_MAP_INFO_HEADER_PRINT_INF
    BitMapInfoHeader info = bmpFile->infoHeader;
    printf("Info Header: \n");
    printf("\tSize %d (0x%x)\n", info.biSize, info.biSize);
    printf("\tWidth %u (0x%x)\n", info.biWidth, info.biWidth);
    printf("\tHeight %u (0x%x)\n", info.biHeight, info.biHeight);
    printf("\tPlanes %d (0x%x)\n", info.biPlanes, info.biPlanes);
    printf("\tBits Per Pixel %d (0x%x)\n", info.biBitCount, info.biBitCount);
    printf("\tCompression %d (0x%x)\n", info.biCompression, info.biCompression);
    printf("\tImageSize %d (0x%x)\n", info.biSizeImage, info.biSizeImage);
    printf("\tXpixelsPerM %u (0x%x)\n", info.biXPelsPerMeter, info.biXPelsPerMeter);
    printf("\tYpixelsPerM %u (0x%x)\n", info.biYPelsPerMeter, info.biYPelsPerMeter);
    printf("\tColors Used %u (0x%x)\n", info.biClrUsed, info.biClrUsed);
    printf("\tImportant Colors %d (0x%x)\n", info.biClrImportant, info.biClrImportant);
#endif

#ifdef BIT_MAP_PIXEL_PRINT_INF
    for(long i = 0; i < bmpFile->infoHeader.biWidth; i++) {
        printf("Pixel %ld: r=%d g=%d b=%d \n", i,
               bmpFile->rgbQuad[i].rgbRed,
               bmpFile->rgbQuad[i].rgbGreen,
               bmpFile->rgbQuad[i].rgbBlue
           );
    }
#endif

}


BMP_File* rotateRandomAngel(BMP_File *bmpFile, int angel) {
    int width = bmpFile->infoHeader.biWidth ;
    int height = bmpFile->infoHeader.biHeight;
    double r = sqrt(width/2 * width/2 + height/2 * height/2);
    double b = atan2(height, width);
    double angel1 = ((double) -angel) / 180 * M_PI;

    BMP_File *new_bmp = copyEmptyBMP(bmpFile);

    new_bmp->infoHeader.biWidth = height;
    new_bmp->infoHeader.biHeight = width;

    for(int y = 0-width/2; y < new_bmp->infoHeader.biHeight-width/2 ; y++) {
        for(int x = 0-height/2; x < new_bmp->infoHeader.biWidth-height/2; x++) {
            int i = (int) (y*cos(angel1) - x*sin(angel1) + r*cos(b));
            int j = (int) (y*sin(angel1) + x*cos(angel1) + r*sin(b));
            if (i <= height && i >= 0 && j <= height && j >= 0 &&
              x+height/2<=height && y+width/2<=width){
              RGBQuad *newPix = getPixel(new_bmp, x+height/2, y+width/2);
              RGBQuad *oldPix = getPixel(bmpFile, j, i);
              memcpy(newPix, oldPix, sizeof(RGBQuad));
            }
        }
    }
    return new_bmp;
}


BMP_File* rotate90Clockwise(BMP_File *bmpFile) {
    int width = bmpFile->infoHeader.biWidth;
    int height = bmpFile->infoHeader.biHeight;

    BMP_File *new_bmp = copyEmptyBMP(bmpFile);

    new_bmp->infoHeader.biWidth = height;
    new_bmp->infoHeader.biHeight = width;

    for(int y = new_bmp->infoHeader.biHeight; y >= 0 ; y--) {
        for(int x = 0; x < new_bmp->infoHeader.biWidth; x++) {
            RGBQuad *newPix = getPixel(new_bmp, x, y);
            RGBQuad *oldPix = getPixel(bmpFile, width - y - 1, x);
            memcpy(newPix, oldPix, sizeof(RGBQuad));
        }
    }
    return new_bmp;
}

BMP_File* rotate180(BMP_File *bmpFile) {
    int width = bmpFile->infoHeader.biWidth;
    int height = bmpFile->infoHeader.biHeight;

    BMP_File *new_bmp = copyEmptyBMP(bmpFile);

    new_bmp->infoHeader.biWidth = width;
    new_bmp->infoHeader.biHeight = height;

    for(int y = new_bmp->infoHeader.biHeight; y >= 0 ; y--) {
        for(int x = 0; x < new_bmp->infoHeader.biWidth; x++) {
            RGBQuad *newPix = getPixel(new_bmp, x, y);
            RGBQuad *oldPix = getPixel(bmpFile, width - x - 1, height - y - 1);
            memcpy(newPix, oldPix, sizeof(RGBQuad));
        }
    }
    return new_bmp;
}

BMP_File* rotate90CounterClockwise(BMP_File *bmpFile) {
    int width = bmpFile->infoHeader.biWidth;
    int height = bmpFile->infoHeader.biHeight;

    BMP_File *new_bmp = copyEmptyBMP(bmpFile);

    new_bmp->infoHeader.biWidth = height;
    new_bmp->infoHeader.biHeight = width;

    for(int y = new_bmp->infoHeader.biHeight-1; y >= 0 ; y--) {
        for(int x = 0; x < new_bmp->infoHeader.biWidth; x++) {
            RGBQuad *newPix = getPixel(new_bmp, x, y);
            RGBQuad *oldPix = getPixel(bmpFile, y, height - x - 1);
            memcpy(newPix, oldPix, sizeof(RGBQuad));
        }
    }
    return new_bmp;
}

RGBQuad* getPixel(BMP_File *bmp, int x, int y) {
    size_t index = bmp->infoHeader.biWidth * y + x;
    return &(bmp->rgbQuad[index]);
}

BMP_File* copyEmptyBMP(BMP_File *bmpFile) {
    BMP_File *newBMP = malloc(1 * sizeof(BMP_File));
    newBMP->fileHeader = bmpFile->fileHeader;
    newBMP->infoHeader = bmpFile->infoHeader;
    RGBQuad *pixels = malloc(newBMP->infoHeader.biHeight * newBMP->infoHeader.biWidth * sizeof(RGBQuad));
    newBMP->rgbQuad = pixels;
    return newBMP;
}

BMP_File* rotate(BMP_File *bmpFile, int angelOfDegrees) {
    if(angelOfDegrees == 0) {
        return bmpFile;
    }else if(angelOfDegrees < 0) {
        angelOfDegrees = -((-angelOfDegrees) % 360);
    }else {
        angelOfDegrees = angelOfDegrees % 360;
    }

    if(angelOfDegrees == 90 || angelOfDegrees == -270) {
        return rotate90Clockwise(bmpFile);
    }else if(angelOfDegrees == 180 || angelOfDegrees == -180) {
        return rotate180(bmpFile);
    }else if (angelOfDegrees == 270 || angelOfDegrees == -90) {
        return rotate90CounterClockwise(bmpFile);
    }else {
        return rotateRandomAngel(bmpFile, angelOfDegrees);
        /*printf("ERROR: Angel degrees must be equals +/- 90 or +/- 180 or +/- 270");
        return NULL;*/
    }
}
