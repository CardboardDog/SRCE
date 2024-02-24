#define FILE_PATH "C:/SRCE/demo.eyn"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "SRCE/loader.h"
#include "SRCE/graphics.h"
int main(int argc, char* args[]){
    int settings[2];
    load_settings(&settings[0],&settings[1]);
    int** level;
    level = malloc(settings[0] * sizeof(*level));
    for (int i = 0; i < settings[1]; i++) {
        level[i] = malloc(settings[0] * sizeof(level[0]));
    }
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        printf("Could not init SDL2: \n\t%s", SDL_GetError());
    }
    init_display();
    clear();
    printf("x6y4:%d",load_level_block("DEMO",6,4));
    while(!should_exit()){
        line(0,0,300,200,3);
        update();
    }
    quit();
    return 0;
}