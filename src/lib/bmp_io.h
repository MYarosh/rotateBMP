//
// Created by lanolin on 31.10.2020.
//

#ifndef LLP_LAB_6__BMP_IO_H
#define LLP_LAB_6__BMP_IO_H

#include "bmp_struct.h"

/**
 *
 * @return BMP_File struct with all information about bmp file
 */
BMP_File* readBMP(char* filename);

/**
 *
 * @return write changes in new file on filename
 */
void writeBMP(BMP_File *bmp, char* newFilename) ;

#endif 
