#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "enigme.h"

void initexte(text *A) {
    A->position.x = 610;
    A->position.y = 30;
    A->textColor.r = 255;
    A->textColor.g = 255;
    A->textColor.b = 255;

    A->font = TTF_OpenFont("fonts/police.ttf", 20);
}


void init_enigme(enigme *e) {
    int i = 1;
    char nomimage[20];

    e->p.x = 360;
    e->p.y = 140;
    e->img = NULL;

    // Exemple de génération d'un numéro aléatoire pour l'énigme
    generate_afficher(&e->num_enigme);

    // Charger l'image de l'énigme depuis un fichier
    FILE *f = fopen("enigme.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %d\n", nomimage, &e->reponsevrai) != EOF && i != e->num_enigme) {
            i++;
        }
        e->img = IMG_Load(nomimage);
        fclose(f);
    } else {
        printf("ERROR loading file\n");
    }
}
// Afficher le résultat (win ou lose) avec un délai de 5 secondes
void afficher_resultat(SDL_Surface *screen, int s, int r, enigme *en) {
    if (r == s) {
        en->res = IMG_Load("img/win.jpg");
    } else {
        en->res = IMG_Load("img/lose.jpg");
    }

    SDL_BlitSurface(en->res, NULL, screen, &(en->p));
    SDL_Flip(screen);

    // Délai de 5 secondes
    //SDL_Delay(3000); // Attendre 5 secondes
    //SDL_FreeSurface(en->img);
}
void generate_afficher(int *alea) {
    int test = *alea; // Variable temporaire
    srand(SDL_GetTicks()); // Initialiser le générateur de nombres aléatoires avec SDL_GetTicks

    do {
        *alea = 1 + rand() % 12; // Générer un nombre entre 1 et 12
    } while (*alea == test); // S'assurer qu'il n'est pas le même que le précédent
}

// Boucle de jeu avec sortie après délai
int enigme_play(SDL_Surface* screen) {
    enigme e;
    e.num_enigme = -1;
    int r = 0;
    int running = 1; // Le jeu est initialement en cours d'exécution
    int boucle = 1; // Boucle principale du jeu
    char cc[30] = "0";
    text tt;

    init_enigme(&e);
    initexte(&tt);

   while (boucle) {
        SDL_BlitSurface(e.img, NULL, screen, &e.p);
        SDL_Flip(screen);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                boucle = 0; // Quitter la boucle
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    boucle = 0; // Quitter la boucle sur ESC
                    break;
                }
                
                switch (event.key.keysym.sym) {
                case SDLK_a:
                    r = 1;
                    running = 0; // Indiquer que le jeu doit arrêter après résultat
                    break;
                case SDLK_z:
                    r = 2;
                    running = 0;
                    break;
                case SDLK_e:
                    r = 3;
                    running = 0;
                    break;
                case SDLK_r:
                    r = 4;
                    running = 0;
                    break;
                default:
                    break;
                }
            }
        }

        if (running == 0) {
            // Afficher le résultat et quitter après 5 secondes
            afficher_resultat(screen, e.reponsevrai, r, &e);
            boucle = 0; // Quitter la boucle après affichage
        }
    }
	
    
    if (r == e.reponsevrai) {
        return 1; // Bonne réponse
    } else {
        return 0; // Mauvaise réponse
    }
    
    
     SDL_FreeSurface(e.img);
    for (int i = 0; i < 10; i++) {
        SDL_FreeSurface(e.timer[i]);
    }
    SDL_FreeSurface(tt.surfaceTexte);
}


