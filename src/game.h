#ifndef GAME_H
#define GAME_H 1
#include <raylib.h>
#include "card.h"
#include "music.h"

typedef struct Game {
  enum {
    STATE_LOADING,
    STATE_WAITING,
    STATE_RUNNING,
    STATE_FINISHED
  } gameState;

  float playLength;
  float timePlayed;
  bool isPlaying;
  int musicIdx;

  int lenPlayer;
  int currentPlayer;
  int player[8];

  int selected;
  int selCards[2];

  Font font;
} Game;

void drawText(const char* text, int x_offset, int y, int width, int fontSize,
              Color color);
bool drawWelcome(Game* game);
void drawEndcard(Game* game);
void drawBoard(Game* game, int x_offset, int y_offset, size_t lenCards,
               Card cards[lenCards], Vector2 mousePos, bool isMouseClicked);
void drawPlayers(Game* game, Color textColor, Color highlightColor);

void updateGameState(Game* game, int x_offset, int y_offset, size_t lenCards,
                     Card cards[lenCards], size_t lenSongs,
                     Music songs[lenSongs], Vector2 mousePos,
                     bool isMouseClicked);

#endif