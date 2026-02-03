#ifndef TYPESH

#define TYPESH

typedef struct 
{
    double x, y;
} DPOINT;

typedef struct 
{
    double x, y, z;
} DPOINT3;

typedef struct
{
    int r;
    int g;
    int b;
} Color;

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832
#define M_PI_2 (M_PI / 2)
#endif

#endif