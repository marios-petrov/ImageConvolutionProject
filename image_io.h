#ifndef IMAGECONVOLUTIONPROJECT_IMAGE_IO_H
#define IMAGECONVOLUTIONPROJECT_IMAGE_IO_H

#include <stdint.h>

/**
 * Pixel structure that holds individual color components.
 * Each component (red, green, blue) is 8 bits, allowing for 256 different intensities.
 */
typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Pixel;

/**
 * Image structure that holds the image dimensions and pixel data.
 * Width and height represent the size of the image in pixels.
 * Pixels is a pointer to the array of pixel data.
 */
typedef struct {
    int width;
    int height;
    Pixel* pixels;
} Image;

/**
 * Reads a bitmap image from the specified file path.
 * @param file_path The path to the bitmap file.
 * @return A pointer to the read image. NULL if there was an error.
 */
Image* read_bmp(const char* file_path);

/**
 * Writes an image as a bitmap to the specified file path.
 * @param file_path The path to the file where the image will be written.
 * @param image The image to be written.
 */
void write_bmp(const char* file_path, const Image* image);

/**
 * Frees the memory allocated for an image.
 * @param image The image to be deallocated.
 */
void free_image(Image* image);

#endif //IMAGECONVOLUTIONPROJECT_IMAGE_IO_H
