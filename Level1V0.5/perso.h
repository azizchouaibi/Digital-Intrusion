#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#include "back.h"

#define crouchdistance 10
#define ground 500

typedef struct {
	
	SDL_Rect posinit;
	SDL_Surface* texture[15];
	int textcourant;
	// proprietes 
	int num_hearts;
	SDL_Surface * vie[3];
	SDL_Rect posvie;
	double acc;
	SDL_Surface * dmg;

}Person;


Person  InitPerso(Person  player );

void afficherPerso(Person * player, SDL_Surface * ecran);
void deplacerPerso(Person * player, int direction, int *currenttext);
void animerPerso (Person * player , SDL_Surface * ecran, int *compt);
void jumpPar(Person *player);
void jumpPerso ( Person * player , int direction);
void afficher_score(int score ,  SDL_Rect * PosTxt, SDL_Surface ** SurfText , TTF_Font * font , SDL_Color txtCoul);



typedef struct {
	SDL_Rect posarr;
	SDL_Surface * back[3];
	int indback;
} Backg;






 
 

 
 	
	
