#ifndef MUSIC_H
#define MUSIC_H 1
#include <stdio.h>
#include <raylib.h>
#include "card.h"

char* fgetline(size_t size, char s[], FILE* stream);
int loadSongFile(char* filename, size_t len, Music songs[]);
void drawProgressBar(int posX, int posY, float timePlayed, float totalTime);

#endif