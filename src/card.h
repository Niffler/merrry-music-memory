#ifndef CARD_H
#define CARD_H 1
#include <raylib.h>
#include <stdlib.h>

typedef struct Card {
  Rectangle rect;
  int music;
  bool disabled;
} Card;

void createCards(int screenWidth, int screenHeight, int numRows, int numCols, size_t len, Card cards[], int cardSize);

bool cardSelected(Card* card, int x_offset, int y_offset, Vector2 mousePos);

void drawCard(Card* card, int cardNumber, int x_offset, int y_offset, Color cardColor, Color textColor, Font font);

#endif