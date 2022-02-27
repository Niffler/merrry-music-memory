#include "game.h"

void drawText(const char* text, int x_offset, int y, int width, int fontSize,
              Color color) {
  int x = MeasureText(text, fontSize);
  x = (width / 2) - (x / 2);
  DrawText(text, x_offset + x, y, fontSize, color);
}

bool drawWelcome(Game* game) {
  int selected = false;
  Vector2 touchPos = {-1, -1};

  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    touchPos = GetMousePosition();
  } 

  for (int i = 0; i < 8; i++) {
    int x = GetScreenWidth() / 2 - 320 + i * 80;
    int y = GetScreenHeight() / 2;
    DrawRectangle(x, y, 60, 60, DARKGREEN);
    DrawText(TextFormat("%1d", i + 1), x + 5, y + 5, 34.0f, WHITE);

    if (touchPos.x > x && touchPos.x < x + 60 && touchPos.y > y && touchPos.y < y + 60) {
      game->lenPlayer = i + 1;
      selected = true;
    }
  }

  int width = GetScreenWidth();
  int height = GetScreenHeight() / 2 - 80;

  drawText("Welcome to Merry Music Memory", 0, height, width, 30, LIGHTGRAY);
  drawText("Start the game by choosing the number of players.", 0, height + 40,
           width, 20, LIGHTGRAY);

  return selected;
}

void drawEndcard(Game* game) {
  int player = 0;
  int number = 0;

  for (int i = 0; i < game->lenPlayer; i++) {
    if (game->player[i] > number) {
      number = game->player[i];
      player = i;
    }
  }

  drawText(TextFormat("Player %d won. Congratulations.", player + 1), 0,
           GetScreenHeight() / 2 - 80, GetScreenWidth(), 30, LIGHTGRAY);
}

void drawBoard(Game* game, int x_offset, int y_offset, size_t lenCards,
               Card cards[lenCards], Vector2 mousePos, bool isMouseClicked) {
  for (int i = 0; i < lenCards; i++) {
    Card* card = &cards[i];

    if (!card->disabled) {
      drawCard(card, i, x_offset, y_offset, MAROON, WHITE, game->font);
    }
  }

  for (int i = 0; i < game->selected; i++) {
    drawCard(&cards[game->selCards[i]], game->selCards[i], x_offset, y_offset,
             WHITE, MAROON, game->font);
  }
}

void updateGameState(Game* game, int x_offset, int y_offset, size_t lenCards,
                     Card cards[lenCards], size_t lenSongs,
                     Music songs[lenSongs], Vector2 mousePos,
                     bool isMouseClicked) {
  bool allDisabled = true;
  for (int i = 0; i < lenCards; i++) {
    if (!cards[i].disabled) {
      allDisabled = false;
      break;
    }
  }
  if (allDisabled) {
    game->gameState = STATE_FINISHED;
  }

  if (game->isPlaying) {
    game->timePlayed = GetMusicTimePlayed(songs[game->musicIdx]);
    if (game->timePlayed > game->playLength) {
      StopMusicStream(songs[game->musicIdx]);
      game->timePlayed = 0.0f;
      game->isPlaying = false;
    }
  } else if (game->selected == 2) {
    if (cards[game->selCards[0]].music == cards[game->selCards[1]].music) {
      cards[game->selCards[0]].disabled = true;
      cards[game->selCards[1]].disabled = true;

      game->player[game->currentPlayer]++;
    } else {
      game->currentPlayer++;
      if (game->currentPlayer >= game->lenPlayer) {
        game->currentPlayer = 0;
      }
    }
    game->selected = 0;
  } else if (isMouseClicked) {
    for (int i = 0; i < lenCards; i++) {
      Card* card = &cards[i];
      if (cardSelected(card, x_offset, y_offset, mousePos) &&
          (game->selected == 0 || i != game->selCards[0])) {
        game->isPlaying = true;
        game->musicIdx = card->music;
        game->selCards[game->selected] = i;
        game->selected++;

        PlayMusicStream(songs[game->musicIdx]);
      }
    }
  }
}

void drawPlayers(Game* game, Color textColor, Color highlightColor) {
  int width = GetScreenWidth() / game->lenPlayer;
  for (int i = 0; i < game->lenPlayer; i++) {
    Color color = textColor;
    if (i == game->currentPlayer) {
      color = highlightColor;
    }
    drawText(TextFormat("%02i", game->player[i]), i * width, 10, width, 30,
             color);
  }
}