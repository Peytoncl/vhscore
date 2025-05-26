#include "../headers/GL/glut.h"
#include "../headers/game.h"
#include "../headers/graphics.h"
#include "../headers/rendering.h"

Player player = {{5, 5}, {0, 0}, 60};

extern int keys[256];

void ReDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(255, 0, 0);

    DrawWalls();

    glutSwapBuffers();
}

void Update()
{
    glutPostRedisplay();
}

void Start()
{
    glClearColor(0, 0, 0, 0);

  

    gluOrtho2D(0, windowW, windowH, 0);
}