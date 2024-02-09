#include <SDL2/SDL.h>
#include <stdbool.h>
SDL_Window* gameWindow;
SDL_Surface* windowSurface;
SDL_Event displayEvents;
int init_display(){
    gameWindow = SDL_CreateWindow("SRCE",0,0,300,200,SDL_WINDOW_SHOWN);
    windowSurface = SDL_GetWindowSurface(gameWindow);
    return 0;
}
bool should_exit(){
    while(SDL_PollEvent(&displayEvents)){
        if(displayEvents.type == SDL_QUIT){
            return true;
        }
    }
    return false;
}
void update(){
    SDL_FillRect(windowSurface,NULL,SDL_MapRGB(windowSurface->format,0x0,0x0,0x0));
    SDL_UpdateWindowSurface(gameWindow);
}
void quit(){
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();
}