#include <stdio.h>
#include "stdbool.h"
#include <stdlib.h> 
#include <math.h>
#include "windows.h"

#include "../headers/GL/glut.h"
#include "../headers/game.h"
#include "../headers/graphics.h"

int keys[256];

int windowW = 1200;
int windowH = 800;

void keyDown(unsigned char key, int x, int y) 
{
  keys[key] = true; 
}

void keyUp(unsigned char key, int x, int y) 
{
  keys[key] = false; 
}

void windowResize(int width, int height)
{
  glutReshapeWindow(windowW, windowH);
}

int main(int argc, char** argv) 
{
  glutInit(&argc, argv);    

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);        
  glutInitWindowSize(windowW, windowH);        
    
  glutCreateWindow("VHS");  

  Start();

  for (int i = 0; i < KEY_COUNT; i++) 
  {
    keys[i] = false;
  }

  glutDisplayFunc(ReDisplay); 
  glutIdleFunc(Update);      

  glutKeyboardFunc(keyDown);  
  glutKeyboardUpFunc(keyUp);  

  glutReshapeFunc(windowResize);

  glutMainLoop();      

  return 0;   
}