#include <string.h>
#include <stdbool.h>
#include <stdio.h>
FILE* gameFile;
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
                return (int)strtol(hexRetrieve, NULL, 16);
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
                return (int)strtol(hexRetrieve, NULL, 16);
            }scanY++;
        }
    }
    fclose(gameFile);
    return 0;
}