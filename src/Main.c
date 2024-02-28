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
    int wallType1[64][64];
    int wallType2[64][64];
    int wallType3[64][64];
    int wallType4[64][64];
    int wallType5[64][64];
    auto_load_walls(&wallType1, &wallType2, &wallType3, &wallType4, &wallType5, "DEMOSET");
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        printf("Could not init SDL2: \n\t%s", SDL_GetError());
    }
    init_display();
    clear();
    while(!should_exit()){
        line(0,0,300,200,3);
        for(int i=0;i<64;i++){textured_stripe(wallType1,0+i,64,0,299,1,64,i);}
        for(int i=0;i<64;i++){textured_stripe(wallType2,64+i,64,0,299,1,64,i);}
        for(int i=0;i<64;i++){textured_stripe(wallType3,128+i,64,0,299,1,64,i);}
        for(int i=0;i<64;i++){textured_stripe(wallType4,192+i,64,0,299,1,64,i);}
        for(int i=0;i<64;i++){textured_stripe(wallType5,256+i,64,0,299,1,64,i);}
        update();
    }
    quit();
    return 0;
}