#ifndef GRAPHICSH

#define GRAPHICSH

#define TARGET_FPS 144
#define FRAME_DURATION (1000 / TARGET_FPS)  // in milliseconds

#define MAX_IMAGES 64

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern int windowW;
extern int windowH;

extern int windowHW;
extern int windowHH;

typedef struct
{
    int width, height;
    uint8_t** pixels;
    FILE* file;
} Image;

extern Image* LoadedImages;

void InitializeImages();
Image OpenImage(const char* location, int index);

#endif