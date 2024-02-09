#include <SDL2/SDL.h>
#include <stdio.h>
#include "SRCE/graphics.h"
int main(int argc, char* args[]){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        printf("Could not init SDL2: \n%s", SDL_GetError());
    }
    init_display();
    while(!should_exit()){
        update();
    }
    quit();
}