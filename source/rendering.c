#include <math.h>

#include "../headers/rendering.h"
#include "../headers/GL/glut.h"
#include "../headers/graphics.h"
#include "../headers/game.h"
#include "../headers/world.h"
#include "../headers/lighting.h"
#include "../headers/math_ext.h"

extern Player player;

extern int map[MAP_LENGTH][MAP_LENGTH];
extern int floorMap[MAP_LENGTH][MAP_LENGTH];
extern int ceilingMap[MAP_LENGTH][MAP_LENGTH];

double Normalize(double value, double min, double max)
{
    return (value - min) / (max - min);
}

void DrawWalls()
{
    // raycasting //

    double dirX = cos(player.angle.x);
    double dirY = sin(player.angle.x);

    double planeX = -sin(player.angle.x) * player.FOV;
    double planeY = cos(player.angle.x) * player.FOV;

    double wallPerpDistances[windowW];
    int wallEnds[windowW];
    int sides[windowW];
    int mapXs[windowW];
    int mapYs[windowW];
    double rayDirXs[windowW];
    double rayDirYs[windowW];
    double wallXs[windowW];

    glEnable(GL_TEXTURE_2D); // enable texturing

    glBegin(GL_POINTS);

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

            if (map[mapY][mapX] >= 0) hit = TRUE;
        }

        int hitIndex = map[mapY][mapX];

        if (side == 0) perpWallDist = (mapX - player.position.x + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - player.position.y + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(windowH / perpWallDist);

        int drawStart = -lineHeight / 2 + windowH / 2;
        int drawEnd = lineHeight / 2 + windowH / 2;

        //if (drawStart < 0) drawStart = 0;
        //if (drawEnd >= windowH) drawEnd = windowH - 1;

        // drawing walls //

        double wallX;  // exact hit location on wall

        if (side == 0) wallX = player.position.y + perpWallDist * rayDirY;
        else wallX = player.position.x + perpWallDist * rayDirX;
        
        wallX -= floor(wallX);

        int spriteX = (int)(wallX * SPRITE_SIZE); 
        int spritesheetX = spriteX + (map[mapY][mapX] * SPRITE_SIZE);

        int row = hitIndex / SPRITES_AMOUNT;

        double spriteTop = 0 + (SPRITE_SIZE * row);
        double spriteBottom = SPRITE_SIZE + (SPRITE_SIZE * row);

        double texStep = (double)SPRITE_SIZE / (double)lineHeight;
        double texPos = 0.0;

        double hitX = player.position.x + rayDirX * perpWallDist;
        double hitY = player.position.y + rayDirY * perpWallDist;

        for (int y = drawStart; y < drawEnd; y++)
        {
            int texY = (int)(spriteTop + texPos);
            double v = (double)texY / (double)SPRITESHEET_SIZE;

            double t = (y - drawStart) / (drawEnd - drawStart);            
            double hitZ = dlerp(CEILING_Z, FLOOR_Z, t);

            double totalLight = 0.0;

            for (int i = 0; i < lightCount; i++)
            {
                Light L = lights[i];

                double dx = L.position.x - hitX;
                double dy = L.position.y - hitY;
                double dz = L.position.z - hitZ;

                double distSq = dx*dx + dy*dy + dz*dz;
                double dist = sqrt(distSq);

                if (dist > L.radius) continue;

                double attenuation = 1.0 / (1.0 + distSq);
                if (distSq < 0.001) distSq = 0.001;

                totalLight += attenuation * L.intensity;
            }

            glColor3f(totalLight, totalLight, totalLight);

            glTexCoord2f((double)spritesheetX / SPRITESHEET_SIZE, v);
            glVertex2i(x, y);

            texPos += texStep;
        }

        wallEnds[x] = drawEnd;
        wallPerpDistances[x] = perpWallDist;
        sides[x] = side;
        mapXs[x] = mapX;
        mapYs[x] = mapY;
        wallXs[x] = wallX;
        rayDirXs[x] = rayDirX;
        rayDirYs[x] = rayDirY;
        
    }

    glEnd();
    
    // drawing floor // 

    glBegin(GL_POINTS);

    for (int x = 0; x < windowW; x++)
    {
        double floorXWall;
        double floorYWall;

        if (sides[x] == 0 && rayDirXs[x] > 0) 
        {
            floorXWall = mapXs[x];
            floorYWall = mapYs[x] + wallXs[x];
        } 
        else if (sides[x] == 0 && rayDirXs[x] < 0) 
        {
            floorXWall = mapXs[x] + 1.0;
            floorYWall = mapYs[x] + wallXs[x];
        } 
        else if (sides[x] == 1 && rayDirYs[x] > 0) 
        {
            floorXWall = mapXs[x] + wallXs[x];
            floorYWall = mapYs[x];
        } 
        else 
        {
            floorXWall = mapXs[x] + wallXs[x];
            floorYWall = mapYs[x] + 1.0;
        }

        for (int y = wallEnds[x] + 1; y <= windowH; y++)
        {
            //double hitX = player.position.x + rayDirXs[x] * wallPerpDistances[x];
            //double hitY = player.position.y + rayDirYs[x] * wallPerpDistances[x];

            double currentDist = windowH / (2.0 * y - windowH);
            double weight = currentDist / wallPerpDistances[x];

            double currentFloorX = weight * floorXWall + (1.0 - weight) * player.position.x;
            double currentFloorY = weight * floorYWall + (1.0 - weight) * player.position.y;

            int cellX = (int)currentFloorX;
            int cellY = (int)currentFloorY;
            
            int floorIndex = floorMap[cellY][cellX];
            int ceilingIndex = ceilingMap[cellY][cellX];

            double fracX = currentFloorX - cellX;
            double fracY = currentFloorY - cellY;

            int texX = (int)(fracX * SPRITE_SIZE + 1);
            int texY = (int)(fracY * SPRITE_SIZE + 1);

            int floorRow = floorIndex / SPRITES_AMOUNT;
            int floorCol = floorIndex % SPRITES_AMOUNT;
            int ceilingRow = ceilingIndex / SPRITES_AMOUNT;
            int ceilingCol = ceilingIndex % SPRITES_AMOUNT;

            int floorSpritesheetX = floorCol * SPRITE_SIZE + texX;
            int floorSpritesheetY = floorRow * SPRITE_SIZE + texY;
            int ceilingSpritesheetX = ceilingCol * SPRITE_SIZE + texX;
            int ceilingSpritesheetY = ceilingRow * SPRITE_SIZE + texY;

            double floorTotalLight = 0.0;

            for (int i = 0; i < lightCount; i++)
            {
                Light L = lights[i];

                double dx = L.position.x - currentFloorX;
                double dy = L.position.y - currentFloorY;
                double dz = L.position.z - FLOOR_Z;

                double distSq = dx*dx + dy*dy + dz*dz;
                double dist = sqrt(distSq);

                if (dist > L.radius) continue;

                double attenuation = 1.0 / (1.0 + distSq);

                floorTotalLight += attenuation * L.intensity;
            }

            double ceilingTotalLight = 0.0;

            for (int i = 0; i < lightCount; i++)
            {
                Light L = lights[i];

                double dx = L.position.x - currentFloorX;
                double dy = L.position.y - currentFloorY;
                double dz = L.position.z - CEILING_Z;

                double distSq = dx*dx + dy*dy + dz*dz;
                double dist = sqrt(distSq);

                if (dist > L.radius) continue;

                double attenuation = 1.0 / (1.0 + distSq);

                ceilingTotalLight += attenuation * L.intensity;
            }
            
            glColor3f(floorTotalLight, floorTotalLight, floorTotalLight);

            glTexCoord2f((float)floorSpritesheetX / (float)SPRITESHEET_SIZE, (float)floorSpritesheetY / (float)SPRITESHEET_SIZE);
            glVertex2i(x, y);

            glColor3f(ceilingTotalLight, ceilingTotalLight, ceilingTotalLight);

            glTexCoord2f((float)ceilingSpritesheetX / (float)SPRITESHEET_SIZE, (float)ceilingSpritesheetY / (float)SPRITESHEET_SIZE);
            glVertex2i(x, windowH - y);
        }

    }

    glEnd();

    glDisable(GL_TEXTURE_2D);
}