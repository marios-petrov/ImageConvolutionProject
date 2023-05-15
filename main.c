#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "image_io.h"
#include "kernels.h"

int main() {
    const char* input_dir = "ImageConvolutionProject\\Input";
    const char* output_dir = "ImageConvolutionProject\\Output";
    const char* input_extension = ".bmp";
    size_t input_extension_len = strlen(input_extension);

    DIR* dir = opendir(input_dir);
    if (!dir) {
        perror("Error opening input directory");
        return 1;

    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        size_t name_len = strlen(entry->d_name);
        if (name_len > input_extension_len &&
            strcmp(entry->d_name + name_len - input_extension_len, input_extension) == 0) {

            char input_path[FILENAME_MAX];
            snprintf(input_path, FILENAME_MAX, "%s/%s", input_dir, entry->d_name);

            Image* input_image = read_bmp(input_path);
            if (!input_image) {
                fprintf(stderr, "Error reading image: %s\n", input_path);
                continue;
            }

            Image* gaussian_output = apply_kernel(input_image, KERNEL_GAUSSIAN_BLUR);
            Image* sobel_output = apply_kernel(input_image, KERNEL_SOBEL);

            char output_gaussian_path[FILENAME_MAX];
            snprintf(output_gaussian_path, FILENAME_MAX, "%s/gaussian_%s", output_dir, entry->d_name);
            char output_sobel_path[FILENAME_MAX];
            snprintf(output_sobel_path, FILENAME_MAX, "%s/sobel_%s", output_dir, entry->d_name);

            write_bmp(output_gaussian_path, gaussian_output);
            write_bmp(output_sobel_path, sobel_output);

            free_image(input_image);
            free_image(gaussian_output);
            free_image(sobel_output);

            printf("Processed: %s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}





