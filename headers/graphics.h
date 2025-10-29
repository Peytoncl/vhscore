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

#define SPRITES_AMOUNT 10 // amount of sprites available in one row of the spritesheet
#define SPRITESHEET_SIZE 2560 // square size of spritesheet (must be a multiple of 256)
#define SPRITE_SIZE 256
 
extern GLuint spritesheet;

void LoadSpritesheet();

#endif