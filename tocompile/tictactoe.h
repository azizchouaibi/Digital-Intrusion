#ifndef ENIGME_H
#define ENIGME_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>

typedef struct
{
	SDL_Surface *img[14];
	int p;
	int nbr;
	SDL_Rect pos;
}background;
typedef struct
{
	SDL_Surface*img[2];
	int j;
	SDL_Rect pos[3][3];
	int tab [3][3];
	int select ;
	int nbr;
}tic_tac_toe;
typedef struct
{	TTF_Font *police;
	char ch[200];
	SDL_Color color;
	SDL_Rect pos;
	SDL_Surface *txt;
} texte;
typedef struct
{
	SDL_Surface *zoom[10];
	SDL_Surface *rotation[10];
	texte goodluck;
	texte hardluck;
	int j;
	int i;
	
}rotozoom;


void initTictactoe (tic_tac_toe *t) ;
void afficherTictactoe (SDL_Surface *screen , tic_tac_toe t);
void afficherTictactoeclavier (SDL_Surface *screen , tic_tac_toe t);
int atilganger(int tab[3][3]);





void initialiser_back(background *back);
void afficher_back(SDL_Surface *screen , background back);
void annimer_back(background *back);

void initialiser_texteGood(texte* good);
void initialiser_textHardLuck(texte* HardLuck);
void initialiser_rotozoom(rotozoom *z);
void afficher_rotozoom(SDL_Surface *screen , rotozoom z);

void joueur2(int tab[3][3]);
void rejouer(tic_tac_toe *t);
#endif
