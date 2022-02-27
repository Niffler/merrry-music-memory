#include "background.h"

void createFlakes(size_t len, Flake flakes[len]) {
  int width = GetScreenWidth();
  int height = GetScreenHeight();
  for (int i = 0; i < len; i++) {
    float radius = (float)GetRandomValue(2, 5);
    flakes[i].position =
        (Vector2){GetRandomValue(0, width), GetRandomValue(0, height)};
    flakes[i].speed.x = 0;
    flakes[i].speed.y = 4.0f / radius;
    flakes[i].color = WHITE;
    flakes[i].radius = radius;
  }
}

void drawFlakes(size_t len, Flake flakes[len]) {
  for (int i = 0; i < len; i++) {
    DrawCircle(flakes[i].position.x, flakes[i].position.y, flakes[i].radius,
               flakes[i].color);
  }
}

Flake generateFlake(int screenWidth) {
  float radius = (float)GetRandomValue(2, 5);
  return (Flake){
      .position.y = 1, 
      .position.x = GetRandomValue(1, screenWidth-1),
      .speed.y = 4.0f / radius,
      .radius = radius,
      .color = WHITE
  };
}

void updateFlakes(size_t len, Flake flakes[len]) {
  int width = GetScreenWidth();
  int height = GetScreenHeight();
  for (int i = 0; i < len; i++) {
    flakes[i].position.x += flakes[i].speed.x;
    flakes[i].position.y += flakes[i].speed.y;

    if ((flakes[i].position.x > width) ||
        (flakes[i].position.x < 0)) {
      flakes[i] = generateFlake(width);
    } else if ((flakes[i].position.y > height) ||
        (flakes[i].position.y < 0)) {
      flakes[i] = generateFlake(width);
    }
  }
}
