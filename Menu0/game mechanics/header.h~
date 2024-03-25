#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>
#include <time.h>

#define ground 100
#define gravity 1.5
#define vitesse_init  1.5
#define max_jump_distance 170

typedef struct {
	
	SDL_Rect posinit;
	SDL_Surface* texture[14];
	int textcourant;
	// proprietes 
	int num_hearts;
	SDL_Surface * vie[3];
	SDL_Rect posvie;
	bool jump;
	double vt;
	int acc;
	
}Person;


Person  InitPerso(Person  player );

void afficherPerso(Person * player, SDL_Surface * ecran);
void deplacerPerso(Person * player, int direction, int *currenttext);
void animerPerso (Person * player , SDL_Surface * ecran, int *compt);
void jumpPerso ( Person * player , int direction);


typedef struct {
	SDL_Rect posarr;
	SDL_Surface * back[3];
	int indback;
} Backg;


Backg initBack(Backg  Back) ;

 
 
 	
 
 	
	
