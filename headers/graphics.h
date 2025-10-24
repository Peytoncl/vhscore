#ifndef GRAPHICSH

#define GRAPHICSH

#define TARGET_FPS 144
#define FRAME_DURATION (1000 / TARGET_FPS)  // in milliseconds

#include "GL/glut.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern int windowW;
extern int windowH;

extern int windowHW;
extern int windowHH;

#define MAX_TEXTURES 1024 // max amount of textures that can be loaded at once during runtime
#define TEXTURE_SIZE 256 // square size of all images, has to be equal to this.
extern GLuint textures[MAX_TEXTURES];

void LoadTexture(char* textureName, int index);

#endif