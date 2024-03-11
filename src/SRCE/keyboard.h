#include "graphics.h"
#include <math.h>
SDL_Event event;
int leftRight;
int keyUp;
int keyDown;
int keyLeft;
int keyRight;
int keySpace;
double gravity = 0;
void move_player(double* playerX, double* playerY, double* playerZ, double* rotationX, double* rotationY, double* planeX, double* planeY, int** levelBuffer, int wSettings[2]){
    double oldRotationX;
    double oldPlaneX;
    while(SDL_PollEvent(&event)==1){
        if(event.type == SDL_KEYUP){
            if(event.key.keysym.sym == SDLK_UP){
                keyUp = 0;
            }else if(event.key.keysym.sym == SDLK_DOWN){
                keyDown = 0;
            }if(event.key.keysym.sym == SDLK_RIGHT){
                keyRight = 0;
            }else if(event.key.keysym.sym == SDLK_LEFT){
                keyLeft = 0;
            }if(event.key.keysym.sym == SDLK_SPACE){
                keySpace = 0;
            }
        }else if(event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_UP){
                keyUp = 1;
            }else if(event.key.keysym.sym == SDLK_DOWN){
                keyDown = 1;
            }if(event.key.keysym.sym == SDLK_RIGHT){
                keyRight = 1;
            }else if(event.key.keysym.sym == SDLK_LEFT){
                keyLeft = 1;
            }if(event.key.keysym.sym == SDLK_SPACE){
                keySpace = 1;
            }
        }else if(event.type == SDL_QUIT){
            exited = true;
        }
    }
    int checkBoxX = (int)(*playerX+(double)((*rotationX*((deltaTime*5)*(keyUp-keyDown)))));
    int checkBoxY = (int)(*playerY+(double)((*rotationY*((deltaTime*5)*(keyUp-keyDown)))));
    if(checkBoxX<wSettings[0] && checkBoxX>-1 && checkBoxY<wSettings[1] && checkBoxY>-1){
        if(levelBuffer
            [checkBoxX]
            [(int)*playerY]-*playerZ<3){
            *playerX += (double)((*rotationX*((deltaTime*5)*(keyUp-keyDown))));
        }if(levelBuffer
            [(int)(*playerX)]
            [checkBoxY]-*playerZ<3){
            *playerY += (double)((*rotationY*((deltaTime*5)*(keyUp-keyDown))));
        }
    }
    if((double)(levelBuffer[(int)(*playerX)][(int)(*playerY)])>*playerZ){
        *playerZ = (double)(levelBuffer[(int)(*playerX)][(int)(*playerY)]);
        gravity = 0.0;
    }else if(*playerZ>levelBuffer[(int)(*playerX)][(int)(*playerY)]){
        gravity += deltaTime;
        *playerZ -= gravity;
    }
    if(keyLeft == 1){
        oldRotationX = *rotationX;
        *rotationX = *rotationX*cos(5*deltaTime)-*rotationY*sin(5*deltaTime);
        *rotationY = oldRotationX*sin(5*deltaTime)+*rotationY*cos(5*deltaTime);
        oldPlaneX = *planeX;
        *planeX = *planeX*cos(5*deltaTime)-*planeY*sin(5*deltaTime);
        *planeY = oldPlaneX*sin(5*deltaTime)+*planeY*cos(5*deltaTime);
    }else if(keyRight == 1){
        oldRotationX = *rotationX;
        *rotationX = *rotationX*cos(-5*deltaTime)-*rotationY*sin(-5*deltaTime);
        *rotationY = oldRotationX*sin(-5*deltaTime)+*rotationY*cos(-5*deltaTime);
        oldPlaneX = *planeX;
        *planeX = *planeX*cos(-5*deltaTime)-*planeY*sin(-5*deltaTime);
        *planeY = oldPlaneX*sin(-5*deltaTime)+*planeY*cos(-5*deltaTime);
    }
}