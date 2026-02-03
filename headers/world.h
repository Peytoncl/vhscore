#ifndef WORLDH

#define WORLDH

typedef enum
{
    BRICK
} WALL_TYPES;

#define MAP_LENGTH 8

extern int map[MAP_LENGTH][MAP_LENGTH];
extern int floorMap[MAP_LENGTH][MAP_LENGTH];
extern int ceilingMap[MAP_LENGTH][MAP_LENGTH];

#endif