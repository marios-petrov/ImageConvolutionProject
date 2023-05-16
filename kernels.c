/**
 * Author: Marios Petrov
 * Version 1.5
 */

#include "kernels.h"
#include <stdlib.h>
#include <math.h>

// Define the Gaussian kernel for blurring
static const float gaussian_kernel[3][3] =
        {
        {1.0/16, 1.0/8, 1.0/16},
        {1.0/8, 1.0/4, 1.0/8},
        {1.0/16, 1.0/8, 1.0/16},
        };

// Define the Sobel kernel for x-axis edge detection
static const int sobel_x_kernel[3][3] =
        {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1},
        };

// Define the Sobel kernel for y-axis edge detection
static const int sobel_y_kernel[3][3] =
        {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1},
        };

// Function to apply a kernel at a specific pixel in the image
static Pixel apply_kernel_at_pixel(const Image* input, int x, int y, KernelType kernel_type)
{
    // Initialize sum variables for each color channel
    int sum_r = 0, sum_g = 0, sum_b = 0;
    int sum_rx = 0, sum_gx = 0, sum_bx = 0;
    int sum_ry = 0, sum_gy = 0, sum_by = 0;
    const int kernel_offset = 1;

    // Iterate over the kernel's area on the image
    for (int ky = -kernel_offset; ky <= kernel_offset; ky++)
    {
        for (int kx = -kernel_offset; kx <= kernel_offset; kx++)
        {
            int img_x = x + kx;
            int img_y = y + ky;

            // Check if the current kernel's position is within the image's dimensions
            if (img_x >= 0 && img_x < input->width && img_y >= 0 && img_y < input->height)
            {
                Pixel pixel = input->pixels[img_y * input->width + img_x];

                // Apply the Gaussian blur kernel
                if (kernel_type == KERNEL_GAUSSIAN_BLUR)
                {
                    float kernel_val = gaussian_kernel[ky + kernel_offset][kx + kernel_offset];
                    sum_r += pixel.red * kernel_val;
                    sum_g += pixel.green * kernel_val;
                    sum_b += pixel.blue * kernel_val;
                }
                // Apply the Sobel edge detection kernel
                else if (kernel_type == KERNEL_SOBEL)
                {
                    int kernel_x_val = sobel_x_kernel[ky + kernel_offset][kx + kernel_offset];
                    int kernel_y_val = sobel_y_kernel[ky + kernel_offset][kx + kernel_offset];
                    sum_rx += pixel.red * kernel_x_val;
                    sum_gx += pixel.green * kernel_x_val;
                    sum_bx += pixel.blue * kernel_x_val;
                    sum_ry += pixel.red * kernel_y_val;
                    sum_gy += pixel.green * kernel_y_val;
                    sum_by += pixel.blue * kernel_y_val;
                }
            }
        }
    }

    Pixel result;

    // Set the result pixel's color channels based on the kernel type
    if (kernel_type == KERNEL_GAUSSIAN_BLUR)
    {
        result.red = sum_r;
        result.green = sum_g;
        result.blue = sum_b;
    }
    // For Sobel kernel, calculate the magnitude of the gradient
    else if (kernel_type == KERNEL_SOBEL)
    {
        result.red = sqrt(sum_rx * sum_rx + sum_ry * sum_ry);
        result.green = sqrt(sum_gx * sum_gx + sum_gy * sum_gy);
        result.blue = sqrt(sum_bx * sum_bx + sum_by * sum_by);
    }
    // Return resulting pixel
    return result;
}
// Function to apply a kernel to an entire image
Image* apply_kernel(const Image* input, KernelType kernel_type)
{
    Image* output = (Image*)malloc(sizeof(Image));
    output->width = input->width;
    output->height = input->height;
    output->pixels = (Pixel*)malloc(input->width * input->height * sizeof(Pixel));

    // Iterate over every pixel of the input image
    for (int y = 0; y < input->height; y++)
    {
        for (int x = 0; x < input->width; x++)
        {
            Pixel pixel = apply_kernel_at_pixel(input, x, y, kernel_type);
            output->pixels[y * input->width + x] = pixel;
        }
    }

    return output;
}

