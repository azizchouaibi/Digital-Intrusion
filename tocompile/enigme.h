#ifndef ENIGME_H
#define ENIGME_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

// Structure pour le texte
typedef struct {
    SDL_Surface *surfaceTexte;
    SDL_Rect position;
    SDL_Color textColor;
    TTF_Font *font;
} text;

// Structure pour les énigmes
typedef struct {
    SDL_Surface *img;
    SDL_Surface *timer[10];
    SDL_Rect p;
    SDL_Rect pos_timer;
    int reponsevrai;
    int reponsejoueur;
    int num_enigme;
} enigme;

// Déclarations des fonctions
void initexte(text *A);  // Déclarer la fonction avec le type text
void afficher_resultat(SDL_Surface *screen, int s, int r, enigme *en);
void init_enigme(enigme *e);
void generate_afficher(int *alea);
int enigme_play(SDL_Surface* screen);

#endif // ENIGME_H

