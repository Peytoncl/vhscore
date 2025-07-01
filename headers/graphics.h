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

#define NUM_TEXTURES 16
extern GLuint textures[NUM_TEXTURES];

#endif