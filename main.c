/**
 * Author: Marios Petrov
 * Version 1.5
 */

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "image_io.h"
#include "kernels.h"

int main() 
{
    // Define the directories and file extension for input images
    const char* input_dir = "ImageConvolutionProject\\Input";
    const char* output_dir = "ImageConvolutionProject\\Output";
    const char* input_extension = ".bmp";
    size_t input_extension_len = strlen(input_extension);

    // Open the input directory
    DIR* dir = opendir(input_dir);
    if (!dir)
    {
        // Print error if the directory cannot be opened
        perror("Error opening input directory");
        return 1;
    }

    struct dirent* entry;
    // Iterate over each entry in the directory
    while ((entry = readdir(dir)) != NULL)
    {
        size_t name_len = strlen(entry->d_name);
        // Check if the file has the correct extension
        if (name_len > input_extension_len &&
            strcmp(entry->d_name + name_len - input_extension_len, input_extension) == 0)
        {

            // Create the full path for the input image
            char input_path[FILENAME_MAX];
            snprintf(input_path, FILENAME_MAX, "%s/%s", input_dir, entry->d_name);

            // Read the input image
            Image* input_image = read_bmp(input_path);
            if (!input_image)
            {
                fprintf(stderr, "Error reading image: %s\n", input_path); // Print error if the image cannot be read
                continue;
            }

            // Apply the Gaussian blur and Sobel kernels to the image
            Image* gaussian_output = apply_kernel(input_image, KERNEL_GAUSSIAN_BLUR);
            Image* sobel_output = apply_kernel(input_image, KERNEL_SOBEL);

            // Create the full paths for the output images
            char output_gaussian_path[FILENAME_MAX];
            snprintf(output_gaussian_path, FILENAME_MAX, "%s/gaussian_%s", output_dir, entry->d_name);
            char output_sobel_path[FILENAME_MAX];
            snprintf(output_sobel_path, FILENAME_MAX, "%s/sobel_%s", output_dir, entry->d_name);

            // Write the output images
            write_bmp(output_gaussian_path, gaussian_output);
            write_bmp(output_sobel_path, sobel_output);

            // Free the memory allocated for the images
            free_image(input_image);
            free_image(gaussian_output);
            free_image(sobel_output);

            // Print a message indicating that the image has been processed
            printf("Processed: %s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(dir);
    return 0;
}






