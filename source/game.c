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

    glColor3f(0, 0, 170);

    DrawWalls();

    glutSwapBuffers();
}

void Update(double deltaTime)
{
    if (keys['a']) player.angle.x -= player.sensitivity * deltaTime;
    if (keys['d']) player.angle.x += player.sensitivity * deltaTime;

    //if (player.angle.x > 360) player.angle.x -= 360;
    //if (player.angle.x < 0) player.angle.x += 360;

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

void Start()
{
    glClearColor(0, 0, 0, 0);

    player.position = (DPOINT){5, 5};
    player.angle = (DPOINT){0, 0};

    player.FOV = 1;
    player.sensitivity = 6;
    player.speed = 2;

    gluOrtho2D(0, windowW, windowH, 0);
}