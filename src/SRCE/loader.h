#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
FILE* gameFile;
int char_to_int(char character){
    char digitBuffer[1] = {character};
    if(isdigit((int)character)){
        return (int)strtol(digitBuffer, NULL, 16);
    }else{
        return (int)abs(character-55);
    }
}
int load_level_block(char* level, int x, int y){
    gameFile = fopen(FILE_PATH,"r");
    char charBuffer[68];
    int settingsOpen = 0;
    int scanY = 0;
    char beginLevelName[68] = "NAME ";
    strcat(beginLevelName, level); // NAME [level]
    while(fscanf(gameFile,"%68[^\n]\n",charBuffer)==1){
        if(strcmp(charBuffer,"LBFER:")==0){
            settingsOpen = 1;
        }
        if(settingsOpen==1 && strcmp(charBuffer,beginLevelName)==0){
            settingsOpen = 2;
        }
        if(settingsOpen==2 && strcmp(charBuffer,"LWALL:")==0){
            settingsOpen = 3;
            scanY = 0;
        }else if(settingsOpen==3){
            if(strcmp(charBuffer,"END")==0){
                break;
            }
            if(scanY==y){
                fclose(gameFile);
                char hexRetrieve[1];
                hexRetrieve[0] = charBuffer[x];
                return char_to_int(hexRetrieve[0]);
            }scanY++;
        }
    }
    fclose(gameFile);
    return 0;
}
int load_height_block(char* level, int x, int y){
    gameFile = fopen(FILE_PATH,"r");
    char charBuffer[68];
    int settingsOpen = 0;
    int scanY = 0;
    char beginLevelName[68] = "NAME ";
    strcat(beginLevelName, level); // NAME [level]
    while(fscanf(gameFile,"%68[^\n]\n",charBuffer)==1){
        if(strcmp(charBuffer,"LBFER:")==0){
            settingsOpen = 1;
        }
        if(settingsOpen==1 && strcmp(charBuffer,beginLevelName)==0){
            settingsOpen = 2;
        }
        if(settingsOpen==2 && strcmp(charBuffer,"WHGHT:")==0){
            settingsOpen = 3;
            scanY = 0;
        }else if(settingsOpen==3){
            if(strcmp(charBuffer,"END")==0){
                break;
            }
            if(scanY==y){
                fclose(gameFile);
                char hexRetrieve[1];
                hexRetrieve[0] = charBuffer[x];
                return char_to_int(hexRetrieve[0]);
            }scanY++;
        }
    }
    fclose(gameFile);
    return 0;
}
void load_level_start(char* level, int* x, int* y){
    gameFile = fopen(FILE_PATH,"r");
    char charBuffer[68];
    int settingsOpen = 0;
    int scanY = 0;
    char beginLevelName[68] = "NAME ";
    strcat(beginLevelName, level); // NAME [level]
    while(fscanf(gameFile,"%68[^\n]\n",charBuffer)==1){
        if(strcmp(charBuffer,"LBFER:")==0){
            settingsOpen = 1;
        }
        if(settingsOpen==1 && strcmp(charBuffer,beginLevelName)==0){
            settingsOpen = 2;
        }
        if(settingsOpen==2){
            if(strcmp(charBuffer,"END")==0){
                break;
            }if(strstr(charBuffer, "XSTRT")){
                strtok(charBuffer," ");
                *x = atoi(strtok(NULL,""));
            }else if(strstr(charBuffer, "YSTRT")){
                strtok(charBuffer," ");
                *y = atoi(strtok(NULL,""));
            }
        }
    }
    fclose(gameFile);
}
void load_settings(int* gameWidth, int* gameHeight){
    gameFile = fopen(FILE_PATH,"r");
    char charBuffer[68];
    int settingsOpen = 0;
    while(fscanf(gameFile,"%68[^\n]\n",charBuffer)==1){
        if(strcmp(charBuffer,"SMODE:")==0){
            settingsOpen = 1;
            printf("opening settings\n");
        }
        if(settingsOpen == 1){
            if(strcmp(charBuffer,"END")==0){
                settingsOpen = 0;
                printf("closing settings\n");
            }else if(strstr(charBuffer, "LWDTH")){
                strtok(charBuffer," ");
                *gameWidth = atoi(strtok(NULL,""));
            }else if(strstr(charBuffer, "LHGHT")){
                strtok(charBuffer," ");
                *gameHeight = atoi(strtok(NULL,""));
            }
        }
    }
    fclose(gameFile);
}
int load_texture_pixel(char* level, int x, int y){
    gameFile = fopen(FILE_PATH,"r");
    char charBuffer[68];
    int settingsOpen = 0;
    int scanY = 0;
    char beginLevelName[68] = "NAME ";
    strcat(beginLevelName, level); // NAME [level]
    while(fscanf(gameFile,"%68[^\n]\n",charBuffer)==1){
        if(strcmp(charBuffer,"GMTEX:")==0){
            settingsOpen = 1;
        }
        if(settingsOpen==1 && strcmp(charBuffer,beginLevelName)==0){
            settingsOpen = 2;
        }
        if(settingsOpen==2 && strcmp(charBuffer,"TEXBF:")==0){
            settingsOpen = 3;
            scanY = 0;
        }else if(settingsOpen==3){
            if(strcmp(charBuffer,"END")==0){
                break;
            }
            if(scanY==y){
                fclose(gameFile);
                char hexRetrieve[1];
                hexRetrieve[0] = charBuffer[x];
                return char_to_int(hexRetrieve[0]);
            }scanY++;
        }
    }
    fclose(gameFile);
    return 0;
}
void load_level(int **levelWalls, int* playerX, int* playerY, int levelWidth, int levelHight, char* level){
    for (int y = 0; y < levelWidth; y++){
        for (int x = 0; x < levelHight; x++){
            levelWalls[x][y] = load_level_block(level,x,y);
        }
    }
    load_level_start("DEMO",playerX,playerY);
}
void load_height(int **levelWalls, int levelWidth, int levelHight, char* level){
    for (int y = 0; y < levelWidth; y++){
        for (int x = 0; x < levelHight; x++){
            levelWalls[x][y] = load_height_block(level,x,y);
            printf("[%d]",levelWalls[x][y]);
        }
        printf("\n");
    }
}
void load_texture(int (*textureBuffer)[64][64], char* texture){
    for (int y = 0; y < 64; y++){
        for (int x = 0; x < 64; x++){
            (*textureBuffer)[x][y]=load_texture_pixel(texture,x,y);
        }
    }
}
void load_texture_set(int (*textureBuffer)[64][64], char* texture, char* textureSet){
    gameFile = fopen(FILE_PATH,"r");
    char charBuffer[68];
    int settingsOpen = 0;
    int scanY = 0;
    char beginLevelName[68] = "NAME ";
    char* xxxxx;
    strcat(beginLevelName, textureSet); // NAME [level]
    while(fscanf(gameFile,"%68[^\n]\n",charBuffer)==1){
        if(strcmp(charBuffer,"TEXST:")==0){
            settingsOpen = 1;
        }
        if(settingsOpen==1 && strcmp(charBuffer,beginLevelName)==0){
            settingsOpen = 2;
        }
        if(settingsOpen==2 && strcmp(charBuffer,"TEXPT:")==0){
            settingsOpen = 3;
            scanY = 0;
        }else if(settingsOpen==3){
            if(strcmp(charBuffer,"END")==0){
                break;
            }
            if(strcmp(strtok(charBuffer," "),texture)==0){
                xxxxx = strtok(NULL,"");
                printf("%s:",texture);
                printf("%s\n",xxxxx);
                load_texture(textureBuffer,xxxxx);
            }
        }
    }
    fclose(gameFile);
}
void auto_load_walls(int (*textureBuffer)[64][64], int (*textureBuffer2)[64][64], int (*textureBuffer3)[64][64], int (*textureBuffer4)[64][64], int (*textureBuffer5)[64][64], char* textureSet){
    load_texture_set(textureBuffer, "WTYPE1", textureSet);
    load_texture_set(textureBuffer2, "WTYPE2", textureSet);
    load_texture_set(textureBuffer3, "WTYPE3", textureSet);
    load_texture_set(textureBuffer4, "WTYPE4", textureSet);
    load_texture_set(textureBuffer5, "WTYPE5", textureSet);
    printf("loaded texture set walls: %s\n",textureSet);
}