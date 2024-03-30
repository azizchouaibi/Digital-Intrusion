#ifndef BACK_H
#define BACK_H

#include <SDL/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCROLL_SPEED_X 5
#define SCROLL_SPEED_Y 5

typedef struct Background {
    SDL_Surface *image;
    SDL_Rect camera_pos;
    int direction;
    bool on;
} Background;

void initBackground(Background *background1, Background *background2);

void scrolling(Background *background1, Background *background2, int direction, int dx, int dy);

#endif /* BACK_H */

