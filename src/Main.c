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
    for (int y = 0; y < settings[1]; y++){
        for (int x = 0; x < settings[0]; x++){
            level[x][y] = load_level_block("DEMO",x,y);
            printf("[%d]",load_level_block("DEMO",x,y));
        }
        printf("\n");
    }
    load_level_start("DEMO",&playerX,&playerY);
    for (int y = 0; y < 64; y++){
        for (int x = 0; x < 64; x++){
            printf("[%d]",load_texture_pixel("WTYPE1",x,y));
        }
        printf("\n");
    }
    printf("PX:[%d]\n",playerX);
    printf("PY:[%d]\n",playerY);
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