#ifndef enig_fichier_H_INCLUDED
#define enig_fichier_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct enig_fichier
{
    SDL_Surface* image_enig_fichier;
    SDL_Rect position_enig_fichier;
    int resultat;
    SDL_Surface *correct,*wrong;
    SDL_Rect position_correct,position_wrong;
SDL_Surface* timer[10]; // Assuming you need 10 images for the timer
    SDL_Rect pos_timer;
 int current_timer_index;
int correct_answer_index;
    TTF_Font *police,*police_q;
    SDL_Surface *reponse_1,*reponse_2,*reponse_3,*question;
    SDL_Rect  pos_reponse_1,pos_reponse_2,pos_reponse_3,pos_question;
    int alea;
    
};
typedef struct enig_fichier enig_fichier;

void alea_enig_fichier(enig_fichier* en,SDL_Color Color);
void init_enig_fichier( enig_fichier* en ,SDL_Color Color);
void blit_enig_fichier ( enig_fichier *en, SDL_Surface* screen);
void free_surface_enig_fichier( enig_fichier *en );
int quiz1(enig_fichier *en, SDL_Surface* screen );
int enig_fichier_avec_fichier();
Uint32 timerCallback(Uint32 interval, void *param);


#endif // enig_fichier_H_INCLUDED






/*
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
    SDL_Surface *res;
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
*/


