#include <stdio.h>
#include <math.h>

#include "../headers/GL/glut.h"
#include "../headers/game.h"
#include "../headers/graphics.h"
#include "../headers/rendering.h"

Player player;

extern int keys[256];

void ReDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1, 1, 1);

    DrawWalls();

    glutSwapBuffers();
}

void Update(double deltaTime)
{
    if (keys['d']) 
    {
        player.position.x += cos(player.angle.x + M_PI_2) * player.speed * deltaTime;
        player.position.y += sin(player.angle.x + M_PI_2) * player.speed * deltaTime;
    }

    if (keys['a']) 
    {
        player.position.x += cos(player.angle.x - M_PI_2) * player.speed * deltaTime;
        player.position.y += sin(player.angle.x - M_PI_2) * player.speed * deltaTime;
    }

    if (keys['w']) 
    {
        player.position.x += cos(player.angle.x) * player.speed * deltaTime;
        player.position.y += sin(player.angle.x) * player.speed * deltaTime;
    }

    if (keys['s']) 
    {
        player.position.x -= cos(player.angle.x) * player.speed * deltaTime;
        player.position.y -= sin(player.angle.x) * player.speed * deltaTime;
    }
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