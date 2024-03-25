
#include "header.h"
#define jumpdistance 10
#define crouchdistance 10

	
int main() {

SDL_Surface *ecran;
SDL_Surface *backgtest;
SDL_Rect posback,posp;
int image;
Backg Back;
Person player;
int quitter=0;
SDL_Event event;
bool jump=false;
bool right=false,left=false;
int *compt;
int i,currenttext;
Uint32 TempsD,TempsCour,TempsF;


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
		printf("ERROR INIT SDL\n");
	}else {
	ecran = SDL_SetVideoMode(600,400,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
		if (ecran==NULL) {
			printf("ERROR LOADING WINDOWN\n");
		}
	
	backgtest=IMG_Load("back.png");
	if (backgtest == NULL) {
		printf("ERROR LOADING BACKGROUND\n");
	}
	
	Back=initBack(Back);
	 player=InitPerso(player);


	do {
	TempsD= SDL_GetTicks();
	
	SDL_BlitSurface(Back.back[Back.indback],NULL,ecran,&Back.posarr);
	afficherPerso(&player, ecran);

	SDL_Flip(ecran);

	
	
	while(SDL_PollEvent(&event)) {
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_RIGHT:
					right = true;

					break;
					case SDLK_LEFT:
					left=true;

					break;
					//case SDLK_UP:
					//player.posinit.y--;
					//break;
					//case SDLK_DOWN:
					//player.posinit.y++;
					//break;
					case SDLK_ESCAPE:
					quitter=1;
					break;
					case SDLK_c:
					player.posinit.y+=crouchdistance;
					break;
					case SDLK_SPACE:
					if ( player.jump == false) {
					player.jump=true;
					player.vt=vitesse_init;
					}
					
					break;
					
				}
			break;
		case SDL_KEYUP:
			switch(event.key.keysym.sym) {
			case SDLK_RIGHT:
			right=false;
			break;
			case SDLK_LEFT:
			left=false;
			break;
			
			case SDLK_SPACE:
			player.jump=false;	
			player.textcourant=currenttext;
			player.posinit.y=ground;
						
			}
			
			
		}

		
		
					printf(" Texure courante : %d\n", player.textcourant);
					printf("x : %d y %d ", event.motion.x , event.motion.y);			

	if ( player.jump) {
		    printf("9bal jump : texture courante : %d\n", player.textcourant); 
			if ( player.textcourant < 5 ) {
				player.textcourant=10;
				jumpPerso (&player , 1);
			}
			else {
				player.textcourant=12;
				jumpPerso (&player,-1);
		}
		}	
	}
if ( player.jump == false ) {
	if (right) {
			deplacerPerso(&player,1,&currenttext);
			


		}
		if (left) {
			deplacerPerso(&player,-1,&currenttext);
			
			
		}
		
		
	}
	
/*	
	if ( player.posinit.x >  300 ) {
		Back.indback=1;
		player.posinit.x=300;
		if ( right ) {
			Back.indback=2;
		}
		
		
	}
	
		
	*/	
		
	
	
				
	TempsF=SDL_GetTicks();
				
	}while(quitter!=1);
	
	
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(backgtest);
	SDL_FreeSurface(player.texture[0]);
	
	
	
	}
return 0;
}
	
		
	
