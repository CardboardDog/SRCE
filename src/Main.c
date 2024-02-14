#define FILE_PATH "C:/SRCE/demo.eyn"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "SRCE/loader.h"
#include "SRCE/graphics.h"
int main(int argc, char* args[]){
    load_settings("sss");
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        printf("Could not init SDL2: \n\t%s", SDL_GetError());
    }
    init_display();
    clear();
    while(!should_exit()){
        line(0,0,300,200,3);
        update();
    }
    quit();
}