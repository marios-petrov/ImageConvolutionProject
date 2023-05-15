//
// Created by Marios on 5/3/2023.
//

#ifndef IMAGECONVOLUTIONPROJECT_IMAGE_IO_H
#define IMAGECONVOLUTIONPROJECT_IMAGE_IO_H

#include <stdint.h>

typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Pixel;

typedef struct {
    int width;
    int height;
    Pixel* pixels;
} Image;

Image* read_bmp(const char* file_path);
void write_bmp(const char* file_path, const Image* image);
void free_image(Image* image);

#endif //IMAGECONVOLUTIONPROJECT_IMAGE_IO_H
