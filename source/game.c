#include <stdio.h>
#include <math.h>

#include "../headers/GL/glut.h"
#include "../headers/game.h"
#include "../headers/graphics.h"
#include "../headers/rendering.h"
#include "../headers/world.h"

Player player;

extern int keys[256];

extern int map[MAP_LENGTH][MAP_LENGTH];

void ReDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1, 1, 1);

    DrawWalls();

    glutSwapBuffers();
}

void Update(double deltaTime)
{
    //classic axis-separated movement + collision resolution algorithm

    DPOINT currentPosition = player.position;

    double dx = 0;
    double dy = 0;

    if (keys['d']) 
    {
        dx += cos(player.angle.x + M_PI_2) * player.speed * deltaTime;
        dy += sin(player.angle.x + M_PI_2) * player.speed * deltaTime;
    }

    if (keys['a']) 
    {
        dx += cos(player.angle.x - M_PI_2) * player.speed * deltaTime;
        dy += sin(player.angle.x - M_PI_2) * player.speed * deltaTime;
    }

    if (keys['w']) 
    {
        dx += cos(player.angle.x) * player.speed * deltaTime;
        dy += sin(player.angle.x) * player.speed * deltaTime;
    }

    if (keys['s']) 
    {
        dx -= cos(player.angle.x) * player.speed * deltaTime;
        dy -= sin(player.angle.x) * player.speed * deltaTime;
    }

    DPOINT testPosition = {currentPosition.x + dx, currentPosition.y};
    if (map[(int)testPosition.y][(int)testPosition.x] < 0) currentPosition.x += dx;

    testPosition = (DPOINT){currentPosition.x, currentPosition.y + dy};
    if (map[(int)testPosition.y][(int)testPosition.x] < 0) currentPosition.y += dy;

    player.position = currentPosition;

}

void MouseMovement(int x, int y)
{
    int dx = mouse.x - windowHW;

    if (dx != 0) player.angle.x += dx * player.sensitivity; 
}

void Start()
{
    glClearColor(0, 0, 0, 0);

    mouse.locked = TRUE;

    player.position = (DPOINT){5, 5};
    player.angle = (DPOINT){0, 0};

    player.FOV = 1;
    player.sensitivity = 0.01;
    player.speed = 4;

    gluOrtho2D(0, windowW, windowH, 0);
}