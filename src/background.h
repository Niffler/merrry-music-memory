#ifndef BACKGROUND_H
#define BACKGROUND_H 1
#include <raylib.h>
#include <stdlib.h>

typedef struct Flake {
    Vector2 position;
    Vector2 speed;
    Color color;
    float radius;
} Flake;

void createFlakes(size_t len, Flake flakes[len]);

void drawFlakes(size_t len, Flake flakes[len]);

void updateFlakes(size_t len, Flake flakes[len]);

#endif