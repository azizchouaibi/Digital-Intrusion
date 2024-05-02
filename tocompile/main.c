#include "perso.h"
#include "header.h"
#include "tictactoe.h"
#include "enigme.h"

#define SCREEN_WIDTH 1920
#define DAMAGE_COOLDOWN 2// 2 second


int main(){
//VARIABLES GLOABLES
time_t lastDamageTime = 0; 
SDL_Event event;
bool mainmenu=true;
bool optionmenu=false;
bool gameloop=true;
SDL_Surface *ecran=NULL;
SDL_Surface *imgmenu=NULL,*play0=NULL,*play1=NULL,*opts0=NULL,*opts1=NULL,*credit0=NULL,*credit1=NULL,*quit0=NULL,*quit1=NULL,*lvlback=NULL,*ecranf,*ecranwin;
SDL_Rect posimg,poslvl1;
Mix_Music *musicmenu;
Mix_Chunk *click,*jumpSFX,*gameOverSFX,*dmgSFX,*CoinSFX;
SDL_Rect play,opts,creds,quit;
SDL_Surface *backg=NULL;
SDL_Rect posopt;
Button *btn;
Button *tabs;
SDL_Rect posSlider;
bool MsClick=false;
bool sfClick=false;
int compt=100;
SDL_Surface *lamp1=NULL,*lamp2=NULL;
SDL_Rect poslmp;
bool playb=false;
bool lvl1=false;
SDL_Surface ** tab;
bool lst =true;
//bool enigmelvl1=false;
bool playS=false;
int indnv = 0 ;
//////NEXT LEVEL ANIMATION // 
SDL_Surface * Loading[3];
Mix_Chunk *  nxtlvlSFX=NULL;


//INTILIAZATION ET CREATION DU FENETRE + AFFICHAGE D'IMAGE MENU + Chargement de music 


if (SDL_Init(SDL_INIT_EVERYTHING) !=0 ) {
	printf("ERROR INITIALIZING SDL\n");
	SDL_Quit();
} else {	
	
	ecran = SDL_SetVideoMode(1920,1080,32, /*SDL_FULLSCREEN|*/ SDL_HWSURFACE| SDL_DOUBLEBUF);
	if (ecran== NULL) {
		printf("ERROR CREATING WINDOW");
	}
	//LES BOUTONS :

	loadbtns(&play0,&play1,&opts0,&opts1,&credit0,&credit1,&quit0,&quit1);
	
	
				//L'IMAGE MENU
	
	imgmenu = IMG_Load("nvack.png");
	if (imgmenu==NULL) {
		printf("ERROR OPENING MENU IMAGE");
		SDL_FreeSurface(ecran);
		SDL_Quit();
	}
	else {
	posimg.x=0;
	posimg.y=0;
	posimg.h=imgmenu->h;
	posimg.w=imgmenu->w;
	dimenstionsBTN(&play,&opts,&creds,&quit,play0);
}
	
	Mix_OpenAudio(48000,MIX_DEFAULT_FORMAT,2,4096);
        musicmenu=Mix_LoadMUS("r&m.mp3");
        if (musicmenu ==NULL) {
	printf("ERROR OPENING MUSIC \n");
}
	click=Mix_LoadWAV("click.wav");
	if ( click==NULL) {
	printf("ERROR LOADING CLICK SOUND\n");
}
	jumpSFX=Mix_LoadWAV("jumpSFX.wav");
	if ( !jumpSFX) {
		printf("ERROR LOADING JUMP SFX \n");
	}
	gameOverSFX=Mix_LoadWAV("GAMEOVERSFX.wav");
	if ( !gameOverSFX) {
		printf("ERROR LOADING GAMEOVER SFX \n");
	}
	dmgSFX=Mix_LoadWAV("dmgSFX.wav");
	if ( !dmgSFX) {
		printf("ERROR LOADING DAMAGE SFX \n");
	}
	CoinSFX = Mix_LoadWAV("coinSFX.wav");
	if ( !CoinSFX) {
			printf("ERROR LOADING COIN SFX\n");
		}
	
	
}
if (TTF_Init() !=0 ) {
	printf("ERROR LOADING TTF ");
}

	backg=IMG_Load("ts_opt/op1.png");





tab =  initAnimBack();

btn=loadoptions(ecran,backg,posopt);
tabs=slider();
posSlider.x=621;
			 posSlider.y=718;
			 posSlider.w=200;
			 posSlider.h=200;
			 
SDL_BlitSurface(imgmenu, NULL, ecran, &posimg);
SDL_Rect test;
test.x=492;
test.y=834;
test.h=87;
test.w=379;

poslmp.x=1600;
poslmp.y=100;

//Mix_PlayMusic(musicmenu,-1);
Mix_VolumeMusic(90);
int j;
SDL_Surface *seleclevel= IMG_Load("lvlselec.png");
if ( !seleclevel) {
	printf("ERROR LOADING SELEC LEVEL \n");
	}
	//VARIABLE POUR TIC TAC TOE 
tic_tac_toe t;
	rotozoom z;
	background back;
	srand(time(NULL));

bool ttc=false;
						int boucle=0;

initTictactoe(&t);
	initialiser_back(&back);
	initialiser_rotozoom(&z);
bool tcc_won=false;





/////////
//VARIABLE DE LEVEL 1 : 
SDL_Rect PosTxt;
	SDL_Surface * SurfText;
	TTF_Font * font ;
	SDL_Color txtCoul;
/*SDL_Surface * es;
es = IMG_Load("Red_rectangle(1).png");
SDL_Rect poses;
poses.x=1950;
poses.y=650;*/
bool gameover=false;
SDL_Surface *Gameover;
			Gameover = IMG_Load("game.png");
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


Uint32 score=0;


		SDL_Surface * ES=NULL,*Coin=NULL;
		SDL_Rect poses,posCoin;
		if ( InitES(&ES,&Coin, "enemy.png", "coin.png", &poses ,&posCoin) == 0) {
			printf("ERROR LOADING ES AND COINS\n");
			SDL_Quit();
		}


	int indlvl;
Background TabBack[3];

    initBackground(&TabBack[0], ecran,"lvl1img1.png","lvl1img2.png"); // back lvl1
    bool Playing=false;

		initBackground(&TabBack[1], ecran,"lvl2img1.png","lvl2img2.png"); // back lvl 2
		initBackground(&TabBack[2], ecran,"lvl3img1.png","lvl3img2.png"); // back lvl3
    

Person player;
	 player=InitPerso(player);


font=TTF_OpenFont("FOnt.ttf",50);
		if( font == NULL) {
			printf("ERROR LOADING FONT  \n");
		}
	Mix_Music *themelvl1;
		themelvl1  = Mix_LoadMUS("Theme.mp3");
	if ( !themelvl1 ) {
		printf("ERROR LOADING MUSIC  \n");
	}
		

						Mix_PlayMusic(musicmenu,-1);
int Temps=0;
bool jump=false;
bool right=false,left=false;
int quitter=0;
int i,currenttext;

	
	SDL_Rect YesGO ;
YesGO.x=578;
YesGO.y=936;
YesGO.w=578+243;
YesGO.h=936+72;
SDL_Rect NOGO;
NOGO.x=1198;
NOGO.y=933;
NOGO.w=1198+182;
NOGO.h=925+83;
SDL_Surface * surft;
// FIN VARIABLE LEVEL 1
while (gameloop) {

if (mainmenu ) {
optionmenu=false;
playS=false;
gameover=false;

SDL_BlitSurface(imgmenu, NULL, ecran, &posimg);
show_high_score(imgmenu,surft);

	









			changetexture(play,opts,creds,quit , event, 
play0,
play1,
opts0,
opts1,
credit0,
credit1,
quit0,
quit1,
ecran); 

//loadtext ("YUMATECH", "CFGlitchCity-Regular.ttf", 50 , 0, 962 , 107 , ecran);



if ( event.motion.x >=  0 && event.motion.x <= 640 )  {
	SDL_BlitSurface(tab[0],NULL,ecran,&poslmp);
}  if ( event.motion.x >=  640 && event.motion.x <= 1280) {
	SDL_BlitSurface(tab[1],NULL,ecran,&poslmp);
}if ( event.motion.x >=  1280 && event.motion.x <= 1920) {
	SDL_BlitSurface(tab[2],NULL,ecran,&poslmp);
}

}





//MISE A JOUR LEL ECRAN (necessaire) 
SDL_Flip(ecran);
//LA MUSIQUE W FAZET

			




//LECTURE DE CLAVIER :
	while (SDL_PollEvent(&event)!=0) {
		
		
		switch(event.type) {	
			case SDL_KEYDOWN:
			switch(event.key.keysym.sym) {
				case SDLK_ESCAPE:
				printf("EXITING...\n");
				gameloop=false; 

				break;
				case SDLK_h:
				printf("HELP REQUESTED\n");
				break;
				case SDLK_BACKSPACE:
				mainmenu=true;
				break;
				case SDLK_o:
				mainmenu=false;
				optionmenu=true;
				break;
				case SDLK_p:
				mainmenu=false;
				playS=true;
				break;
				
			}
				break;	
			

			case SDL_MOUSEBUTTONDOWN:
			if ( mainmenu) {
/*play*/		if ( sourisSurbtn(play,event)&& event.button.button==SDL_BUTTON_LEFT ) {
					if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }
					mainmenu=false;
					playS=true;
					printf("TEST SUR CLICK  PASSE \n");
				}
/*options*/		else 
                        if(sourisSurbtn(opts,event) && event.button.button==SDL_BUTTON_LEFT ){
					if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }
					printf("Options\n");
					mainmenu=false;
					optionmenu=true;

					printf("ok 3\n");


				}
/*credits*/		else if (sourisSurbtn(creds,event) && event.button.button==SDL_BUTTON_LEFT ){
					if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }		
					printf("Credits\n");

					
				}
/*quitter*/		else if(sourisSurbtn(quit,event) && event.button.button==SDL_BUTTON_LEFT ){
	
					if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }		
					SDL_FreeSurface(ecran);
					SDL_FreeSurface(imgmenu);
					Mix_FreeMusic(musicmenu);
					Mix_CloseAudio();
					SDL_Delay(10);
					SDL_Quit();
					gameloop=false;
					printf("Quit\n");
				}
				
				
				
}
	else if ( optionmenu ) { 
			
			if (sourisSurbtn(btn[0].pos,event) && event.button.button==SDL_BUTTON_LEFT) { // music on walla off
							printf("Test 1 \n");
						MsClick=!MsClick;						
						Mix_VolumeMusic(0);
			   	} 
			if (sourisSurbtn(btn[1].pos,event) && event.button.button==SDL_BUTTON_LEFT ) { // sfx on walla off

						sfClick=!sfClick;
						Mix_HaltChannel(-1);
						
			   		
			   	}
			   if(sourisSurbtn(btn[4].pos,event) &&event.button.button==SDL_BUTTON_LEFT ) {
			   if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }
			   		printf("FULLSCREEN \n");
					ecranf = SDL_SetVideoMode(1920,1080,32, SDL_FULLSCREEN |  SDL_HWSURFACE| SDL_DOUBLEBUF);
					ecran=ecranf;
				}
				
			   if (sourisSurbtn(btn[5].pos,event) &&  event.button.button==SDL_BUTTON_LEFT) {
			   if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }
			   		printf("WINDOWED MODE \n");
			   		ecranwin= SDL_SetVideoMode(1920,1080,32, SDL_HWSURFACE| SDL_DOUBLEBUF);
			   		ecran=ecranwin;	
			   		}
			if( (event.motion.x >= 1335 && event.motion.x <= 1335+80 && event.motion.y >=713 && event.motion.y <= 713 + 80 ) && (event.button.button==SDL_BUTTON_LEFT) ) { 
				if ( compt <100 && compt>=0) {
				compt+=25;
				}
				
			 }
			   if( (event.motion.x >= 591 && event.motion.x <= 591+60 && event.motion.y >=600 && event.motion.y <= 713 + 80 ) &&  event.button.button==SDL_BUTTON_LEFT ) {



			 	if ( compt > 0  && compt <= 100) {
			 	compt-=25;
			 	}
			 	
			 	}	
			   	
			


}


 
	}

								
				
			

}//END OF POLL EVENT 


if (optionmenu==true ){

				
		        SDL_BlitSurface(backg, NULL, ecran, &posopt);
		        if ( MsClick == false) {
			SDL_BlitSurface(btn[0].img[0],NULL,backg,&btn[0].pos);
			Mix_VolumeMusic(90);
			}else 
			if ( MsClick == true) {				
			SDL_BlitSurface(btn[0].img[1],NULL,backg,&btn[0].pos);
			}
			if (sfClick==false) {
			SDL_BlitSurface(btn[1].img[0],NULL,backg,&btn[1].pos);
			}else if (sfClick==true) {
			SDL_BlitSurface(btn[1].img[1],NULL,backg,&btn[1].pos);
			}
			if(sourisSurbtn(btn[4].pos,event)) {	
		   	SDL_BlitSurface(btn[4].img[1],NULL,backg,&btn[4].pos); // fullscreen	   	
			   } else {
			   	SDL_BlitSurface(btn[4].img[0],NULL,backg,&btn[4].pos);
			}
			  if(sourisSurbtn(btn[5].pos,event)) { //windowd
			   	SDL_BlitSurface(btn[5].img[1],NULL,ecran,&btn[5].pos);
			   } else {
			   SDL_BlitSurface(btn[5].img[0],NULL,backg,&btn[5].pos);
			  }
			  

			 

			 if (MsClick == false) {
			 switch(compt) {
			 case 0:
			SDL_BlitSurface(tabs[0].img[0],NULL,backg,&posSlider);
			Mix_VolumeMusic(15);
			 break;
			 case 25:
			SDL_BlitSurface(tabs[1].img[0],NULL,backg,&posSlider);
			Mix_VolumeMusic(25);
			 break;
			 case 50 :
			SDL_BlitSurface(tabs[2].img[0],NULL,backg,&posSlider);
			Mix_VolumeMusic(50);
			 break;
			 case 100:
			SDL_BlitSurface(tabs[3].img[0],NULL,backg,&posSlider);
			Mix_VolumeMusic(100);
			 break;
			 
			if ( compt>100) {
				compt =100;
			}else
			if (compt <0) {
				compt=0;
				}

				
			 }
			 
}
}	
		


			if ( playS ) {	

					SDL_BlitSurface(seleclevel,NULL,ecran,&posimg);
					while ( SDL_PollEvent(&event)){
						switch(event.type) {
							case SDL_KEYDOWN:
								switch(event.key.keysym.sym) {
									case SDLK_KP1:
										indlvl=1;
										Playing=true;
										playS=false;										
										break;
									case SDLK_KP2:
										indlvl=2;
										Playing=true;
										playS=false;	
										break;
									case SDLK_KP3:
										indlvl=3;
										Playing=true;
										playS=false;	
									break;
									case SDLK_BACKSPACE:
										
										mainmenu=true;
										playS=false;
										Playing=false;
									break;
									case SDLK_ESCAPE:
									quitter=1;
									
									
								}
							}
							}
						}
						
					if (Playing) {
					Mix_PlayMusic(themelvl1,-1);
						
				do {
				deplacerES(&posCoin,&poses);
		
				if ( gameover== false){

	       if (TabBack[indlvl-1].showing_main_image) {
            SDL_BlitSurface(TabBack[indlvl-1].image, &TabBack[indlvl-1].camera_pos, ecran, NULL);
        } else {
            SDL_BlitSurface(TabBack[indlvl-1].secondary_image, &TabBack[indlvl-1].camera_pos, ecran, NULL);
        }
        				updateBackgroundImage(&TabBack[indlvl-1]);
				SDL_BlitSurface(SurfText,NULL,ecran,&PosTxt);
				afficherES(ecran,ES,Coin,poses,posCoin);
				afficherPerso(&player, ecran);
				afficher_score(score,&PosTxt,&SurfText ,font ,txtCoul );

				}		
				
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
					
					case SDLK_ESCAPE:
						if ( Playing == true) {
					Playing=false;
					mainmenu=true;
					Mix_PlayMusic(musicmenu,-1);

					}
					
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
		if ( sfClick == false ) {Mix_PlayChannel(4,jumpSFX,0); }

			if ( player.textcourant < 5 ) {
				player.textcourant=10;
				jumpPerso (&player ,1);
			}
			else {
				player.textcourant=12;
				jumpPerso (&player,-1);
		}
		}
			
			
				
				
				
				
				
				
				
	}//END OF POLL EVENT LOOP

	
	//GESTIN MOVEMENT ET SCROLLING BACKGROUND
				if (right ) {
				
			score+=3;
			deplacerPerso(&player,1,&currenttext);

			
		}
		
		if (left) {
			score-=1;
			deplacerPerso(&player,-1,&currenttext);
			}
	if (player.posinit.x >= SCREEN_WIDTH/ 4 ) {   
	   player.posinit.x= SCREEN_WIDTH/4 ;   
       scrollingHorizontal(&TabBack[indlvl-1], 7);			
       	}
       	
			 /////////////////////////////////////////////      
       		
       		
       		
		 //GESTION COLLISON ET DOMMAGE///////////////////////////
		
		 
		 
		 
			time_t currentTime = time(NULL);
       if (currentTime - lastDamageTime >= DAMAGE_COOLDOWN) {
            int collisionType = Collided(player, poses);
            switch (collisionType) {
                case 1:

                    if (sfClick == false) {
                        Mix_PlayChannel(-1, dmgSFX, 0);
                    }

                    player.textcourant = 14;
                    score -= 10;
                    if (player.num_hearts != 0) {
                        player.num_hearts--;
                    }
                    lastDamageTime = currentTime;
                    break;
                case 2:
                    poses.x = 1920;
                    break;
                default:

                    break;
            }
        }
        
        HandleCollision_Player_Bonus(&player,&posCoin,&score,CoinSFX);
			
	if ( player.num_hearts < 1 ) {
	player.num_hearts=1;
	poses.x+=10;

	printf("Game Over\n");
	gameover=true;

		}
				
				
			

		///////////////////////////////////////////////////
		
		
if (gameover==true) {
							if ( sfClick == false  && lst ) {Mix_PlayChannel(-1,gameOverSFX,0); lst = false;}
				Mix_HaltMusic();
				SDL_BlitSurface(Gameover,NULL,ecran,&pas);
										poses.x=1600;
					switch(event.type){
					case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
					case SDLK_y:
						lst=true;
						Mix_ResumeMusic();		
						Mix_PlayMusic(themelvl1,-1);
						printf("YES \n");
						poses.x=1600;
						player.posinit.x = 100;
						player.num_hearts=3;

						score=0;
						lvl1=true;
						gameover=false;
					break;						
					case SDLK_n:		
						Playing=false;
						playS=false;
						gameover=false;
						mainmenu=true;

						Mix_PlayMusic(musicmenu,-1);
					break;
					}
				break;
		}
}


	if ( indlvl==1 && ( score >  400 && score < 550)) { //GESTION TIC TAC TOE
							ttc=true;

					do {
						afficher_back(ecran , back);
						afficherTictactoe(ecran , t);
						afficherTictactoeclavier(ecran , t);
						SDL_Flip(ecran);
						while(SDL_PollEvent(&event))
		{ // 
			switch(event.type)
			{
			case SDL_MOUSEMOTION:
			{
				for(int i=0 ; i< 3 ; i++)
				{
					for(int j=0 ; j < 3 ; j++)
					{
						if(event.motion.x>t.pos[i][j].x && event.motion.x < t.pos[i][j].x + t.pos[i][j].w
						&& event.motion.y>t.pos[i][j].y && event.motion.y < t.pos[i][j].y + t.pos[i][j].h)
						{
							t.select=(i*3) + j;
						}
					}
				}
				break;
			}
			case SDL_MOUSEBUTTONUP:
				for(int i=0 ; i< 3 ; i++)
				{
					for(int j=0 ; j < 3 ; j++)
					{
						if(event.motion.x>t.pos[i][j].x && event.motion.x < t.pos[i][j].x + t.pos[i][j].w
						&& event.motion.y>t.pos[i][j].y && event.motion.y < t.pos[i][j].y + t.pos[i][j].h)
						{	
							if(t.tab[i][j] == 0)
							{
								if(t.j==0)
								{
									t.tab[i][j]=1;
									t.j=1;
									for(int i=0;i<3;i++)
									{
										for(int j=0 ; j<3;j++)
										{
											printf("%d\t" , t.tab[i][j]);
										}
										printf("\n");
									}
									printf("\n");
								}
								else 
								{
									t.tab[i][j]=2;
									t.j=0;

								}
								if (atilganger(t.tab)  !=0 ) {
									 tcc_won=true;
										ttc=false;
										score+=700;
										
									}
									
							}
							
						}
					}
				}
				break;
				
				
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_RIGHT)
				{
					t.select++;
					if(t.select == 9)
					{
						t.select = 0;
					}
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					t.select -- ;
					if(t.select<=-1)
					{
						t.select=8;
					}
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					t.select +=3 ;
					if(t.select>8)
					{
						t.select-=9;
					}
				}
				else if (event.key.keysym.sym == SDLK_UP)
				{
					t.select -=3 ;
					if(t.select<0)
					{
						t.select+=9;
					}
				}
				else if(event.key.keysym.sym == SDLK_RETURN)
				{
					if(0<=t.select && t.select<=2)
					{
						if(t.tab[0][t.select] == 0)
						{
							t.tab[0][t.select]=t.j+1;
							if(t.j==1) t.j=0;
							else t.j=1;
							
						}
					}
					else if (3<=t.select && t.select<=5)
					{
						if(t.tab[1][t.select - 3] == 0)
						{
							t.tab[1][t.select-3]=t.j+1;
							if(t.j==1) t.j=0;
							else t.j=1;
						}
					}
					else 
					{
						if(t.tab[2][t.select-6] == 0)
						{
							t.tab[2][t.select-6]=t.j+1;
							if(t.j==1) t.j=0;
							else t.j=1;
						}
					}
				}
				break;
			}
		}

				
/****ANNIMATION*****/
		annimer_back(&back);
							
					}while(ttc);
					
						if ( tcc_won) {
					Playing=false;
										Pass_to_Next_Level(Loading, ecran, &nxtlvlSFX,&player,TabBack , indlvl);
										playS=true;
					
				}
					}
					
					
					
				/*if ( indlvl==2 && ( autre condition )) {
				}*/
				
				
				if ( indlvl==3 && ( score > 300 && score < 450)) {
							     if ( enigme_play(ecran) == 0 ) { // mauvaise reponse
													gameover = true;
													score += 500;
																				
				} else {
																			Pass_to_Next_Level(Loading, ecran, &nxtlvlSFX,&player,TabBack , indlvl);
																			mainmenu=true;
					}
					
				
				
				}
				
				
				
   
	
	
	
	
	
	
	
	
	
	
	
	
	
		




}while(Playing == true);
			}
			
			
			 // FIN LEVEL 1 //////////////////////////////////////////
				//}//FIN PLAY
			
			} // FIN gameloop;
			
			
			//SAUVEGARDE DU SCORE
			
			if ( sauvegarde_score(score,"score.txt") == false ) {
				printf("ERROR SAVING SCORE \n");
			} else {
				printf("SCORE SAVED \n");
			}
			//HIGHEST_SCORE
			
			Uint32	highest_score;
			highest_score=best_score("score.txt");
			if ( best_score == 0 ) {
					printf("ERROR LOADING HIGHEST SCORE \n");
			}else {
				printf("HIGHEST SCORE : %u \n",highest_score);
			}
			
			
				
			
			
			
		//LIBERATION 

	for( int p=0 ; p < 14 ; p++) {
		SDL_FreeSurface(player.texture[p]);
		}
		for ( int s=0 ; s < 3 ; s++) {
			SDL_FreeSurface(TabBack[indlvl-1].image);
			SDL_FreeSurface(TabBack[indlvl-1].secondary_image);
		}
		  for (int i = 0; i < 3; i++) {
        SDL_FreeSurface(Loading[i]);
    }
    for (int i = 0; i < 14; i++) {
        SDL_FreeSurface(back.img[i]);
    }


    for (int i = 0; i < 2; i++) {
        SDL_FreeSurface(t.img[i]);
    }




    for (int i = 0; i < 10; i++) {
        SDL_FreeSurface(z.zoom[i]);
        SDL_FreeSurface(z.rotation[i]);
    }
    
 for (int i = 0; i < 3; i++) {
        if (Loading[i]) {
            SDL_FreeSurface(Loading[i]);
            Loading[i] = NULL;
        }
    }



    

	SDL_FreeSurface(Gameover);


    SDL_FreeSurface(ecran);
    SDL_FreeSurface(imgmenu);
    SDL_FreeSurface(backg);
    SDL_FreeSurface(lamp1);
    SDL_FreeSurface(lamp2);
    SDL_FreeSurface(seleclevel);
    SDL_FreeSurface(Gameover);
    SDL_FreeSurface(ES);
		SDL_FreeSurface(surft);
		
    Mix_FreeMusic(musicmenu);
    Mix_FreeMusic(themelvl1);
    Mix_FreeChunk(click);
    Mix_FreeChunk(jumpSFX);
    Mix_FreeChunk(gameOverSFX);
    Mix_FreeChunk(dmgSFX);
     Mix_FreeChunk(nxtlvlSFX);
		 Mix_FreeChunk(nxtlvlSFX);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    
    
return 0;
}




	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


