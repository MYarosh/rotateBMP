#ifndef LLP_LAB_6__BMP_STRUCT_H
#define LLP_LAB_6__BMP_STRUCT_H

#include <stdint.h>

typedef struct __attribute__((packed)){
    uint16_t bfType;
    uint32_t bfFileSize;
    uint32_t bfReserved1;
    uint32_t bfOffBits;
} BitMapFileHeader;

typedef struct __attribute__((packed)){
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BitMapInfoHeader;

typedef struct __attribute__((packed)){
    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;
} RGBQuad;

typedef struct {
    BitMapFileHeader fileHeader;
    BitMapInfoHeader infoHeader;
    RGBQuad* rgbQuad;
} BMP_File;

#endif
