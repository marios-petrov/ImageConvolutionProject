#include "image_io.h"
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPHeader;

typedef struct {
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
#pragma pack(pop)

Image* read_bmp(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    BMPHeader header;
    fread(&header, sizeof(BMPHeader), 1, file);

    if (header.type != 0x4D42) {
        fclose(file);
        fprintf(stderr, "Error: Not a valid BMP file\n");
        return NULL;
    }

    BMPInfoHeader info;
    fread(&info, sizeof(BMPInfoHeader), 1, file);

    if (info.bits != 24 || info.compression != 0) {
        fclose(file);
        fprintf(stderr, "Error: Unsupported BMP format\n");
        return NULL;
    }

    Image* image = (Image*)malloc(sizeof(Image));
    image->width = info.width;
    image->height = info.height;
    image->pixels = (Pixel*)malloc(info.width * info.height * sizeof(Pixel));

    int padding = (4 - (info.width * 3) % 4) % 4;

    fseek(file, header.offset, SEEK_SET);
    for (int y = 0; y < info.height; y++) {
        for (int x = 0; x < info.width; x++) {
            fread(&image->pixels[y * info.width + x], sizeof(Pixel), 1, file);
        }
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
    return image;
}

void write_bmp(const char* file_path, const Image* image) {
    FILE *file = fopen(file_path, "wb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    BMPHeader header = {0x4D42, 0, 0, 0, 54};
    BMPInfoHeader info = {40, image->width, image->height, 1, 24, 0, 0, 0, 0, 0, 0};

    int padding = (4 - (info.width * 3) % 4) % 4;
    int row_size = (info.width * 3) + padding;
    int image_size = row_size * info.height;

    header.size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + image_size;
    info.imagesize = image_size;

    fwrite(&header, sizeof(BMPHeader), 1, file);
    fwrite(&info, sizeof(BMPInfoHeader), 1, file);

    for (int y = 0; y < info.height; y++) {
        for (int x = 0; x < info.width; x++) {
            fwrite(&image->pixels[y * info.width + x], sizeof(Pixel), 1, file);
            for (int p = 0; p < padding; p++) {
                fputc(0, file);
            }
        }
    }

    fclose(file);
}

void free_image(Image *image) {
        if (image) {
            if (image->pixels) {
                free(image->pixels);
            }
            free(image);
        }
    }




