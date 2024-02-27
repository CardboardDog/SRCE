#define FILE_PATH "C:/SRCE/demo.eyn"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "SRCE/loader.h"
#include "SRCE/graphics.h"
int main(int argc, char* args[]){
    int settings[2];
    load_settings(&settings[0],&settings[1]);
    int playerX = 0, playerY = 0;
    int** level;
    level = malloc(settings[0] * sizeof(*level));
    for (int i = 0; i < settings[1]; i++) {
        level[i] = malloc(settings[0] * sizeof(level[0]));
    }
    load_level(level,&playerX,&playerY,settings[0],settings[1],"DEMO");
    int wallType1[64][64], wallType2[64][64], 
    wallType3[64][64], wallType4[64][64], wallType5[64][64];
    auto_load_walls(&wallType1, &wallType2, &wallType3, &wallType4, &wallType5, "DEMOSET");
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
    return 0;
}