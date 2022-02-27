#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "background.h"
#include "card.h"
#include "game.h"
#include "music.h"

const int numSongs = 18;
Music songs[18];

const int CARD_ROWS = 2;
const int CARD_COLUMNS = 2;
const int totalCards = 4;
Card cards[4];

const size_t lenFlakes = 400;
Flake flakes[400];

Game game;

Vector2 mousePos = {0.0f};
bool isMouseClicked = false;

void updateDrawFrame(void);

int main(void) {
  int screenWidth = 800;
  int screenHeight = 600;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight, "Merry Music Memory");
  SetWindowMinSize(screenWidth, screenHeight);

  game = (Game){.gameState = STATE_LOADING,
                .font = GetFontDefault(),
                .playLength = 5.0f,
                .isPlaying = false,
                .lenPlayer = 0,
                .currentPlayer = 0};

  createCards(screenWidth, screenHeight, CARD_ROWS, CARD_COLUMNS, totalCards,
              cards, 60);
  createFlakes(lenFlakes, flakes);

  InitAudioDevice();
  if (loadSongFile("resources/christmas_songs/", numSongs, songs)) {
    return 1;
  }
  game.gameState = STATE_WAITING;

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    updateDrawFrame();
  }

  for (int i = 0; i < numSongs; i++) {
    UnloadMusicStream(songs[i]);
  }

  CloseAudioDevice();
  CloseWindow();

  return 0;
}

void updateDrawFrame() {
  int x_offset = GetScreenWidth() / 2;
  x_offset -= CARD_COLUMNS / 2 * 80;

  int y_offset = GetScreenHeight() / 2;
  y_offset -= CARD_ROWS / 2 * 80;

  mousePos = GetMousePosition();
  isMouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawFPS(5,5);
  drawFlakes(lenFlakes, flakes);

  if (game.gameState == STATE_RUNNING) {
    UpdateMusicStream(songs[game.musicIdx]);
    drawBoard(&game, x_offset, y_offset, totalCards, cards, mousePos,
              isMouseClicked);
    drawPlayers(&game, MAROON, DARKGREEN);
    drawProgressBar(GetScreenWidth() / 2 - 200, GetScreenHeight() - 40, game.timePlayed, game.playLength);
  } else if (game.gameState == STATE_WAITING) {
    if (drawWelcome(&game)) {
      game.gameState = STATE_RUNNING;
    }
  } else if (game.gameState == STATE_LOADING) {
    drawText("Press to start.", 0, GetScreenHeight() / 2 - 80, GetScreenWidth(),
             30, LIGHTGRAY);

  } else if (game.gameState == STATE_FINISHED) {
    drawEndcard(&game);
  }

  EndDrawing();
  updateFlakes(lenFlakes, flakes);

  if (game.gameState == STATE_RUNNING) {
    updateGameState(&game, x_offset, y_offset, totalCards, cards, numSongs, songs, mousePos,
                    isMouseClicked);
  }
}