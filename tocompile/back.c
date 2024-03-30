#include "back.h"
#include <SDL/SDL_image.h>
#include "perso.h"
void initBackground(Background *background1, Background *background2) {
    background1->image = IMG_Load("ack1.png");
    background2->image = IMG_Load("ack2 (2).png");
    
    background1->camera_pos.x = 0;
    background1->camera_pos.y = 0;
    background1->camera_pos.w = SCREEN_WIDTH;
    background1->camera_pos.h = SCREEN_HEIGHT;

    background2->camera_pos.x = 1920;
    background2->camera_pos.y = 0;
    background2->camera_pos.w = SCREEN_WIDTH;
    background2->camera_pos.h = SCREEN_HEIGHT;
    
    background1->direction = 0;
    background2->direction = 0;
}

void scrolling(Background *background1, Background *background2, int direction, int dx, int dy) {
    if (direction == 0) { // Défilement horizontal
        background1->camera_pos.x += dx;
        background2->camera_pos.x += dx;

        if (background1->camera_pos.x <= background1->image->w) {
            background1->camera_pos.x = background2->camera_pos.x + SCREEN_WIDTH;
        } else if (background1->camera_pos.x >= SCREEN_WIDTH) {
            background1->camera_pos.x = background2->camera_pos.x - background1->image->w;
        }

        if (background2->camera_pos.x <= -background2->image->w) {
            background2->camera_pos.x = background1->camera_pos.x + SCREEN_WIDTH;
        } else if (background2->camera_pos.x >= SCREEN_WIDTH) {
            background2->camera_pos.x = background1->camera_pos.x - background2->image->w;
        }
         
         
         
         
    } else if (direction == 1) { // Défilement vertical
        background1->camera_pos.y += dy;
        background2->camera_pos.y += dy;

        // Limite supérieure du défilement vertical
        if (background1->camera_pos.y < 0) {
            background1->camera_pos.y = 0;
            background2->camera_pos.y = 0;
        }
        // Limite inférieure du défilement vertical
        else if (background1->camera_pos.y > (background1->image->h - SCREEN_HEIGHT)) {
            background1->camera_pos.y = background1->image->h - SCREEN_HEIGHT;
            background2->camera_pos.y = background2->image->h - SCREEN_HEIGHT;
        }
      
    }
}



