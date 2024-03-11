#define FILE_PATH "C:/SRCE/demo.eyn"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "SRCE/loader.h"
#include "SRCE/keyboard.h"
int startX, startY;
double rotationX = -1.0, rotationY = 0.0;
double planeX = 0, planeY = 0.66;
double cameraX, rayRotationX, rayRotationY;
double sideDistanceX, sideDistanceY;
double deltaDistanceX, deltaDistanceY;
double perpWallDistance;
double floorZoom = 0.0;
int stepX;
int stepY;
int wallHit, side;
int cellX, cellY;
double wallX;
int textureRow;
int renderHeight, renderY1, renderY2;
int clipHeight;
int settings[2];
//float rayRotationX1;
//float rayRotationY1;
//float rayRotationX2;
//float rayRotationY2;
//float rowDistance;
//float floorStepX;
//float floorStepY;
//float floorX;
//float floorY;
int wallType1[64][64], wallType2[64][64],
wallType3[64][64], wallType4[64][64], wallType5[64][64];
int main(int argc, char *args[])
{
    double playerX, playerY, playerZ;
    int **level;
    int **levelHeight;
    int **levelFloor;
    load_settings(&settings[0], &settings[1]);
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
    levelFloor = malloc(settings[0] * sizeof(*levelFloor));
    for (int i = 0; i < settings[1]; i++)
    {
        levelFloor[i] = malloc(settings[0] * sizeof(levelFloor[0]));
    }
    load_level(level, &startX, &startY, settings[0], settings[1], "DEMO");
    load_height(levelHeight, settings[0], settings[1], "DEMO");
    load_floors(levelFloor, settings[0], settings[1], "DEMO");
    playerX = (double)startX;
    playerY = (double)startY;
    playerZ = 0.0;
    auto_load_walls(&wallType1, &wallType2, &wallType3, &wallType4, &wallType5, "DEMOSET");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Could not init SDL2: \n\t%s", SDL_GetError());
    }
    init_display();
    clear();
    for(int i = 0; i<settings[0]; i++){
        for(int ii = 0; ii<settings[1]; ii++){
            printf("[%d]",levelHeight[ii][i]);
        }
        printf("\n");
    }
    while (!should_exit())
    {
        clear();
        // not currently working
        /*for (int i = 0; i < 100; i++){
            rayRotationX1 = (float)(rotationX - planeX);
            rayRotationY1 = (float)(rotationY - planeY);
            rayRotationX2 = (float)(rotationX + planeX);
            rayRotationY2 = (float)(rotationY + planeY);
            rowDistance = (float)((100.0*1.3)/((float)i-100.0));
            floorStepX = (rowDistance*(rayRotationX2-rayRotationX1))/300.0;
            floorStepY = (rowDistance*(rayRotationY2-rayRotationY1))/300.0;
            floorX = (float)(0.0-playerX + ((float)rowDistance) * ((float)rayRotationX1));
            floorY = (float)(0.0-playerY + ((float)rowDistance) * ((float)rayRotationY1));
            for(int ii = 0; ii < 300; ii++){
                int gridX = (int)floorX;
                int gridY = (int)floorY;
                int textureX = (int)(64 * (floorX - (float)gridX)) & (64 - 1);
                int textureY = (int)(64 * (floorY - (float)gridY)) & (64 - 1);
                floorX += floorStepX;
                floorY += floorStepY;
                if((0.0f-floorX)<settings[0] && (0.0f-floorY)<settings[1] && (0.0f-floorX)>0.0f && (0.0f-floorY)>0.0f){
                    if((((int)(gridX + gridY)) & 1) == 0){
                        set_pixel(ii,200-i-1,wallType1[textureX][textureY],1);
                    }else{
                        set_pixel(ii,200-i-1,wallType2[textureX][textureY],1);
                    }
                }
            }
        }*/
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
                    switch (level[cellX][cellY])
                    {
                    case 1:
                        textured_stripe(wallType1, i, renderY2, renderY1, clipHeight, 0, (int)(((double)levelHeight[cellX][cellY]/4.0)*64.0), textureRow, side);
                        break;
                    case 2:
                        textured_stripe(wallType2, i, renderY2, renderY1, clipHeight, 0, (int)(((double)levelHeight[cellX][cellY]/4.0)*64.0), textureRow, side);
                        break;
                    case 3:
                        textured_stripe(wallType3, i, renderY2, renderY1, clipHeight, 0, (int)(((double)levelHeight[cellX][cellY]/4.0)*64.0), textureRow, side);
                        break;
                    case 4:
                        textured_stripe(wallType4, i, renderY2, renderY1, clipHeight, 0, (int)(((double)levelHeight[cellX][cellY]/4.0)*64.0), textureRow, side);
                        break;
                    default:
                        textured_stripe(wallType5, i, renderY2, renderY1, clipHeight, 0, (int)(((double)levelHeight[cellX][cellY]/4.0)*64.0), textureRow, side);
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
                    textured_stripe(wallType5, i, renderY2, clipHeight, clipHeight, 0, 64, 2, 1);
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
        move_player(&playerX, &playerY, &playerZ, &rotationX, &rotationY, &planeX, &planeY, levelHeight, settings);
        update();
    }
    free(level);
    free(levelFloor);
    free(levelHeight);
    quit();
    return 0;
}