#include "header.h"


int main() {
//VARIABLES GLOABLES 
SDL_Event event;
bool mainmenu=true;
bool optionmenu=false;
bool gameloop=true;
SDL_Surface *ecran=NULL;
SDL_Surface *imgmenu=NULL,*play0=NULL,*play1=NULL,*opts0=NULL,*opts1=NULL,*credit0=NULL,*credit1=NULL,*quit0=NULL,*quit1=NULL,*lvlback=NULL,*ecranf,*ecranwin;
SDL_Rect posimg,poslvl1;
Mix_Music *musicmenu;
Mix_Chunk *click;
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


//INTILIAZATION ET CREATION DU FENETRE + AFFICHAGE D'IMAGE MENU + Chargement de music 


if (SDL_Init(SDL_INIT_EVERYTHING) !=0 ) {
	printf("ERROR INITIALIZING SDL\n");
	SDL_Quit();
} else {	
	
	ecran = SDL_SetVideoMode(1920,1080,32, SDL_FULLSCREEN| SDL_HWSURFACE| SDL_DOUBLEBUF);
	if (ecran== NULL) {
		printf("ERROR CREATING WINDOW");
	}
	//LES BOUTONS :

	loadbtns(&play0,&play1,&opts0,&opts1,&credit0,&credit1,&quit0,&quit1);
	
	
				//L'IMAGE MENU
	
	imgmenu = IMG_Load("/home/aziz/Desktop/Travail/nvack.png");
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
        musicmenu=Mix_LoadMUS("/home/aziz/Desktop/Travail/r&m.mp3");
        if (musicmenu ==NULL) {
	printf("ERROR OPENING MUSIC \n");
}
	click=Mix_LoadWAV("click.wav");
	if ( click==NULL) {
	printf("ERROR LOADING CLICK SOUND\n");
}
}
if (TTF_Init() !=0 ) {
	printf("ERROR LOADING TTF ");
}

	backg=IMG_Load("/home/aziz/Desktop/Travail/ts_opt/op1.png");
		//Blit  D'image menu + boutons
//SDL_BlitSurface(imgmenu, NULL, ecran, &posimg);

//lamp1 = IMG_Load("/home/aziz/Desktop/Travail/ts_opt/lamp1.png");
//lamp2=IMG_Load("/home/aziz/Desktop/Travail/ts_opt/lamp2.png");
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

Mix_PlayMusic(musicmenu,-1);
Mix_VolumeMusic(90);
int j;
while (gameloop) {

if (mainmenu ) {
SDL_BlitSurface(imgmenu, NULL, ecran, &posimg);

	









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

//loadtext ("YUMATECH", "/home/aziz/Desktop/Travail/CFGlitchCity-Regular.ttf", 50 , 0, 962 , 107 , ecran);



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
				SDL_FreeSurface(ecran);
				SDL_FreeSurface(imgmenu);
				Mix_FreeMusic(musicmenu);
				Mix_CloseAudio();
				SDL_Delay(10);
				SDL_Quit();
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
				lvl1=true;
				break;
				
			}
				break;	
			

			case SDL_MOUSEBUTTONDOWN:
			if ( mainmenu) {
/*play*/		if ( sourisSurbtn(play,event)&& event.button.button==SDL_BUTTON_LEFT ) {
					if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }
					mainmenu=false;
					lvl1=true;
					printf("TEST SUR CLICK  PASSE \n");
				}
/*options*/		else 
                        if(sourisSurbtn(opts,event) && event.button.button==SDL_BUTTON_LEFT ){
					if ( sfClick == false ) {Mix_PlayChannel(-1,click,0); }
					printf("Options\n");
					optionmenu=true;
					mainmenu=false;
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


if (optionmenu==true){
				
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
if (lvl1) {	
				
		loadlevel1(lvlback,ecran,poslvl1);
	}
}//END OF GAME LOOP

SDL_FreeSurface(ecran);
SDL_FreeSurface(imgmenu);
SDL_FreeSurface(backg);
SDL_FreeSurface(lamp1);
SDL_FreeSurface(lamp2);


Mix_FreeMusic(musicmenu);
Mix_FreeChunk(click);


Mix_CloseAudio();
Mix_Quit();
SDL_Quit();
return 0;
}



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


