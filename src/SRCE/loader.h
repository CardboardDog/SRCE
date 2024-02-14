#include <string.h>
#include <stdbool.h>
#include <stdio.h>
FILE* gameFile;
void load_settings(char levelName[]){
    gameFile = fopen(FILE_PATH,"r");
    char charBuffer[68];
    while(fscanf(gameFile,"%68[^\n]\n",charBuffer)==1){
        printf("%s[\\N]\n",charBuffer);
    }
    fclose(gameFile);
}