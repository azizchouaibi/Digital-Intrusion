#include "back.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>

 int LargeurEcran;
 int HauteurEcran;
 int LargeurImageBackground;
 int HauteurImageBackground;
 Uint32 last_image_change_time=0;

void initBackground(Background *bg, SDL_Surface *screen,char* chemin1 , char * chemin2) {
    bg->image = IMG_Load(chemin1);
    if (bg->image == NULL) {
        printf("Erreur lors du chargement de l'image de fond principale : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    bg->secondary_image = IMG_Load(chemin2);
    if (bg->secondary_image == NULL) {
        printf("Erreur lors du chargement de l'image de fond secondaire : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    bg->camera_pos.x = 0;
    bg->camera_pos.y = 0;
    bg->camera_pos.w = screen->w;
    bg->camera_pos.h = screen->h;
    bg->showing_main_image = true;
}

void toggleBackgroundImage(Background *bg) {
    bg->showing_main_image = !bg->showing_main_image;
}

void scrollingHorizontal(Background *bg, int dx) {
    bg->camera_pos.x += dx;

    if (bg->camera_pos.x >= bg->image->w - bg->camera_pos.x  ) {
        bg->camera_pos.x = 0;

    } else if (bg->camera_pos.x < 0) {
        bg->camera_pos.x = bg->image->w - bg->camera_pos.w;
    }
}

void scrollingVertical(Background *bg, int dy) {
    bg->camera_pos.y += dy;

    if (bg->camera_pos.y >= bg->image->h) {
        bg->camera_pos.y = 0;
    } else if (bg->camera_pos.y < 0) {
        bg->camera_pos.y = bg->image->h - bg->camera_pos.h;
    }
}

void updateBackgroundImage(Background *bg) {
    Uint32 current_time = SDL_GetTicks();
    if (current_time - last_image_change_time >= 1000) {
        toggleBackgroundImage(bg);
        last_image_change_time = current_time;
    }
}

