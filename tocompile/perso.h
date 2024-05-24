#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#include "back.h"
#include <math.h>
#define ground 500

#define SPRITE_WIDTH 34
#define SPRITE_HEIGHT 34
#define NUM_FRAMES 3
#define NUM_DIRECTIONS 4 






typedef struct {
	
	SDL_Rect posinit;
	SDL_Surface* texture[16];
	int textcourant;
	// proprietes 
	int num_hearts;
	SDL_Surface * vie[3];
	SDL_Rect posvie;
	double acc;
	SDL_Surface * dmg;
	int dx;
	int slide;
	int energy;
	bool shoot;
	int score;
	// 2 eme joueur minijeu
	SDL_Surface *sprite[NUM_DIRECTIONS][NUM_FRAMES];
	int frame;
	int direction;
	int health;
	///
	SDL_Surface *spriteSheet;
    SDL_Rect frameClips[NUM_DIRECTIONS][NUM_FRAMES];
	
}Person;


Person  InitPerso(Person  player );

void afficherPerso(Person * player, SDL_Surface * ecran);
void deplacerPerso(Person * player, int direction, int *currenttext);
void animerPerso (Person * player , SDL_Surface * ecran, int *compt);
void jumpPar(Person *player);
void jumpPerso ( Person * player , int direction);
void afficher_score(int score ,  SDL_Rect * PosTxt, SDL_Surface ** SurfText , TTF_Font * font , SDL_Color txtCoul);






//TEST POUR TACHE COLLISION

typedef struct {
		SDL_Surface * texture;
		SDL_Surface * anim[6];
		SDL_Rect pos;
		bool active;
		int dx;
		int health;
		int txt_cour;
		bool weapon;
}Entity;


int InitES(SDL_Surface **ES, SDL_Surface **Coin,  char* cheminES, char *cheminCoin, SDL_Rect *poses , SDL_Rect * posCoin);
//void afficherES(SDL_Surface *screen, SDL_Surface *ES, SDL_Surface *Coin, SDL_Rect poses_ES, SDL_Rect poses_Coin);

int Collided(SDL_Rect p , SDL_Rect poses); // 1 Player damaged , 2 Es damaged

Entity InitEntity(char* chemin,int x , int y,int dx);

 int CollisionTrigo(SDL_Rect C, Person P);

 
 	
	
