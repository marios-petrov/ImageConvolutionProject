# Image Convolution Project

This project is a simple image processing pipeline that reads BMP images, applies different kernels for image processing, and then writes the output images. Currently, the project supports applying Gaussian blur and Sobel edge detection kernels to images.

## Getting Started

To build and run the project, you need a C compiler like gcc or clang. You can build the project by running `gcc main.c image_io.c kernels.c -o image_convolution`.

To run the program, use `./image_convolution`.

## File Structure

- **image_io.h**: This header file defines the Pixel and Image structures, as well as the functions for reading and writing BMP images and freeing up memory used by images.

- **kernels.h**: This header file defines the functions related to applying different types of kernels to images.

- **image_io.c**: This file contains the implementation of the functions declared in `image_io.h`. It includes functions to read and write BMP files and to free up memory used by images.

- **kernels.c**: This file contains the implementation of the functions declared in `kernels.h`. It includes the implementation for applying the Gaussian blur and Sobel kernels to an image.

- **main.c**: This is the entry point of the program. It opens the specified input directory, reads each BMP file in the directory, applies the Gaussian blur and Sobel kernels to each image, and then writes the output images to the output directory.

## Code Explanation

- **Pixel**: This represents a pixel in an image. Each pixel is made up of red, green, and blue components.

- **Image**: This represents an image. It contains the width and height of the image, as well as an array of pixels that make up the image.

- **read_bmp**: This function reads a BMP image from the specified file path and returns an `Image` struct containing the image data.

- **write_bmp**: This function writes the given image data to a BMP file at the specified file path.

- **free_image**: This function frees up the memory used by an `Image` struct.

- **KernelType**: This defines the different types of kernels that can be applied to an image.

- **apply_kernel**: This function applies the specified kernel to the input image and returns a new image. The kernels currently supported are Gaussian blur and Sobel edge detection.
