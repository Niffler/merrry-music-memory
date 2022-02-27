#include "card.h"
#include <stdio.h>

void createCards(int screenWidth, int screenHeight, int numRows, int numCols,
                 size_t len, Card cards[len], int cardSize) {
  int cardMargin = 20;

  // init cards
  for (int i = 0; i < len; i = i + 2) {
    cards[i] = (Card){.music = i / 2, .disabled = false};
    cards[i + 1] = cards[i];
  }

  // shuffle cards
  for (int i = 0; i < len; i++) {
    int j = rand() / (RAND_MAX / len);
    int t = cards[i].music;
    cards[i].music = cards[j].music;
    cards[j].music = t;
  }

  // add positions to cards
  for (int i = 0; i < numRows; i++) {
    int offset = i * numCols;
    int row_offset = (cardSize + cardMargin) * i;

    for (int j = 0; j < numCols; j++) {
      cards[offset + j].rect =
          (Rectangle){(cardSize + cardMargin) * j, row_offset, cardSize, cardSize};
    }
  }
}

bool cardSelected(Card* card, int x_offset, int y_offset, Vector2 mousePos) {
  return (card->rect.x + x_offset < mousePos.x && card->rect.y + y_offset < mousePos.y &&
          mousePos.x < (card->rect.x + x_offset + card->rect.width) &&
          mousePos.y < (card->rect.y + y_offset + card->rect.height));
}

void drawCard(Card* card, int cardNumber, int x_offset, int y_offset, Color cardColor, Color textColor, Font font) {
  DrawRectangle(card->rect.x + x_offset, card->rect.y + y_offset, card->rect.width, card->rect.height, cardColor);
  DrawText(TextFormat("%02i", cardNumber+1), card->rect.x+5+x_offset, card->rect.y+5+y_offset, 34.0f, textColor);
}