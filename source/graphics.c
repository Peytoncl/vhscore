#include "../headers/graphics.h"

Image* LoadedImages;

void InitializeImages()
{
    LoadedImages = malloc(sizeof(Image) * MAX_IMAGES);
}

Image OpenImage(const char* location, int index)
{
    Image image;

    unsigned char ihdr_chunk[24];

    image.file = fopen(location, "rb");

    if (!image.file) { printf("Error reading image\n"); return; }

    fseek(image.file, 8, SEEK_SET);

    fread(ihdr_chunk, 1, 21, image.file);

    image.width = (ihdr_chunk[8] << 24) | (ihdr_chunk[9] << 16) | (ihdr_chunk[10] << 8) | ihdr_chunk[11];
    image.height = (ihdr_chunk[12] << 24) | (ihdr_chunk[13] << 16) | (ihdr_chunk[14] << 8) | ihdr_chunk[15];

    image.pixels = malloc(sizeof(uint8_t*) * image.height);
    for (int y = 0; y < image.height; y++) image.pixels[y] = malloc(sizeof(uint8_t) * image.width);

    

    LoadedImages[index] = image;

    return image;
}