#ifndef GAMEH

#define GAMEH

#include <windows.h>
#include "types.h"

// Game Variables

typedef struct
{
    DPOINT position;
    DPOINT angle;
    double FOV;
    double sensitivity;
    double speed;
} Player;

extern Player player;

// Core Engine things

#define KEY_COUNT 256

extern int keys[KEY_COUNT];

void ReDisplay();
void Update(double deltaTime);
void Start();

#endif