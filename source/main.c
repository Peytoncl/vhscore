#include <stdio.h>
#include "stdbool.h"
#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include <windows.h>

#include "../headers/GL/glut.h"
#include "../headers/game.h"
#include "../headers/graphics.h"

clock_t lastFrameTime = 0;

int keys[256];

int windowW = 1200;
int windowH = 800;

void KeyDown(unsigned char key, int x, int y) 
{
  keys[key] = true; 
}

void KeyUp(unsigned char key, int x, int y) 
{
  keys[key] = false; 
}

void FrameLimiter(int value) // cap update function to run at target fps
{
  clock_t now = clock();
  static clock_t previous = 0;

  if (previous == 0) previous = now; // init on first run

  double deltaTime = (double)(now - lastFrameTime) / CLOCKS_PER_SEC;
  lastFrameTime = now;

  Update(deltaTime); // run update and send delta time through

  glutPostRedisplay();

  glutTimerFunc(FRAME_DURATION, FrameLimiter, 0); 
}

void WindowResize(int width, int height)
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

  glutKeyboardFunc(KeyDown);  
  glutKeyboardUpFunc(KeyUp);  

  glutReshapeFunc(WindowResize);

  lastFrameTime = clock(); 
  glutTimerFunc(0, FrameLimiter, 0);

  glutMainLoop();      

  return 0;   
}