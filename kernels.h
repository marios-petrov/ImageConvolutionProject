#ifndef IMAGECONVOLUTIONPROJECT_KERNELS_H
#define IMAGECONVOLUTIONPROJECT_KERNELS_H

#include "image_io.h"

/**
 * Enum to represent different types of kernels that can be applied to an image.
 * KERNEL_GAUSSIAN_BLUR: Applies Gaussian blur to the image.
 * KERNEL_SOBEL: Applies Sobel edge detection to the image.
 */
typedef enum {
    KERNEL_GAUSSIAN_BLUR,
    KERNEL_SOBEL,
} KernelType;

/**
 * Applies the specified kernel to the input image.
 * @param input The input image to be processed.
 * @param kernel_type The type of kernel to apply.
 * @return A new image with the kernel applied.
 */
Image* apply_kernel(const Image* input, KernelType kernel_type);

#endif //IMAGECONVOLUTIONPROJECT_KERNELS_H
