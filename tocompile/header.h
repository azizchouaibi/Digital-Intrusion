#ifndef FONCTIONS_H_
#define FONCTIONS_H_
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>
#include <SDL/SDL_ttf.h>


typedef struct {
	SDL_Surface *text;
	SDL_Rect pos;
	SDL_Color color;
	TTF_Font *font;
}Text;

typedef struct {
	SDL_Surface img[3];
	SDL_Rect pos;
	int lvl;
	Mix_Music *music;
}backg;

typedef struct {
	SDL_Surface * img[2];
	SDL_Rect pos;
}Button;

typedef struct {
	SDL_Surface img[10];
	SDL_Rect pos;
	int i;
}animation;
typedef	struct 
{
	char username[256];
	char password[256];
	char pfp_path[256];
	SDL_Surface * pfp;
	int score;
}user;

enum State {
    PLAYING,
    OPTIONSMENU,
    PROFILESMENU,
    MAINMENU,
};
enum ControllerPlayerCommands {
    SHOOT,
    JUMP,
    SLIDE,
    NOJUMP,
    NOSLIDE,
    NONE,
};
void dimenstionsBTN(SDL_Rect *btn1,SDL_Rect *btn2,SDL_Rect* btn3,SDL_Rect *btn4, SDL_Surface *btnclick0);
void loadbtns(SDL_Surface **play0, SDL_Surface **play1 , SDL_Surface **opts0, SDL_Surface **opts1, SDL_Surface **credit0, SDL_Surface **credit1, SDL_Surface **quit0 , SDL_Surface **quit1);
bool sourisSurbtn(SDL_Rect btn, SDL_Event event);
void changetexture(SDL_Rect btn1, SDL_Rect btn2, SDL_Rect btn3, SDL_Rect btn4 , SDL_Event event, 
SDL_Surface * play0,
SDL_Surface * play1,
SDL_Surface * opts0,
SDL_Surface * opts1,
SDL_Surface * credit0,
SDL_Surface * credit1,
SDL_Surface * quit0,
SDL_Surface * quit1,
 SDL_Surface *ecran); 

void loadlevel1(SDL_Surface *lvlback , SDL_Surface *ecran , SDL_Rect posback ) ;
SDL_Surface ** initAnimBack() ;

Button* slider();
void loadtext (char text[] , char cheminfont[], int taille , int indcouleur, int x , int y , SDL_Surface *ecran);
Button* loadoptions(SDL_Surface *ecran, SDL_Surface *backg, SDL_Rect posopt); // 1 red , 2 green , 3 blue , 0 white , -1 black 
//void loadoptions(SDL_Surface *ecran,  SDL_Surface * backg, SDL_Rect posopt) ;
//void hover(SDL_Rect posbtn, char chemin1[100] , char chemin0[100], SDL_Event event,SDL_Surface *ecran);
bool backspace(SDL_Event );
bool sauvegarde_score(Uint32 score,const char *filename);
int best_score(const char *filename);
void show_high_score(SDL_Surface * ecran);

#endif
