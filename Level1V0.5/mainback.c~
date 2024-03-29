#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "back.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if (!screen) {
        printf("Failed to create window! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    Background background1, background2;
    initBackground(&background1, &background2);
	
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *music = Mix_LoadMUS("music.mp3");
    if (!music) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        SDL_Quit();
        return -1;
    }
    Mix_PlayMusic(music, -1);

    int quit = 0;
    SDL_Event event;

    // Position du joueur (à adapter)
    SDL_Rect player_pos = {50, 300, 32, 32};
    
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        const Uint8 *keystate = SDL_GetKeyState(NULL);

        // Vérification si le joueur dépasse la moitié du background 1
        if (player_pos.x >= SCREEN_WIDTH / 2) {
          
            scrolling(&background1, &background2, 0, -SCROLL_SPEED_X, 0);
        }

        if (keystate[SDLK_LEFT]) {
            // Déplacer le joueur vers la gauche (à adapter)
            player_pos.x -= SCROLL_SPEED_X;
        } else if (keystate[SDLK_RIGHT]) {
            // Déplacer le joueur vers la droite (à adapter)
            player_pos.x += SCROLL_SPEED_X;
        } else if (keystate[SDLK_UP]) {
            scrolling(&background1, &background2, 1, 0, -SCROLL_SPEED_Y);
        } else if (keystate[SDLK_DOWN]) {
            scrolling(&background1, &background2, 1, 0, SCROLL_SPEED_Y);
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        // Dessiner les fonds d'écran
      
	
        // Dessiner le joueur (à adapter)
        SDL_FillRect(screen, &player_pos, SDL_MapRGB(screen->format, 255, 255, 255));

        SDL_Flip(screen);

        SDL_Delay(10);
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_FreeSurface(background1.image);
    SDL_FreeSurface(background2.image);
    SDL_Quit();

    return 0;
}

