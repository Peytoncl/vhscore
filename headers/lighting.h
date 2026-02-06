#ifndef LIGHTING_H

#define LIGHTING_H

#include "types.h"

#define MIN_LIGHT 0.08
typedef struct 
{
    DPOINT3 position; // 3d value
    double intensity;
    double radius;
    //Color color;
} Light;

#endif