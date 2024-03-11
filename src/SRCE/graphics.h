#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
SDL_Window* gameWindow;
SDL_Renderer* gameRenderer;
Uint64 lastTime;
double deltaTime;
bool exited = false;
int colorPalette[20][3] = {{0,0,0},{127,127,127},{136,0,21},{237,28,36},{255,127,39},{255,242,0},{34,177,76},{0,162,232},{63,72,204},{163,73,164},{255,255,255},{195,195,195},{185,122,87},{255,174,201},{255,201,14},{239,228,176},{181,230,29},{153,217,234},{112,146,190},{200,291,231}}; // note modify to use 1D arrays!
int init_display(){
    gameWindow = SDL_CreateWindow("SRCE",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,300,200,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    lastTime = 0;
    gameRenderer = SDL_CreateRenderer(gameWindow,-1,SDL_RENDERER_ACCELERATED);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"0");
    if(gameRenderer == NULL){
        printf("Could not create renderer: \n\t%s", SDL_GetError());
    }
    SDL_RenderSetLogicalSize(gameRenderer,300,200);
    return 0;
}
bool should_exit(){
    return exited;
}
void clear(){
    SDL_SetRenderDrawColor(gameRenderer,0x0,0x0,0x0,0xFF);
    SDL_RenderClear(gameRenderer);
}
void update(){
    int windowWidth;
    int windowHeight;
    SDL_GetWindowSize(gameWindow,&windowWidth,&windowHeight);
    SDL_SetWindowSize(gameWindow,windowWidth,(int)(windowWidth*(200.0/300.0)));
    SDL_RenderPresent(gameRenderer);
    SDL_UpdateWindowSurface(gameWindow);
    deltaTime = (double)((double)(SDL_GetTicks64()-lastTime)/1000);
    lastTime = SDL_GetTicks64();
}
void line(int x1, int y1, int x2, int y2, int color, int divide){
    SDL_SetRenderDrawColor(gameRenderer,colorPalette[color][0]/divide,colorPalette[color][1]/divide,colorPalette[color][2]/divide,SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(gameRenderer,x1,y1,x2,y2);
}
void set_pixel(int x, int y, int color, int divide){
    SDL_SetRenderDrawColor(gameRenderer,colorPalette[color][0]/divide,colorPalette[color][1]/divide,colorPalette[color][2]/divide,SDL_ALPHA_OPAQUE);
    if(x>0 && x<300 && y>0 && y<200){SDL_RenderDrawPoint(gameRenderer,x,y);}
}
void textured_stripe(int textureBuffer[64][64], int x1, int y1, int y2, int clipMax, int clipMin, int textureZoom, int textureRow, int shaded){
    int ty1;
    int ty2;
    int textureY = 0;
    for(int i = 0; i < textureZoom; i++){
        ty1=(int)(y2-((double)((double)(y2-y1)/(double)textureZoom)*i));
        ty2=(int)(y2-((double)((double)(y2-y1)/(double)textureZoom)*(i+1)));
        if(ty2>clipMax){
            ty2 = clipMax;
        }
        if(ty2<clipMin){
            ty2 = clipMin;
        }if(ty1>clipMax){
            ty1 = clipMax;
        }
        if(ty1<clipMin){
            ty1 = clipMin;
        }
        if((ty1-ty2)!=0){
            line(x1,ty1,x1,ty2,textureBuffer[textureRow][textureY],(shaded==1)?1:2);
        }
        textureY++;
        if(textureY>63){
            textureY = 0;
        }
    }
}
void quit(){
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();
}