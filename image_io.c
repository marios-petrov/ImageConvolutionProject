#include "image_io.h"
#include "stdio.h"
#include "stdlib.h"

// Ensure the structure packing in memory is done without padding
#pragma pack(push, 1)

// Structure for BMP Header
typedef struct
{
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPHeader;

// Structure for BMP Info Header
typedef struct
{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits;
    uint32_t compression;
    uint32_t imagesize;
    int32_t xresolution;
    int32_t yresolution;
    uint32_t ncolours;
    uint32_t importantcolours;
} BMPInfoHeader;

// End of packing
#pragma pack(pop)

// Function to read BMP files
Image* read_bmp(const char* file_path)
{
    // Open the file in read-binary mode
    FILE* file = fopen(file_path, "rb");
    if (!file)
    {
        // Print error if file cannot be opened
        perror("Error opening file");
        return NULL;
    }

    // Create an instance of the BMPHeader structure
    BMPHeader header;
    // Read the BMPHeader from the file
    fread(&header, sizeof(BMPHeader), 1, file);

    // Check if the file is a valid BMP file
    if (header.type != 0x4D42)
    {
        fclose(file);
        fprintf(stderr, "Error: Not a valid BMP file\n");
        return NULL;
    }

    // Create an instance of the BMPInfoHeader structure
    BMPInfoHeader info;
    // Read the BMPInfoHeader from the file
    fread(&info, sizeof(BMPInfoHeader), 1, file);

    // Check if the BMP file is in the supported format
    if (info.bits != 24 || info.compression != 0)
    {
        fclose(file); // Close the file
        fprintf(stderr, "Error: Unsupported BMP format\n");
        return NULL;
    }

    // Create a new Image and allocate memory for it
    Image* image = (Image*)malloc(sizeof(Image));
    image->width = info.width;
    image->height = info.height;
    image->pixels = (Pixel*)malloc(info.width * info.height * sizeof(Pixel));

    // Calculate the padding
    int padding = (4 - (info.width * 3) % 4) % 4;

    // Set the file position to the beginning of the pixel data
    fseek(file, header.offset, SEEK_SET);

    // Read the pixel data from the file
    for (int y = 0; y < info.height; y++)
    {
        for (int x = 0; x < info.width; x++)
        {
            fread(&image->pixels[y * info.width + x], sizeof(Pixel), 1, file);
        }
        // Skip over the padding
        fseek(file, padding, SEEK_CUR);
    }
    fclose(file);
    return image;
}

// Function to write BMP files
void write_bmp(const char* file_path, const Image* image)
{
    // Open the file in write-binary mode
    FILE *file = fopen(file_path, "wb");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    // Prepare the BMPHeader and BMPInfoHeader for the image
    BMPHeader header = {0x4D42, 0, 0, 0, 54};
    BMPInfoHeader info = {40, image->width, image->height, 1, 24, 0, 0, 0, 0, 0, 0};

    // Calculate the padding
    int padding = (4 - (info.width * 3) % 4) % 4;
    // Calculate the row size
    int row_size = (info.width * 3) + padding;
    // Calculate the image size
    int image_size = row_size * info.height;

    // Set the size of the header
    header.size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + image_size;
    // Set the size of the image
    info.imagesize = image_size;

    // Write the BMPHeader to the file
    fwrite(&header, sizeof(BMPHeader), 1, file);
    // Write the BMPInfoHeader to the file
    fwrite(&info, sizeof(BMPInfoHeader), 1, file);

    // Write the pixel data to the file
    for (int y = 0; y < info.height; y++)
    {
        for (int x = 0; x < info.width; x++)
        {
            fwrite(&image->pixels[y * info.width + x], sizeof(Pixel), 1, file);
            // Write the padding
            for (int p = 0; p < padding; p++)
            {
                fputc(0, file);
            }
        }
    }
    fclose(file);
}

// Function to free the memory allocated for the image
void free_image(Image *image)
{
    if (image)
    {
        if (image->pixels)
        {
            free(image->pixels); // Free the memory allocated for the pixels
        }
        free(image); // Free the memory allocated for the image
    }
}





