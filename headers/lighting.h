#ifndef LIGHTING_H

#define LIGHTING_H

#include "types.h"

typedef struct 
{
    DPOINT3 position; // 3d value
    double intensity;
    double radius;
    Color color;
} Light;

#endif