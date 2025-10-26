#ifndef WORLDH

#define WORLDH

typedef enum
{
    BRICK
} WALL_TYPES;

#define MAP_LENGTH 8

int map[MAP_LENGTH][MAP_LENGTH] = //Y, X
{

    {0,0,0,0,0,0,0,0},
    {0,-1,-1,-1,-1,-1,-1,0},
    {0,-1,-1,-1,-1,-1,-1,0},
    {0,-1,-1,-1,-1,-1,-1,0},
    {0,-1,-1,-1,-1,-1,-1,0},
    {0,-1,-1,-1,-1,-1,-1,1},
    {0,-1,-1,-1,-1,-1,1,1},
    {0,0,0,0,0,0,1,1}

};

#endif