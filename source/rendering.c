#include <math.h>

#include "../headers/rendering.h"
#include "../headers/GL/glut.h"
#include "../headers/graphics.h"
#include "../headers/game.h"
#include "../headers/world.h"

extern Player player;

void DrawWalls()
{
    glBegin(GL_LINES);

    double dirX = cos(player.angle.x);
    double dirY = sin(player.angle.x);

    double planeX = -sin(player.angle.x) * player.FOV;
    double planeY = cos(player.angle.x) * player.FOV;

    for (int x = 0; x < windowW; x++) 
    {
        double cameraX = 2 * x / (double)windowW - 1;

        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)player.position.x;
        int mapY = (int)player.position.y;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = FALSE;
        int side;

        if (rayDirX < 0) 
        {
            stepX = -1;
            sideDistX = (player.position.x - mapX) * deltaDistX;
        } 
        else 
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player.position.x) * deltaDistX;
        }
        if (rayDirY < 0) 
        {
            stepY = -1;
            sideDistY = (player.position.y - mapY) * deltaDistY;
        } 
        else 
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player.position.y) * deltaDistY;
        }

        while (!hit) //DDA
        {
            if (sideDistX < sideDistY) 
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } 
            else 
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (map[mapX][mapY] > 0) hit = TRUE;
        }
        
        if (side == 0) perpWallDist = (mapX - player.position.x + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - player.position.y + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(windowH / perpWallDist);

        int drawStart = -lineHeight / 2 + windowH / 2;
        int drawEnd = lineHeight / 2 + windowH / 2;

        if (drawStart < 0) drawStart = 0;
        if (drawEnd >= windowH) drawEnd = windowH - 1;

        glVertex2i(x, drawStart);
        glVertex2i(x, drawEnd);
    }

    glEnd();
}