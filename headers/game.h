#ifndef GAMEH

#define GAMEH

#include <windows.h>

// Game Variables

typedef struct
{
    POINT position;
    POINT angle;
    double FOV;
} Player;

extern Player player;

// Core Engine things

#define KEY_COUNT 256

extern int keys[KEY_COUNT];

void ReDisplay();
void Update();
void Start();

#endif