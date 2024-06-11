#include "perso.h"
#include "header.h"
#include "tictactoe.h"
#include "enigme.h"
#include "minimap.h"
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#define SCREEN_WIDTH 1920
#define DAMAGE_COOLDOWN 2// 2 second
#define ARDUINO_SERIAL_PORT "/dev/ttyACM0"  // notre port arduino
#define SLIDE_DURATION 1000 // Duration in milliseconds
#define JUMP_DURATION 600
int main(){
enum State gamestate;
enum ControllerPlayerCommands command;


int num_j=0;
int manette;
do {
//printf(" Joueurs ? \n");
//scanf("%d",&num_j);
printf("Manette ?\n");
scanf("%d",&manette);
}while ( manette > 1 || manette < 0 /*|| num_j > 2 || num_j < 0*/ );
   // srand(time(NULL));
				int collected=0;
				Uint32 currentTime_P1=0;
				Uint32 currentTime_P2=0;
				bool startMPtimer=false;
				int chose_MP=0;
printf("=========STARTED=========\n");
Uint32 jumpStartTime = 0;
Uint32 slideStartTime = 0;
bool sliding = false;
bool jumping=false;
//VARIABLES GLOABLES
time_t lastDamageTime = 0; 
SDL_Event event;
bool mainmenu=false;
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
bool benig=false;
SDL_Rect poslmp;
bool playb=false;
bool lvl1=false;
SDL_Surface ** tab;
bool lst =true;
//bool enigmelvl1=false;
bool playS=false;
int indnv = 0 ;
SDL_Surface *creditsIMG;
//////NEXT LEVEL ANIMATION // 
SDL_Surface * Loading[3];
Mix_Chunk *  nxtlvlSFX=NULL;
	bool show_obj=false;
bool credit=false;
				int bgscrolling=7;
Mix_Chunk * slideSFX;
SDL_Surface *lazer;

	    int x = 0, y = 0;
    int mouseX = 320, mouseY = 240;

							double elapsed_jump;
time_t level_start_time, current_time,time_j;
	time_t startTime;

//INTILIAZATION ET CREATION DU FENETRE + AFFICHAGE D'IMAGE MENU + Chargement de music 


if (SDL_Init(SDL_INIT_EVERYTHING) !=0 ) {
	printf("ERROR INITIALIZING SDL\n");
	SDL_Quit();
} else {	
	
	ecran = SDL_SetVideoMode(1920,1080,32, SDL_FULLSCREEN| SDL_HWSURFACE| SDL_DOUBLEBUF | SDL_SRCALPHA | SDL_NOFRAME);
	if (ecran== NULL) {
		printf("ERROR CREATING WINDOW");
	}
	//LES BOUTONS :
	      SDL_EnableUNICODE(1);

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
	slideSFX=Mix_LoadWAV("slideSFX.wav");
		if ( !slideSFX) {
			printf("ERROR LOADING SLIDE SFX \n");
			
		}
	creditsIMG=IMG_Load("credits.png");
		if ( !creditsIMG) {
				printf("ERROR LOADING CREDITS IMG\n");
			}
	
	lazer=IMG_Load("anim perso test/lazer.png");
		if ( !lazer) {
				printf("ERROR LOADING LAZER");
			
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
bool choose_skin=false;

////////////////
//VAR POUR ENIGME /////
SDL_Color Color = {255, 255, 255};
enig_fichier en;
int resultat_fichier;
init_enig_fichier(&en, Color);
Entity FB;
initFinalBoss(&FB);
ColorFade fade;
initColorFade(&fade, 255, 0, 0, 0, 0, 255, 2000); // Red to Blue over 2000 ms
Entity Drone;
Entity Lazer_drone;







////
Entity e1,e2,e3,CD_collect , Flash_collect , heart_collect,spider;
Entity DotP1= InitEntity("mini_joueur.png",1440,540,0);
Entity DotP2 = InitEntity("mini_es.png",480,540,0);
e1= InitEntity( "enemy.png", 1950 , 650,10);
e2= InitEntity("enemy2.png", 1950 ,650,12);
e3= InitEntity( "enemy3.png", 1950 , 650,14);
spider=InitEntity("spider.png",1925,-50,1);
Flash_collect= InitEntity("disk.png", 1100 ,ground+100,0);
heart_collect= InitEntity( "coin.png", 1000, ground+100,0);
CD_collect= InitEntity("cd.png", 1100 , ground-200,0);
Entity  TabEnt[3] = {e1,e2,e3};
Drone = InitEntity("drone.png", 1925 , 100 , -5);
Lazer_drone = InitEntity("anim perso test/lazer_drone.png",0 ,0, 0);
Drone.state = 1;
Button Load_btn;
init_btn(&Load_btn,"for ts/load_1.png","for ts/load_0.png",294,721);
Button change_outfit;
init_btn(&change_outfit,"Skin2/chng_0.png","Skin2/chng_1.png",1196,721);

Button Profiles_btn,Arrow__menu_btn;
init_btn(&Profiles_btn,"for ts/pfp_btn_0.png","for ts/pfp_btn_1.png",1546,43);
init_btn(&Arrow__menu_btn,"for ts/arrow_0.png","for ts/arrow_1.png",1753,210);
 int scoresP1[3], scoresP2[3];
SDL_Rect PlPvPos;
/////////
//VARIABLE DE LEVEL 1 : 
SDL_Rect PosTxt;
	SDL_Surface * SurfText;
	TTF_Font * font ;
	SDL_Color txtCoul;
	
SDL_Rect PosEnergy;
SDL_Surface *SurfEnergy	;
SDL_Color energyCoul;
SDL_Surface * TabCutscene[4];
InitCutscene(TabCutscene);
int ind_cutscene=0;
bool cut_scene = false;


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


//int score=0;


		SDL_Surface * ES=NULL,*Coin=NULL;
		SDL_Rect poses,posCoin;
		if ( InitES(&ES,&Coin, "enemy.png", "coin.png", &poses ,&posCoin) == 0) {
			printf("ERROR LOADING ES AND COINS\n");
			SDL_Quit();
		}
  minimap m1,m2,m3;
    initmap(&m1,"minimaplvl1.png");
    initmap(&m2,"minimaplvl2.png");
    initmap(&m3,"minimaplvl3.png");
		minimap TabMap[3]={m1,m2,m3};

	int indlvl;
Background TabBack[3];

    initBackground(&TabBack[0], ecran,"lvl1img1.png","lvl1img2.png"); // back lvl1
    bool Playing=false;

		initBackground(&TabBack[1], ecran,"lvl2img1.png","lvl2img2.png"); // back lvl 2
		initBackground(&TabBack[2], ecran,"lvl3img1.png","lvl3img2.png"); // back lvl3
    
							               bool final_boss = false;

Person player;
Person player_SecondOutfit;
	 player=InitPerso(player);
	 player_SecondOutfit=InitPersoSecondOutfit(player_SecondOutfit);

//player=player_SecondOutfit;
	
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
//VAR ARDUINO 
int arduino_fd;
    struct termios toptions;
    char buffer[255];
    int nbytes;
bool ManetteRight=false;
		bool ManetteLeft=false;
		bool ManetteMil=false;

//
//// Init arduino/
if (manette ==1) {


    // Open the serial port
    arduino_fd = open(ARDUINO_SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (arduino_fd == -1) {
        perror("Error opening serial port");
        return -1;
    }
 
    // Set serial port options
    tcgetattr(arduino_fd, &toptions);
    cfsetispeed(&toptions, B9600);
    cfsetospeed(&toptions, B9600);
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    tcsetattr(arduino_fd, TCSANOW, &toptions);



		}
		
		
		
		//VAR POUR 2EME JOUEUR
		SDL_Rect PLAYER2_ZONE = {0, 0, 960, 1080};
		SDL_Rect PLAYER1_ZONE = {960, 0, 960, 1080};
		Background bg1, bg2;
		initBackground(&bg1, ecran,"bg1.png","lvl1img2.png");
   		initBackground(&bg2, ecran,"bg1.png","lvl1img2.png");    
	Person p1;
	p1.posinit.x=1380;
	p1.posinit.y=540;
	Person p2;
	p2.posinit.x=480;
	p2.posinit.y=540;
	p1.score=0;
	p2.score=0;
	SDL_Rect PlaySpace1 = {1130,170 , 627 , 733};
	SDL_Rect PlaySpace2 = {170 , 170 ,627 , 733 };
loadPlayerSpriteSheet(&p1,"anim perso test/p1.png");
loadPlayerSpriteSheet(&p2,"anim perso test/p2.png");					
 bool p1r=false,p1l=false,p1u=false,p1d=false;
bool p2r=false,p2l=false,p2u=false,p2d=false;
      SDL_Rect PosScoreP2 = {1750,20,50,50};
Uint32 moveInterval = 5000;  // 1 SECONDE		
		Uint32 lastMoveTime_P1,lastMoveTime_P2;
						 lastMoveTime_P1 = SDL_GetTicks();
						 lastMoveTime_P2 = SDL_GetTicks();

SDL_Surface *SurfText_P1=NULL;
SDL_Surface *SurfText_P2=NULL;
SDL_Surface * SurfTime_P1=NULL;
SDL_Surface * SurfTime_P2=NULL;
SDL_Rect PosVie_P1={950,20, 50 , 50};
//SDL_Rect PosVie_P2={1120,20, 50 , 50};
///
////////
SDL_Rect poslazer;
	poslazer.x=player.posinit.x;
	poslazer.y=player.posinit.y +50;
	//bool player.shoot=false;
	SDL_Rect camera = {0, 0, 1024, 768};
int chose=0; // variable for login/signup
user Current_User;
Uint32 Global_startTime = SDL_GetTicks();
while (gameloop) {
	if ( manette ==1) {

		
    nbytes = read(arduino_fd, buffer, sizeof(buffer));
    if (nbytes > 0) {
        buffer[nbytes] = '\0';
        sscanf(buffer, "X:%d,Y:%d", &x, &y);
        ProcessControllerEvent(&event,arduino_fd, gamestate,ecran,&x,&y , buffer, &mouseX,&mouseY);
    }

		

}

			if (num_j==0) {handleGameMode(&num_j,ecran);}
				if(chose ==0 && num_j==1 ) {
						if(game(event,ecran,&Current_User) ==1) {
								mainmenu=true;
								gamestate=MAINMENU;
								chose=1;
								send_message(arduino_fd, Current_User.username);
								//send_message(arduino_fd, Current_User.username);
								//send_message(arduino_fd, "Login Successful");
								    //usleep(1000000); // Delay for 1 second

								//send_message(arduino_fd, "Welcome");
								  //  usleep(1000000); // Delay for 1 second

								


						}else {

								gameloop=false;


						}

				} else if(chose ==0 && num_j==2) {
						mainmenu=true;
				}




    				int EntityToShow = rand() % 3 ;

if (mainmenu ) {
optionmenu=false;
playS=false;
gameover=false;

SDL_BlitSurface(imgmenu, NULL, ecran, &posimg);
/*if (read_joystick(arduino_fd, &x, &y)) {
            // Debugging message
 			mouseX += (x - 512) / 100; // Adjust mapping as needed
            mouseY += (y - 512) / 100; // Adjust mapping as needed

            // Constrain the cursor within the screen boundaries
            if (mouseX < 0) mouseX = 0;
            if (mouseX > 1919) mouseX = 1919;
            if (mouseY < 0) mouseY = 0;
            if (mouseY > 1079) mouseY = 1079;
            	printf("X: %d\nY:%d\n",mouseX,mouseY);
            // Debugging message
        }
        event.motion.x = mouseX;
        event.motion.y=mouseY;
                SDL_PushEvent(&event);*/



if ( num_j==1) {
//show_high_score(imgmenu);
} else if (num_j==2) {
	//
}
	









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

//send_message(arduino_fd, Current_User.username); // past 


if ( event.motion.x >=  0 && event.motion.x <= 640 )  {
	SDL_BlitSurface(tab[0],NULL,ecran,&poslmp);
}  if ( event.motion.x >=  640 && event.motion.x <= 1280) {
	SDL_BlitSurface(tab[1],NULL,ecran,&poslmp);
}if ( event.motion.x >=  1280 && event.motion.x <= 1920) {
	SDL_BlitSurface(tab[2],NULL,ecran,&poslmp);
}



	blitButton(ecran,&Arrow__menu_btn);		
	if(isButtonClicked(&event,&Arrow__menu_btn.pos)){
				printf("PROFILES MENU\n");

				gamestate=MAINMENU;
					//if(handle_Profile_menu(event,ecran) ==1){
							//printf("PROFILE MENU ACCESSED\n");
							/*if(*/

				if(Profile_Menu(event, ecran)==0){
								mainmenu=true;
				}



								/*==0) {
									mainmenu=true;
							}

			/*}/* else {
					mainmenu=true;
				}*/
		}	
}

	    //write(arduino_fd, Current_User.username, 5);




//MISE A JOUR LEL ECRAN (necessaire) 

//ARDUINO MAIN MENU
if ( manette==1) {
if ( !playS && !Playing && !optionmenu && !gameover) {

} 
}

SDL_Flip(ecran);



//LECTURE DE CLAVIER :
	while (SDL_PollEvent(&event)!=0) {
		
	
		switch(event.type) {	
			case SDL_KEYDOWN:
			switch(event.key.keysym.sym) {
				case SDLK_ESCAPE:
				printf("--------Exit--------\n");
				gameloop=false; 

				break;
				case SDLK_h:
				break;
				case SDLK_BACKSPACE:
					if (mainmenu==true){num_j=0;} else {
				mainmenu=true;
				optionmenu=false;
				credit=false;
			}
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

				}
/*options*/		else 
                        if(sourisSurbtn(opts,event) && event.button.button==SDL_BUTTON_LEFT ){
					if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }

					mainmenu=false;
					optionmenu=true;




				}
/*credits*/		else if (sourisSurbtn(creds,event) && event.button.button==SDL_BUTTON_LEFT ){
					if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }		
										
								credit=true;

					
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

				}
				
				
		
			
	
}
	else if ( optionmenu ) { 

			if (sourisSurbtn(btn[0].pos,event) && event.button.button==SDL_BUTTON_LEFT  ) { // music on walla off

						MsClick=!MsClick;						
						Mix_VolumeMusic(0);
			   	} 
			if (sourisSurbtn(btn[1].pos,event) && event.button.button==SDL_BUTTON_LEFT ) { // sfx on walla off

						sfClick=!sfClick;
						Mix_HaltChannel(-1);
						
			   		
			   	}
			   if(sourisSurbtn(btn[4].pos,event) &&event.button.button==SDL_BUTTON_LEFT ) {
			   if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }

					ecranf = SDL_SetVideoMode(1920,1080,32, SDL_FULLSCREEN |  SDL_HWSURFACE| SDL_DOUBLEBUF);
					ecran=ecranf;
				}
				
			   if (sourisSurbtn(btn[5].pos,event) &&  event.button.button==SDL_BUTTON_LEFT) {
			   if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }

			   		ecranwin= SDL_SetVideoMode(1920,1080,32, SDL_HWSURFACE| SDL_DOUBLEBUF);
			   		ecran=ecranwin;	
			   		}

			if(( (event.motion.x >= 1335 && event.motion.x <= 1335+80 && event.motion.y >=713 && event.motion.y <= 713 + 80 ) && (event.button.button==SDL_BUTTON_LEFT) ) ) { 
				if ( compt <100 && compt>=0) {
				compt+=25;
				}
				
			 }
			   if(( (event.motion.x >= 591 && event.motion.x <= 591+60 && event.motion.y >=600 && event.motion.y <= 713 + 80 ) &&  event.button.button==SDL_BUTTON_LEFT ) ) {



			 	if ( compt > 0  && compt <= 100) {
			 	compt-=25;
			 	}
			 	
			 	}	
			   	
			


}
if ( credit) {mainmenu=false;SDL_BlitSurface(creditsIMG,NULL,ecran,&pas);} // 


 
	}

								
				
			

}//END OF POLL EVENT 


if (optionmenu==true ){
								
		
		        SDL_BlitSurface(backg, NULL, ecran, NULL);
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

		

			if ( playS) {
				if(manette==1) {
					nbytes = read(arduino_fd, buffer, sizeof(buffer));
    if (nbytes > 0) {
        buffer[nbytes] = '\0';
	       if(strstr(buffer,"BL")) {
	       		indlvl=1;
	       		Playing=true;
				playS=false;
				cut_scene=true;
				gamestate=PLAYING;

	       } else if(strstr(buffer,"BU")) {
	       	indlvl=2;
	       	Playing=true;
			playS=false;
			gamestate=PLAYING;
	       } else if(strstr(buffer,"BR")) {
	       	indlvl=3;
	       	Playing=true;
			playS=false;
			gamestate=PLAYING;
	       }

    }
				}
				if ( num_j==2 ) {{if(HandleMPAuthentication(ecran,event )) {indlvl=1;Playing=true;playS=false; startMPtimer=true;chose_MP =1;
				startTime = time(NULL);}}}

							
					SDL_BlitSurface(seleclevel,NULL,ecran,&posimg);
					 blitButton(ecran,&change_outfit,event);
					 blitButton(ecran,&Load_btn,event);
					while ( SDL_PollEvent(&event)){
						switch(event.type) {
							case SDL_KEYDOWN:
								switch(event.key.keysym.sym) {
									case SDLK_KP1:
										indlvl=1;
										Playing=true;
										playS=false;
										cut_scene=true;
																					gamestate=PLAYING;


										break;
									case SDLK_KP2:
										indlvl=2;
										Playing=true;
										playS=false;	
																				gamestate=PLAYING;

										break;
									case SDLK_KP3:
										indlvl=3;
										Playing=true;
										playS=false;	
																				gamestate=PLAYING;

									break;
									case SDLK_BACKSPACE:
										
										mainmenu=true;
										playS=false;
										Playing=false;
																				gamestate=PLAYING;

									break;
									case SDLK_ESCAPE:
									quitter=1;
									
									
								}
							}

						if(isButtonClicked(&event,&Load_btn.pos)){
							if(	loadGame("Saves.txt",&player,&indlvl,&collected,&Current_User)){
								Playing=true;
								playS=false;
							}else{
							 renderText(ecran, "This user doesnt have any saves", font, Color, 500, 900);
							 SDL_Flip(ecran);
							 SDL_Delay(1000);
							}
						}
						if(isButtonClicked(&event,&change_outfit.pos)) {
									playS=false;
								if(handle_SkinSelection(event,ecran,player,player_SecondOutfit)==1){
									player=player_SecondOutfit;
									playS=true;
								}else{
									playS=true;
	
								}
						}




							}
					
						
	
							if ( manette==1) {
							/*if (read_joystick(arduino_fd, &x, &y)){

	if (strstr(buffer,"pin 3")){
			indlvl=1;
			Playing=true;
			playS=false;
	}
	if (strstr(buffer,"pin 7")){
indlvl=2;
Playing=true;
playS=false;
	
	}
	
	if (strstr(buffer,"pin 13" )){
			indlvl=3;
			Playing=true;
			playS=false;
	
	
	}
}*/
}

	
					


					}
						
						SDL_Flip(ecran);
					if (Playing) {
					
						        time(&level_start_time);
					Mix_PlayMusic(themelvl1,-1);

						
				do {

						printf("Mouse X : %d \n Mouse Y : %d\n",x,y);
			SDL_Rect posEsMnmp;
		//BLITTAGE
				if ( gameover== false){

				
				if ( num_j==1) {
					if (cut_scene == true  && ind_cutscene <=3) { // cut scene
						//if ( ind_cutscene <=3 ) {
						SDL_BlitSurface(TabCutscene[ind_cutscene],NULL,ecran,NULL);

						while(SDL_PollEvent(&event)) {
							switch(event.type) {
							 	case SDL_KEYDOWN:
							 		switch(event.key.keysym.sym) {
							 		case SDLK_RIGHT:
							 			if ( ind_cutscene < 3) {
							 			ind_cutscene++;
							 			break;
							 		} 
							 			cut_scene=false;
							 		case SDLK_LEFT:
							 			if ( ind_cutscene != 0 ) {
							 			ind_cutscene--;
							 			;
							 		} else {
							 				ind_cutscene=0;
							 		}
							 		break;
							 		
							 		case SDLK_RETURN:
							 			cut_scene=false;
							 			ind_cutscene = 5;
							 		break;

							 		}
							 	break;
							}
						}
							player.score=0;

					//}
					

					} else {
						PlPvPos = (SDL_Rect) player.posinit;
			 TabMap[indlvl-1].pos_joueur = MAJMinimap(player.posinit, 10, TabBack[indlvl-1].camera_pos);  // Adjust scale as needed
			 TabMap[indlvl-1].pos_es =MAJMinimap(TabEnt[EntityToShow].pos, 10, TabBack[indlvl-1].camera_pos);
				if ( final_boss == false) {deplacerES(&TabEnt[EntityToShow],TabEnt[EntityToShow].dx);}
				deplacerCoin(&heart_collect,3);

	       if (TabBack[indlvl-1].showing_main_image) {
            SDL_BlitSurface(TabBack[indlvl-1].image, &TabBack[indlvl-1].camera_pos, ecran, NULL);
        } else {
            SDL_BlitSurface(TabBack[indlvl-1].secondary_image, &TabBack[indlvl-1].camera_pos, ecran, NULL);
        }
        				updateBackgroundImage(&TabBack[indlvl-1]);

        				afficher_score(player.score,&PosTxt,&SurfText ,font ,txtCoul );
        				
        				afficher_energy(player,&PosEnergy,&SurfEnergy ,font ,energyCoul );
				SDL_BlitSurface(SurfText,NULL,ecran,&PosTxt);
				SDL_BlitSurface(SurfEnergy,NULL,ecran,&PosEnergy);
				



				afficherES(ecran,heart_collect);	
				afficherPerso(&player, ecran);
			
				if ( indlvl==2) {
					if (Flash_collect.active) {
							Flash_collect.pos.x-=3;
							afficherES(ecran,Flash_collect);
						} 
						
					if ( CD_collect.active) {
						CD_collect.pos.x-=3;
						afficherES(ecran,CD_collect);
					}

																deplacerES(&spider,spider.dx);
																afficherES(ecran,spider);											
																				spider.pos.y+=2;
																			if ( spider.pos.y >= 110) {
																					spider.pos.y=-20;
																			}
																				
																	
									
							
						
					}
						if ( player.shoot) {
								SDL_BlitSurface(lazer,NULL,ecran,&poslazer);
						}
						if ( indlvl==3) {
								printf("FB X : %d\n FB Y : %d\n",FB.pos.x,FB.pos.y);
								printf("Player Shoot : %d\n" , player.shoot);
								if (final_boss==true) {

										
										AnimerFB(&FB,ecran);
										deplacerFB_AVEC_AI(&FB,player,&Drone);
										render_hacker_health(&FB,ecran,font,1000);

										if( FB.weapon) {
											//deplacerES(&Drone,Drone.dx);	
											  move_and_animate_drone(&Drone, &Lazer_drone);
											  move_laser(&Lazer_drone);

											  afficherES(ecran,Drone);
											//Handle_Fight(&player,&FB);

											  	if (Lazer_drone.active) {
                									afficherES(ecran, Lazer_drone);
          									    }
											//Drop_Laser(&Lazer_drone, &Drone, 2000);

										}
										if ( FB.pos.x < 1800  && player.shoot ) {

										//handle_FB_health(&FB, poslazer);
											FB.health--;
										
								}
									if(checkCollision(player.posinit,Lazer_drone.pos)) {
										if (sfClick == false) {
                        Mix_PlayChannel(-1, dmgSFX, 0);
                    }

                    player.textcourant = 14;
												player.num_hearts=1;

										}
									if ( FB.health < 0) {

											        //updateScreenColor(ecran, &fade);

											        handleGameWin(ecran,&mainmenu,musicmenu);
											        FB.health=500;
											        Playing=false;
											        final_boss=false;
											        benig=false;
									}




							}
						}

					if (final_boss == false) {afficherES(ecran,TabEnt[EntityToShow]);}
					afficherminimap(TabMap[indlvl-1], ecran);
				}
				}else  if (num_j ==2 && chose_MP){ // si il ya 2 joueur // MULTIPLAYER
						printf("ok\n");
						        	printf("start mp timer %d\n",startMPtimer);
						        						printf("ok\n");
						        		if(startMPtimer==true && chose_MP==1) {
						        							        	printf("start mp timer %d\n",startMPtimer);

						        								currentTime_P1 = SDL_GetTicks();
						        								currentTime_P2=SDL_GetTicks();

						    	player.num_hearts=3;
						    	printf("TIME %d ", currentTime_P1/1000);
			 	SDL_BlitSurface(bg1.image, NULL, ecran, &PLAYER1_ZONE);
			 							printf("ok\n");

			 	SDL_BlitSurface(bg2.image, NULL, ecran, &PLAYER2_ZONE);
			 							printf("ok\n");
			
			 							printf("ok\n");
			 	        								printf("ok\n");

        		Deplacer_ET_NON_COLLISION(&p1, &DotP1, PlaySpace1, &lastMoveTime_P1, currentTime_P1, moveInterval);
				Deplacer_ET_NON_COLLISION(&p2, &DotP2, PlaySpace2, &lastMoveTime_P2, currentTime_P2, moveInterval);
        		afficherES(ecran,DotP1);
				afficherES(ecran,DotP2);
				


				
					
       afficher_score(p1.score,&PosTxt,&SurfText_P2 ,font ,txtCoul );
      afficher_score(p2.score,&PosTxt,&SurfText_P1 ,font ,txtCoul );
      SDL_BlitSurface(SurfText_P1,NULL,ecran,&PosTxt);
      SDL_BlitSurface(SurfText_P2,NULL,ecran,&PosScoreP2);
      renderPlayerFrame(&p1,ecran);
      renderPlayerFrame(&p2,ecran);
      // int remainingTime = timer(startTime, 120, font, PosVie_P1, ecran);
      if ( timer(startTime, 62, font, PosVie_P1, ecran) == 0) {handleMPGameState (p1.score , p2.score ,PLAYER1_ZONE,PLAYER2_ZONE ,  ecran,&mainmenu,&Playing);currentTime_P1=0;startMPtimer=false;}

        SDL_Flip(ecran); // Update screen
        SDL_Delay(60); // Adjust frame rate								

				} else {
					currentTime_P1=0;
					printf("TIME %d ", currentTime_P1/1000);
				}
				}
				
				
				
        	
				}
				SDL_Flip(ecran);
				if(manette) {
				read_joystick(arduino_fd, &x,&y,&command);
				if (x > 600) {
					right=false;
					left=true;
        }
        if (x < 110) {
        	left=false;
        	right=true;
        }
        	if(command == SHOOT) {	
        		player.shoot=true;
        	}
        	if(command==SLIDE) {
        			right=false;
        			event.type=SDL_KEYDOWN;
        			event.key.keysym.sym=SDLK_c;
        			slideStartTime = SDL_GetTicks();
        			SDL_PushEvent(&event);
        			sliding=true;

        	} 

					if (sliding && SDL_GetTicks() - slideStartTime >= SLIDE_DURATION) {
        					event.type=SDL_KEYUP;
        			event.key.keysym.sym=SDLK_c;
        			SDL_PushEvent(&event);
        			bgscrolling=7;
						player.posinit.y=ground;
						sliding=false;
        				}

			if(command==JUMP) {
        			right=false;
        			event.type=SDL_KEYDOWN;
        			event.key.keysym.sym=SDLK_SPACE;
        			jumpStartTime = SDL_GetTicks();
        			SDL_PushEvent(&event);
        			jumping=true;

        	} 

					if (jumping && SDL_GetTicks() - jumpStartTime >= JUMP_DURATION) {
        					event.type=SDL_KEYUP;
        			event.key.keysym.sym=SDLK_SPACE;
        			SDL_PushEvent(&event);
        			//bgscrolling=7;
						player.posinit.y=ground;
						jumping=false;
        				}

        				/*if(command==PAUSEMENU) {
        					event.type=SDL_KEYDOWN;
        			event.key.keysym.sym=SDLK_ESCAPE;
        			SDL_PushEvent(&event);
        			command=NONE;
        				
        				}*/


        	

					

        	
       }
	while(SDL_PollEvent(&event)) {
	
		 

	if ( num_j==1 && !cut_scene) {
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_RIGHT:
						if (  !jump){
					right = true;
					}
					
					
					break;
					case SDLK_LEFT:
					left=true;

					break;
					
					/*case SDLK_ESCAPE:
						if ( Playing == true) {
					Playing=false;
					mainmenu=true;
					Mix_PlayMusic(musicmenu,-1);

					}
					
					break;*/
					case SDLK_SPACE:
					if ( jump == false) {
					jump=true;
					}
					break;
					case SDLK_c:
							if ( player.posinit.x >=350 && player.energy > 25 ) {
						player.slide=1;
						bgscrolling=13;
						}
							
					
					break;
					case SDLK_x:
						player.shoot=true;
						break;
					case SDLK_ESCAPE:
							 if(handle_pause_menu(event, ecran,&player ,indlvl, collected,&Current_User)==2) {
							 	Playing=false;
					mainmenu=true;
					Mix_PlayMusic(musicmenu,-1);

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
			break;
			case SDLK_c:
						if ( player.slide == 1) {
									player.slide=0;
									player.textcourant=2;
									
									
				}
				bgscrolling=7;
				player.posinit.y=ground;
				break;

			
				
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
		
		
		
	
			
			
				
				
				
				
				
				
	} else {
            if (event.type == SDL_QUIT) {
                gameloop = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:

					Playing=false;
					mainmenu=true;
					Mix_PlayMusic(musicmenu,-1);
					break;
                    case SDLK_UP:
                        p1.direction = 3; // Set direction to p1u
                        p1u=true;
                    break;
                    case SDLK_DOWN:
                        p1.direction = 0; // Set direction to p1d
                        p1d=true;
                        break;
                    case SDLK_LEFT:
                        p1.direction = 1; // Set direction to p1l
                        p1l=true;
                        break;
                    case SDLK_RIGHT:
                        p1.direction = 2; // Set direction to p1r
                        p1r=true;
                        break;
                  
                    case SDLK_z:
                    	p2.direction=3;
                    	p2u=true;
                    break;
                    case SDLK_s:
                    	p2.direction=0;
                    	p2d=true;
                    break;
                    case SDLK_q:
                    	p2.direction=1;
                    	p2l=true;
                    break;
                    case SDLK_d:
                    	p2.direction=2;
                    	p2r=true;
                    break;
                    

                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:

                        p1u=false;
                        break;
                    case SDLK_DOWN:

                        p1d=false;
                        break;
                    case SDLK_LEFT:

                        p1l=false;
                        break;
                    case SDLK_RIGHT:

                        p1r=false;
                        break;
                   
                       case SDLK_z:

                    	p2u=false;
                    break;
                    case SDLK_s:

                    	p2d=false;
                    break;
                    case SDLK_d:

                    	p2r=false;
                    break;
                    case SDLK_q:

                    	p2l=false;
                    break;
                }
            }
       
	
						

	}
	
	}//END OF POLL EVENT LOOP
	
			
		
	 //MANETTE
	 if ( manette==1) {
        /*if (	read_joystick(arduino_fd, &x, &y)){
        	
        	
							
            

							if ( x > 600 ) {
										right=true;
										left=false;
										jump=false;
							} 
								
								if (strstr(buffer, "pin2")) {
								right=false;
								left=false;
								if (player.textcourant < 5) {
            player.textcourant = 10;
            jumpPerso(&player, 1);
        } else {
            player.textcourant = 12;
            jumpPerso(&player, -1);
        }
        
    time(&jump_start_time);
    printf("Jump started at: %ld\n", jump_start_time);
}


if (jump_start_time != 0) {

    time(&current_time);


    elapsed_jump = difftime(current_time, jump_start_time);



    if (elapsed_jump >= 0.1) {

        player.posinit.y = ground;
        printf("Player returned to ground\n");
        jump_start_time = 0;
        
    } 
}
							
								
								
							if ( x < 110) {
								left=true;	
								right=false;
								jump=false;
								//usleep(100);  


							}
							            	printf("X: %d\nY:%d\n",x,y);

							
							
							
							
							
           
        }*/
     
    //
}
    
	//GESTIN MOVEMENT ET SCROLLING BACKGROUND
				if (right ) {
				
			player.score+=3;
			deplacerPerso(&player,1,&currenttext);

			
		}
		
		if (left) {
			player.score-=1;
			deplacerPerso(&player,-1,&currenttext);
			}
			if ((player.slide==1  && right) )	 {
					Mix_PlayChannel(-1,slideSFX,0);
					bgscrolling++;
					right=false;
					player.textcourant=15;	
					player.posinit.y=500;
					
			} 
				
					
			
	if (player.posinit.x >= 350  ) {   
	   player.posinit.x= 350 ;   
       scrollingHorizontal(&TabBack[indlvl-1], bgscrolling);			
       	}
   if( player.slide ==1 || sliding==true) {
    		player.energy--;									
    													
    }
       	
       	
       	if( player.energy > 100) {player.energy=100;}
       	if ( player.energy < 0 ) {player.energy=0;}
       	if ( player.energy < 25 && player.slide==1) {player.posinit.y =ground ; player.textcourant =10;player.slide=0; jumpPerso(&player,1);bgscrolling=7;}
      	
      	
     if ( player.shoot) {
     		poslazer.x+=50;
     		poslazer.y++;
     			if ( poslazer.x > 1920 ) {poslazer.x=player.posinit.x;player.shoot=false;poslazer.y=player.posinit.y;}
     		
     }
     		
     		if ( num_j==2) {
     			if (p1u ) {p1.posinit.y-=10; p1d=false;p1l=false;p1r=false;p1.frame = (p1.frame + 1) % NUM_FRAMES;}
        		if (p1d){p1.posinit.y+=10;p1.frame = (p1.frame + 1) % NUM_FRAMES;}
        		if(p1r){p1.posinit.x+=10;p1.frame = (p1.frame + 1) % NUM_FRAMES;}
        		if(p1l) {p1.posinit.x-=10;p1.frame = (p1.frame + 1) % NUM_FRAMES;}
        		
        		if (p2u ) {p2.posinit.y-=10;p2.frame = (p2.frame + 1) % NUM_FRAMES;}
        		if (p2d){p2.posinit.y+=10;p2.frame = (p2.frame + 1) % NUM_FRAMES;}
        		if(p2r){p2.posinit.x+=10;p2.frame = (p2.frame + 1) % NUM_FRAMES;}
        		if(p2l) {p2.posinit.x-=10;p2.frame = (p2.frame + 1) % NUM_FRAMES;}
        		
        		
        		

     					/*if ( p1.posinit.y > 1080 / 2) {
     							scrollingVertical(&bg2,5);
     							p1.posinit.y = 1080 / 2;
     					}

     					   
     					if ( p2.posinit.y > 1080 / 2) {
     							scrollingVertical(&bg1,4);
     							p2.posinit.y = 1080/2;
     					}*/

     					if ( p1.posinit.x < SCREEN_WIDTH/2) {
					
					p1.posinit.x = SCREEN_WIDTH/2;
					}
						if ( p2.posinit.x > SCREEN_WIDTH/2) {
					
					p2.posinit.x = SCREEN_WIDTH/2  ;
					}
     					
     					
     	
     		}

       	
			 /////////////////////////////////////////////      
       		
       		
       		
		 //GESTION COLLISON ET DOMMAGE///////////////////////////
		
		 
		 
		 
			time_t currentTime = time(NULL);
       if (currentTime - lastDamageTime >= DAMAGE_COOLDOWN) {
            int collisionType = Collided(player.posinit,TabEnt[EntityToShow].pos);
         
            switch (collisionType) {
                case 1:
											if ( player.slide==0) {
                    if (sfClick == false) {
                        Mix_PlayChannel(-1, dmgSFX, 0);
                    }

                    player.textcourant = 14;
                    player.score -= 10;
                    if (player.num_hearts != 0) {
                        player.num_hearts--;
                    }
                    lastDamageTime = currentTime;
                    EntityToShow = rand() % 3 ;
                    } else {
                    			 TabEnt[EntityToShow].pos.x=1920;
									EntityToShow = rand() % 3 ;
									player.score+=100;
                    			
                    }
                    break;
                case 2:
                TabEnt[EntityToShow].pos.x=1920;
									EntityToShow = rand() % 3 ;
									player.score+=100;
								
                    break;
                default:

                    break;
            }
            		
            
            
        }


if(indlvl==2){ if ( Collided(spider.pos,player.posinit) == 1  && player.slide==0){	

												spider.dx=15;
												player.textcourant=14;
													if( player.num_hearts !=0 ) {
												player.num_hearts--;
											}
											spider.dx=-5;
											
				}  else if (Collided(spider.pos,player.posinit) == 1 &&  player.slide==1) {
																									spider.dx=-5;
																									player.score+=125;
																				}
													if ( spider.pos.x >= 1960) {
																spider.dx=5;
														}
														
				if ( Collided (spider.pos,poslazer) ==1 ) {spider.dx=-5;
																									player.score+=125;
																				
													if ( spider.pos.x >= 1960) {
																spider.dx=5;
														}}


													}

       

																				

	
   /* if ((Drone.pos.x - 250) - player.posinit.x < 250 && (Drone.pos.x - 250) - player.posinit.x > 270 ) {
    	Drone.dx=-10;
    	//FB.pos.x += 50;
    	

    	
    }
    if( FB.pos.x < 1800) {
    	if (player.shoot) {
    				FB.dx=-10;
    				FB.health-=25;		
    		}
    }*/
    if (Collided(Drone.pos,player.posinit) == 1  ) {
    			FB.dx-=10;

    	}

    	if(FB.pos.x > 2500) {
    			FB.dx+=10;
    	}


		if ( Drone.pos.x <= 50) {
				Drone.dx =5;
		} 
		if (Drone.pos.x > 1800 ) {
			Drone.dx=-5;
		}

		

    	


        if ( num_j==1) {
        HandleCollision_Player_Bonus(&player,&heart_collect.pos,&player.score,CoinSFX);
    }
        
	if ( player.num_hearts < 1 ) {
	player.num_hearts=1;



	gameover=true;

		}
				
				
			

		///////////////////////////////////////////////////
		
		
if (gameover==true) {


							if ( sfClick == false  && lst ) {Mix_PlayChannel(-1,gameOverSFX,0); lst = false;}
				Mix_HaltMusic();
				SDL_BlitSurface(Gameover,NULL,ecran,&pas);
				TabEnt[EntityToShow].pos.x=1800;
				if(manette) {
								nbytes = read(arduino_fd, buffer, sizeof(buffer));
    if (nbytes > 0) {
        buffer[nbytes] = '\0';
	       if(strstr(buffer,"BL")) {
	       		lst=true;
						Mix_ResumeMusic();		
						Mix_PlayMusic(themelvl1,-1);
						TabEnt[EntityToShow].pos.x = 1600;
						//poses.x=1800;
						player.posinit.x = 100;
						player.num_hearts=3;

						player.score=0;
						lvl1=true;
						gameover=false;
						indlvl=1;

	       }  else if(strstr(buffer,"BR")) {
	     Playing=false;
						playS=false;
						gameover=false;
						mainmenu=true;
						cut_scene=true;
						player.score=0;
						benig=false;



						player.num_hearts=3;
						player.energy=100;

						Mix_PlayMusic(musicmenu,-1);
	       }

    }





				}
					switch(event.type){
					case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
					case SDLK_y:
						lst=true;
						Mix_ResumeMusic();		
						Mix_PlayMusic(themelvl1,-1);
						TabEnt[EntityToShow].pos.x = 1600;
						//poses.x=1800;
						player.posinit.x = 100;
						player.num_hearts=3;

						player.score=0;
						lvl1=true;
						gameover=false;
						indlvl=1;
					break;						
					case SDLK_n:		
						Playing=false;
						playS=false;
						gameover=false;
						mainmenu=true;
						cut_scene=true;
						player.score=0;
						benig=false;



						player.num_hearts=3;
						player.energy=100;

						Mix_PlayMusic(musicmenu,-1);
					break;
					}
				break;
		}
		
		
}



	if ( indlvl==1  && num_j==1) { //GESTION TIC TAC TOE
				time(&current_time);
					                double elapsed_time = difftime(current_time, level_start_time);
					                	
					                if (elapsed_time >= 30 && !gameover && !cut_scene) {
			
			
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
										player.score+=700;
										
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
			if(t.j==1)
		{
			joueur2(t.tab);
			t.j=0;
			z.j=atilganger(t.tab);
			printf("%d\n" , z.j);
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
							
					}while(ttc);
					
						if ( tcc_won) {
					Playing=false;
					ttc=false;
										Pass_to_Next_Level(Loading, ecran, &nxtlvlSFX,&player,TabBack , indlvl);
										playS=true;
					
				}
					} 
					}
					

				if ( indlvl==2 ) {  // lvl 2
							time(&current_time);
					                double elapsed_time = difftime(current_time, level_start_time);
					                
					                if (elapsed_time >= 8 && elapsed_time <=14 ) {
																			Flash_collect.active=true;
																								 if ( HandleCollision_Player_Bonus(&player,&Flash_collect.pos,&player.score,CoinSFX) == 1) {Flash_collect.active=false;collected=1;}				
					                }
					                
					                if ( elapsed_time >= 25 && elapsed_time <= 30) {
					                	CD_collect.active=true;
																								 if ( HandleCollision_Player_Bonus(&player,&CD_collect.pos,&player.score,CoinSFX) == 1) {CD_collect.active=false;collected=2;}			
					                	
					                	}
					                	
					                	
					           if ( collected>=2 ) {
					           
					           																					Pass_to_Next_Level(Loading, ecran, &nxtlvlSFX,&player,TabBack , indlvl);
					           																					collected=0;
					           																					Playing=false;
					           																					playS=true;
					           }
					           
					                	
							        				 
							        		
											
				}
				

				if ( indlvl==3 ) {
				time(&current_time);
					                double elapsed_time = difftime(current_time, level_start_time);
					                if (elapsed_time >= 3 && elapsed_time <= 10 && benig==false) {
					                benig=true;
					                
					                }

					               if ( benig){
    									resultat_fichier = quiz1(&en,ecran);
    										if ( resultat_fichier  == 1 ) {
    											
    												benig=false;
    												final_boss = true;
    											
    												//Playing=false;
    												//playS=true;
    										} else  if ( resultat_fichier == 2){
    												benig=false;
    												Playing=false;
    												playS=false;
    												handleGameLoss(ecran,&mainmenu,musicmenu); 


    										}

					                

				}
				

				}
				
				
				
				
				
   
	
	
	
	
	
	
	
	
	
	
	
	
	
		




}while(Playing == true);
			}
			
			
			 // FIN LEVEL 1 //////////////////////////////////////////
				//}//FIN PLAY
			
			} // FIN gameloop;

			Uint32 Global_endTime = SDL_GetTicks();
			Uint32 totalPlayTime = getTimeDifference(Global_startTime,Global_endTime);
			saveGameTime("gameTime.txt",totalPlayTime);
			
			//SAUVEGARDE DU SCORE
			if ( num_j==1) {
			if ( sauvegarde_score(player.score,"score.txt") == false ) {
				printf("ERROR SAVING SCORE \n");
			} else {
				printf("=========Score saved=========\n");
			}
			//HIGHEST_SCORE
			
			int	highest_score;
			highest_score=best_score("score.txt");
			if ( best_score == 0 ) {
					printf("ERROR LOADING HIGHEST SCORE \n");
			}else {
				printf("=========Highest Score:%u\n=========",highest_score);
			}
			
			} else {

					if ( SAVE_SCORE_MP(p1.score ,p2.score ,"score_MP")){printf("MULTIPLAYER SCORE SAVED \n");}


						}
				
			
			
			
		//LIBERATION 
			

	for( int p=0 ; p < 16 ; p++) {
		SDL_FreeSurface(player.texture[p]);
		SDL_FreeSurface(player_SecondOutfit.texture[p]);
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


    /*for (int i = 0; i < 2; i++) {
        SDL_FreeSurface(t.img[i]);
    }*/




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
		for ( int i=0 ; i < 3 ; i++) {SDL_FreeSurface(TabEnt[i].texture);}
		SDL_FreeSurface(heart_collect.texture);
		SDL_FreeSurface(Flash_collect.texture);
		SDL_FreeSurface(CD_collect.texture);		


    

	SDL_FreeSurface(Gameover);

//SDL_FreeSurface(e.img);
    /*for (int i = 0; i < 10; i++) {
        SDL_FreeSurface(e.timer[i]);
    }*/
    for (int dir = 0; dir < NUM_DIRECTIONS; ++dir) {
        for (int frame = 0; frame < NUM_FRAMES; ++frame) {
            SDL_FreeSurface(p1.sprite[dir][frame]);
        }
    }
    SDL_FreeSurface(p1.spriteSheet);
   	for ( int i=0 ; i < 4 ; i++) {
   			SDL_FreeSurface(TabCutscene[i]);
   	}
   	for ( int i=0 ; i< 6 ; i++) {
   			SDL_FreeSurface(FB.anim[i]);
   	}

   	SDL_FreeSurface(DotP1.texture);
   	SDL_FreeSurface(DotP2.texture);
   	SDL_FreeSurface(SurfTime_P1);
   	SDL_FreeSurface(SurfTime_P2);
   	SDL_FreeSurface(SurfText_P1);
   	SDL_FreeSurface(SurfText_P2);
    //SDL_FreeSurface(e.res);
    free_surface_enig_fichier(&en);
    SDL_FreeSurface(m1.img_map);
    SDL_FreeSurface(m2.img_map);
    SDL_FreeSurface(m3.img_map);
    SDL_FreeSurface(m1.img_es);
    SDL_FreeSurface(m2.img_es);
    SDL_FreeSurface(m3.img_es);
    freeButton(&Load_btn);
    freeButton(&change_outfit);
    SDL_FreeSurface(lazer);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(imgmenu);
    SDL_FreeSurface(backg);
    SDL_FreeSurface(lamp1);
    SDL_FreeSurface(lamp2);
    SDL_FreeSurface(seleclevel);
    SDL_FreeSurface(Gameover);
    SDL_FreeSurface(ES);
		SDL_FreeSurface(surft);
	SDL_FreeSurface(Lazer_drone.texture);
	SDL_FreeSurface(Drone.texture);
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

    if ( manette !=0 ) {
     close(arduino_fd);
    }
    printf("=========Execution complete=========\n");
return 0;
}




	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


