#include "graphics.h"
#include <math.h>
int leftRight;
int keyUp;
int keyDown;
int keyLeft;
int keyRight;
SDL_Event event;
void move_player(double* playerX, double* playerY, double* rotationX, double* rotationY, double* planeX, double* planeY){
    double oldRotationY;
    double oldRotationX;
    double oldPlaneY;
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
            }
        }else if(event.type == SDL_QUIT){
            exited = true;
        }
    }
    //printf("%d:%d\n",keyUp,keyDown);
    *playerX += (double)((*rotationX*((deltaTime*5)*(keyUp-keyDown))));
    *playerY += (double)((*rotationY*((deltaTime*5)*(keyUp-keyDown))));
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