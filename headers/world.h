#ifndef WORLDH

#define WORLDH

#include "lighting.h"

typedef enum
{
    BRICK
} WALL_TYPES;

#define MAP_LENGTH 8
#define MAX_LIGHTS 64

#define FLOOR_Z 0
#define CEILING_Z 1

extern int map[MAP_LENGTH][MAP_LENGTH];
extern int floorMap[MAP_LENGTH][MAP_LENGTH];
extern int ceilingMap[MAP_LENGTH][MAP_LENGTH];
extern Light lights[MAX_LIGHTS];
extern int lightCount;

#endif