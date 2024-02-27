#include <SDL2/SDL.h>
#include <stdbool.h>
SDL_Window* gameWindow;
//SDL_Surface* windowSurface;
SDL_Event displayEvents;
SDL_Renderer* gameRenderer;
int colorPalette[20][3] = {{0,0,0},{127,127,127},{136,0,21},{237,28,36},{255,127,39},{255,242,0},{34,177,76},{0,162,232},{63,72,204},{163,73,164},{255,255,255},{195,195,195},{185,122,87},{255,174,201},{255,201,14},{239,228,176},{181,230,29},{153,217,234},{112,146,190},{200,291,231}}; // note modify to use 1D arrays!
int init_display(){
    gameWindow = SDL_CreateWindow("SRCE",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,300,200,SDL_WINDOW_SHOWN);
    //windowSurface = SDL_GetWindowSurface(gameWindow);
    gameRenderer = SDL_CreateRenderer(gameWindow,-1,SDL_RENDERER_ACCELERATED);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    if(gameRenderer == NULL){
        printf("Could not create renderer: \n\t%s", SDL_GetError());
    }
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
void clear(){
    SDL_SetRenderDrawColor(gameRenderer,0x0,0x0,0x0,0xFF);
    SDL_RenderClear(gameRenderer);
}
void update(){
    SDL_RenderPresent(gameRenderer);
    SDL_UpdateWindowSurface(gameWindow);
}
void line(int x1, int y1, int x2, int y2, int color){
    SDL_SetRenderDrawColor(gameRenderer,colorPalette[color][0],colorPalette[color][1],colorPalette[color][2],SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(gameRenderer,x1,y1,x2,y2);
}
void textured_line(){
    // later
}
void quit(){
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();
}