#ifndef BACK_H
#define BACK_H

#include <stdbool.h>
#include <SDL/SDL.h>

typedef struct {
    SDL_Surface* image;
    SDL_Surface* secondary_image;
    SDL_Rect camera_pos;
    bool showing_main_image;
} Background;


void initBackground(Background *bg, SDL_Surface *screen, char * chemin1 , char *chemin2);
void toggleBackgroundImage(Background *bg);
void scrollingHorizontal(Background *bg, int dx);
void scrollingVertical(Background *bg, int dy);
void updateBackgroundImage(Background *bg);

#endif /* BACK_H */

