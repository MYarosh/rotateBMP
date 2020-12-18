#include "bmp_io.h"
#include <stdlib.h>
#include <stdio.h>

BMP_File *readBMP(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("File %s is not opened", filename);
        return NULL;
    }

    BitMapFileHeader fileHeader = {};
    fread(&fileHeader, sizeof(BitMapFileHeader), 1, fp);

    if (fileHeader.bfType != 0x4d42 && fileHeader.bfType != 0x4349 && fileHeader.bfType != 0x5450) {
        printf("File %s is not BMP format", filename);
        fclose(fp);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, sizeof(BitMapFileHeader), SEEK_SET);

    BitMapInfoHeader infoHeader = {};
    fread(&infoHeader, sizeof(BitMapInfoHeader), 1, fp);

    if(fileHeader.bfFileSize != filesize) {
        printf("BMP file has invalid filesize field");
        return NULL;
    }

    if(infoHeader.biSize != 40 && infoHeader.biSize != 108 && infoHeader.biSize != 124) {
        printf("BMP file has unknown size info header");
        fclose(fp);
        return NULL;
    }

    if(infoHeader.biWidth < 1 || infoHeader.biWidth > 10000 ||
       infoHeader.biHeight < 1 || infoHeader.biHeight > 10000) {
        printf("BMP file has not supported width or height ( > 10000 or < 1)");
        fclose(fp);
        return NULL;
    }

    if (fileHeader.bfReserved1 != 0 || infoHeader.biPlanes != 1 ||
        fileHeader.bfOffBits != 14 + infoHeader.biSize) {
        printf("BMP file contains some errors in structure");
        fclose(fp);
        return NULL;
    }

    if (infoHeader.biBitCount != 24 || infoHeader.biCompression != 0) {
        printf("BMP file is only full colored (24 bits) and not compressed");
        fclose(fp);
        return NULL;
    }


    fseek(fp, fileHeader.bfOffBits, SEEK_SET);
    RGBQuad *pixels = malloc(infoHeader.biHeight * infoHeader.biWidth * sizeof(RGBQuad));
    if (pixels == NULL) {
        printf("Cannot create array of pixel");
        fclose(fp);
        exit(1);
    }

    int kr = (infoHeader.biWidth * 3) % 4;
    if (kr != 0) { kr = 4 - kr; }

    for (size_t i = 0; i < infoHeader.biHeight; i++) {
        for (size_t j = 0; j < infoHeader.biWidth; j++) {
            size_t index = i * infoHeader.biWidth + j;
            fread(&(pixels[index]), sizeof(RGBQuad), 1, fp);
        }
        for (int k = 0; k < kr; k++) { getc(fp); }
    }
    fclose(fp);

    BMP_File *bmpFile = malloc(1 * sizeof(BMP_File));

    bmpFile->fileHeader = fileHeader;
    bmpFile->infoHeader = infoHeader;
    bmpFile->rgbQuad = pixels;

    return bmpFile;
}

void writeBMP(BMP_File *bmp, char *newFilename) {
    FILE *fw = fopen(newFilename, "w+");
    if (fw == NULL) {
        printf("File %s is not opened", newFilename);
        exit(1);
    }

    BitMapFileHeader fileHeader = bmp->fileHeader;
    fwrite(&fileHeader, sizeof(BitMapFileHeader), 1, fw);

    BitMapInfoHeader infoHeader = bmp->infoHeader;
    fwrite(&infoHeader, sizeof(BitMapInfoHeader), 1, fw);

    fseek(fw, fileHeader.bfOffBits, SEEK_SET);

    int kr = (infoHeader.biWidth * 3) % 4;
    if (kr != 0) { kr = 4 - kr; }

    RGBQuad *pixels = bmp->rgbQuad;
    for (size_t i = 0; i < infoHeader.biHeight; i++) {
        for (size_t j = 0; j < infoHeader.biWidth; j++) {
            size_t index = i * infoHeader.biWidth + j;
            fwrite(&(pixels[index]), sizeof(RGBQuad), 1, fw);
        }
        for (int k = 0; k < kr; k++) { putc(0, fw); }
    }

    fclose(fw);
}