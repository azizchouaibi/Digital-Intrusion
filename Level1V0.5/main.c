
#include "perso.h"
#include "back.h"
#define jumpdistance 10


	
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
int Temps=0;
Uint32 score=0;
Uint16 gamecompt=0;
SDL_Rect PosTxt;
	SDL_Surface * SurfText;
	TTF_Font * font ;
	SDL_Color txtCoul;
SDL_Surface * es;
es = IMG_Load("/home/aziz/Desktop/Integration (copy)/es.png");
SDL_Rect poses;
poses.x=1950;
poses.y=650;
bool gameover=false;
SDL_Surface *Gameover;
			Gameover = IMG_Load("/home/aziz/Desktop/Integration (copy)/game.png");
			if ( Gameover  == NULL) {
			printf("ERROR INIT GAME OVER \n");
			SDL_Quit();
			}
int ans;
		SDL_Rect pas;
			pas.x=0;
			pas.y=0;
			pas.w=1920;
			pas.h=1080;
			

		


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
		printf("ERROR INIT SDL\n");
	}else {
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
				printf("ERROR INIT OPEN AUDIO \n");
				
}

	ecran = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
		if (ecran==NULL) {
			printf("ERROR LOADING WINDOWN\n");
		}
	
	/*backgtest=IMG_Load("back.png");
	if (backgtest == NULL) {
		printf("ERROR LOADING BACKGROUND\n");
	}*/
	TTF_Init();

	
	Background background1, background2,aux;
	
    initBackground(&background1, &background2);
	
	 player=InitPerso(player);
	font=TTF_OpenFont("/home/aziz/Desktop/Integration (copy)/FOnt.ttf",50);
		if( font == NULL) {
			printf("ERROR LOADING FONT  \n");
		}
	Mix_Music *themelvl1;
		themelvl1  = Mix_LoadMUS("/home/aziz/Desktop/Integration (copy)/Theme.mp3");
	if ( !themelvl1 ) {
		printf("ERROR LOADING MUSIC  \n");
	}
		
				Mix_PlayMusic(themelvl1,-1);
	do {


		poses.x-=15;
		if ( gameover== false){
			       	SDL_BlitSurface(background1.image,NULL, ecran, &background1.camera_pos);
			       	SDL_BlitSurface(background2.image, NULL, ecran, &background2.camera_pos);
				SDL_BlitSurface(SurfText,NULL,ecran,&PosTxt);
				SDL_BlitSurface(es,NULL,ecran,&poses);
				afficherPerso(&player, ecran);
				afficher_score(score,&PosTxt,&SurfText ,font ,txtCoul );
				}		

	
	TempsD= SDL_GetTicks();
	



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
					if ( jump == false) {
					jump=true;
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
			if ( jump==true) {

			jump=false;	
	
}
						player.textcourant=currenttext;
						player.posinit.y=ground;
			}
			
			
		}

		
		


	if ( jump) {

			if ( player.textcourant < 5 ) {
				player.textcourant=10;
				jumpPerso (&player ,1);
			}
			else {
				player.textcourant=12;
				jumpPerso (&player,-1);
		}
		}
						

		
		
   //printf("mouse X : %d mouse Y : %d ", event.motion.x , event.motion.y);
   
	}//
if (right ) {
			score+=3;

			deplacerPerso(&player,1,&currenttext);

			if (player.posinit.x >= SCREEN_WIDTH/ 2) {   
				Temps++;
				//background1.camera_pos.x-=10;
			}
			
				
				
			
		}
		if (left) {
			score-=1;
			deplacerPerso(&player,-1,&currenttext);
			
			
		}

	

	
	if (player.posinit.x >= SCREEN_WIDTH/ 2 ) {   
	    player.posinit.x= SCREEN_WIDTH/2 ;
	    
            if ( Temps % 100 ==0 && Temps != 0)  {
	aux=background1;
         background1=background2;
         background2=aux;
         background1.camera_pos.x +=500;
         printf("Camera pos : %d\n ", background1.camera_pos.x);
         
         
            	}

            	    scrolling(&background1, &background2, 0, -20, 0);	
       } if ( Temps > 2000 *2 ) {
       			Temps=0;
       	}
       	 	
       		
       if ( !jump )  {

}
       	


       


       	
        
       
        

	
	

				
				
		
		
		
           	


   		if (  ( (poses.x - 10 ) - ( player.posinit.x + 10 ) ) == 0 ) {

			player.textcourant = 14;

			score-=10;
			if ( player.num_hearts != 0) {
			player.num_hearts--;
			
}
printf("num h : %d\n " ,player.num_hearts);


			} 
	if ( player.num_hearts < 1 ) {
	player.num_hearts=1;
	poses.x+=10;
	printf("Game Over\n");
	gameover=true;

		}

				

if ( poses.x == 0) {
	poses.x = 1600;
}
			
			
		//gestion fin du jeu 
		if (gameover==true) {
				SDL_Delay(1000);
				SDL_BlitSurface(Gameover,NULL,ecran,&pas);
				if ( event.motion.
				
		}
		
			
				
			
		
		

		
	

		
	
	
				
	TempsF=SDL_GetTicks();
	score = score <= 0 ? 1 : score;
	
			

			
	}while(quitter!=1);
	
	
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(backgtest);
	int j;
	for( j=0 ; j < 14 ; j++) {
		SDL_FreeSurface(player.texture[j]);
		}
	SDL_FreeSurface(background1.image);
	SDL_FreeSurface(background2.image);
	SDL_FreeSurface(es);
	SDL_FreeSurface(Gameover);
	Mix_FreeMusic(themelvl1);
	Mix_CloseAudio();
	
	
	
	}
return 0;
}
	
		
	
