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

typedef struct
{
    int x;
    int y;
    int state;
    int clicked;
    int locked;
} Mouse;

// Core Engine things

#define KEY_COUNT 256

extern Player player;
extern int keys[KEY_COUNT];
extern Mouse mouse;

void ReDisplay();
void Update(double deltaTime);
void Start();
void MouseMovement(int x, int y);

#endif