#include "music.h"
#include <string.h>

enum {
  buf_max = 1024,
};

char* fgetline(size_t size, char s[restrict size], FILE* restrict stream) {
  s[0] = 0;
  char* ret = fgets(s, size, stream);

  if (ret) {
    char* pos = strchr(s, '\n');
    if (pos) {
      *pos = 0;
    } else {
      ret = 0;
    }
  }
  return ret;
}

int loadSongFile(char* folder, size_t len, Music songs[len]) {
  char buffer[buf_max] = {0};
  char filename[len][buf_max];

  snprintf(buffer, buf_max, "%snames.txt", folder);
  FILE* instream = fopen(buffer, "r");

  if (instream) {
    int i = 0;
    while (fgetline(buf_max, buffer, instream)) {
      if (i >= len) {
        int j = i % len;
        if (rand() / (RAND_MAX / 2) == 1) {
          snprintf(filename[j], buf_max, "%s%s", folder, buffer);
        }
      } else {
        snprintf(filename[i], buf_max, "%s%s", folder, buffer);
      }
      i++;
    }
    fclose(instream);
  } else {
    fprintf(stderr, "Could not open '%s'", folder);
    return 1;
  }

  for (int i = 0; i < len; i++) {
    int j = rand() / (RAND_MAX / len);
    char s[buf_max];
    strncpy(s, filename[i], buf_max);
    strncpy(filename[i], filename[j], buf_max);
    strncpy(filename[j], s, buf_max);
  }

  for (int i = 0; i < len; i++) {
    songs[i] = LoadMusicStream(filename[i]);
  }

  return 0;
}

void drawProgressBar(int posX, int posY, float timePlayed, float totalTime) {
  int timeProgress = timePlayed / totalTime * 400;
  DrawRectangle(posX, posY, 400, 12, LIGHTGRAY);
  DrawRectangle(posX, posY, timeProgress, 12, MAROON);
  DrawRectangleLines(posX, posY, 400, 12, GRAY);
}
