#include "../headers/GL/glut.h"
#include "../headers/game.h"
#include "../headers/graphics.h"

extern int keys[256];

void ReDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



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