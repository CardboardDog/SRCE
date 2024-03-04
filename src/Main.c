#define FILE_PATH "C:/SRCE/demo.eyn"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "SRCE/loader.h"
#include "SRCE/keyboard.h"
int main(int argc, char *args[])
{
    int settings[2];
    load_settings(&settings[0], &settings[1]);
    int startX, startY;
    double playerX, playerY, playerZ;
    double rotationX = -1, rotationY = 0;
    double planeX = 0, planeY = 0.66;
    double cameraX, rayRotationX, rayRotationY;
    double sideDistanceX, sideDistanceY;
    double deltaDistanceX, deltaDistanceY;
    double perpWallDistance;
    int stepX;
    int stepY;
    int wallHit, side;
    int cellX, cellY;
    double wallX;
    int textureRow;
    int **level;
    int **levelHeight;
    int renderHeight, renderY1, renderY2;
    int clipHeight;
    level = malloc(settings[0] * sizeof(*level));
    for (int i = 0; i < settings[1]; i++)
    {
        level[i] = malloc(settings[0] * sizeof(level[0]));
    }
    levelHeight = malloc(settings[0] * sizeof(*levelHeight));
    for (int i = 0; i < settings[1]; i++)
    {
        levelHeight[i] = malloc(settings[0] * sizeof(levelHeight[0]));
    }
    load_level(level, &startX, &startY, settings[0], settings[1], "DEMO");
    load_height(levelHeight, settings[0], settings[1], "DEMO");
    playerX = (double)startX;
    playerY = (double)startY;
    playerZ = 0.0;
    int wallType1[64][64], wallType2[64][64],
        wallType3[64][64], wallType4[64][64], wallType5[64][64];
    auto_load_walls(&wallType1, &wallType2, &wallType3, &wallType4, &wallType5, "DEMOSET");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Could not init SDL2: \n\t%s", SDL_GetError());
    }
    init_display();
    clear();
    while (!should_exit())
    {
        clear();
        for (int i = 0; i < 300; i++)
        {
            clipHeight = 200;
            cameraX = 2 * i / (double)300 - 1;
            rayRotationX = rotationX + planeX * cameraX;
            rayRotationY = rotationY + planeY * cameraX;
            cellX = (int)playerX;
            cellY = (int)playerY;
            deltaDistanceX = (rayRotationX == 0) ? 1e30 : fabs(1 / rayRotationX);
            deltaDistanceY = (rayRotationY == 0) ? 1e30 : fabs(1 / rayRotationY);
            wallHit = 0;
            if (rayRotationX < 0)
            {
                stepX = -1;
                sideDistanceX = (playerX - cellX) * deltaDistanceX;
            }
            else
            {
                stepX = 1;
                sideDistanceX = (cellX + 1.0 - playerX) * deltaDistanceX;
            }
            if (rayRotationY < 0)
            {
                stepY = -1;
                sideDistanceY = (playerY - cellY) * deltaDistanceY;
            }
            else
            {
                stepY = 1;
                sideDistanceY = (cellY + 1.0 - playerY) * deltaDistanceY;
            }
            while (wallHit == 0)
            {
                if (sideDistanceX < sideDistanceY)
                {
                    sideDistanceX += deltaDistanceX;
                    cellX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistanceY += deltaDistanceY;
                    cellY += stepY;
                    side = 1;
                }
                if ((cellX > (settings[0] - 1)) || (cellY > (settings[1] - 1)) || (cellX < 0) || (cellY < 0))
                {
                    wallHit = 1;
                    break;
                }
                if (level[cellX][cellY] > 0)
                {
                    if (side == 0)
                    {
                        perpWallDistance = sideDistanceX - deltaDistanceX;
                    }
                    else
                    {
                        perpWallDistance = sideDistanceY - deltaDistanceY;
                    }
                    renderHeight = (int)(200 / perpWallDistance);
                    renderY1 = 100 + (renderHeight / 2);
                    renderY2 = (int)((double)renderY1 - (double)(renderHeight / 4.0) * (double)(levelHeight[cellX][cellY]));
                    renderY1 += (int)(((double)renderHeight / 4.0) * (playerZ+0.5));
                    renderY2 += (int)(((double)renderHeight / 4.0) * (playerZ+0.5));
                    if (side == 0)
                    {
                        wallX = playerY + perpWallDistance * rayRotationY;
                    }
                    else
                    {
                        wallX = playerX + perpWallDistance * rayRotationX;
                    }
                    wallX -= floor(wallX);
                    textureRow = (int)(wallX * 64.0);
                    if (side == 0 && rayRotationX > 0)
                    {
                        textureRow = 64 - textureRow - 1;
                    }
                    else if (side == 1 && rayRotationY < 0)
                    {
                        textureRow = 64 - textureRow - 1;
                    }
                    textured_stripe(wallType5, i, renderY2, renderY1, clipHeight, 0, 64, 3, 1);
                    switch (level[cellX][cellY])
                    {
                    case 1:
                        textured_stripe(wallType1, i, renderY2, renderY1, clipHeight, 0, 64, textureRow, side);
                        break;
                    case 2:
                        textured_stripe(wallType2, i, renderY2, renderY1, clipHeight, 0, 64, textureRow, side);
                        break;
                    case 3:
                        textured_stripe(wallType3, i, renderY2, renderY1, clipHeight, 0, 64, textureRow, side);
                        break;
                    case 4:
                        textured_stripe(wallType4, i, renderY2, renderY1, clipHeight, 0, 64, textureRow, side);
                        break;
                    default:
                        textured_stripe(wallType5, i, renderY2, renderY1, clipHeight, 0, 64, textureRow, side);
                        break;
                    }
                    if (renderY1 < clipHeight)
                    {
                        clipHeight = renderY1;
                    }
                    if (renderY2 < clipHeight)
                    {   
                        clipHeight = renderY2;
                    }
                    double sideDistanceX1 = sideDistanceX;
                    double sideDistanceY1 = sideDistanceY;
                    double perpWallDistance1;
                    // back faces
                    if (sideDistanceX < sideDistanceY)
                    {
                        sideDistanceX1 += deltaDistanceX;
                        perpWallDistance1 = sideDistanceX1 - deltaDistanceX;
                    }
                    else
                    {
                        sideDistanceY1 += deltaDistanceY;
                        perpWallDistance1 = sideDistanceY1 - deltaDistanceY;
                    }
                    renderHeight = (int)(200 / perpWallDistance1);
                    renderY1 = 100 + (renderHeight / 2);
                    renderY2 = (int)((double)renderY1 - ((double)renderHeight / 4.0) * (double)(levelHeight[cellX][cellY]));
                    renderY1 += (int)(((double)renderHeight / 4.0) * (playerZ+0.5));
                    renderY2 += (int)(((double)renderHeight / 4.0) * (playerZ+0.5));
                    textured_stripe(wallType5, i, renderY2, clipHeight, clipHeight, 0, 64, 3, 1);
                    if (renderY2 < clipHeight)
                    {   
                        clipHeight = renderY2;
                    }
                    if (renderY1 < clipHeight)
                    {   
                        clipHeight = renderY1;
                    }
                }
            }
        }
        move_player(&playerX, &playerY, &playerZ, &rotationX, &rotationY, &planeX, &planeY, levelHeight);
        update();
    }
    quit();
    return 0;
}