#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>
#include <SDL/SDL_ttf.h>

void dimenstionsBTN(SDL_Rect* btn1,SDL_Rect *btn2,SDL_Rect *btn3,SDL_Rect* btn4,SDL_Surface * btnclick0) {
	btn1->x=218;
	btn1->y=89;
	btn1->w=btnclick0->w;
	btn1->h=btnclick0->h;
	
	btn2->x=218;
	btn2->y=340;
	btn2->w=btnclick0->w;
	btn2->h=btnclick0->h;
	
	btn3->x=218;
	btn3->y=588;
	btn3->w=btnclick0->w;
	btn3->h=btnclick0->h;
	
	btn4->x=218;
	btn4->y=832;
	btn4->w=btnclick0->w;
	btn4->h=btnclick0->h;
	
}
bool sourisSurbtn(SDL_Rect btn, SDL_Event event) {


	if (event.motion.x >= btn.x && event.motion.x <= btn.x+btn.w && 
	event.motion.y >=btn.y && event.motion.y <= btn.y + btn.h) {
		return true;
	}
	else {
		return false;
	}
	}
	
void changetexture(SDL_Rect btn1, SDL_Rect btn2, SDL_Rect btn3, SDL_Rect btn4 , SDL_Event event, 
SDL_Surface * play0,
SDL_Surface * play1,
SDL_Surface * opts0,
SDL_Surface * opts1,
SDL_Surface * credit0,
SDL_Surface * credit1,
SDL_Surface * quit0,
SDL_Surface * quit1,
SDL_Surface *ecran) {

	if (sourisSurbtn(btn1,event)) {
		SDL_BlitSurface(play1, NULL, ecran, &btn1);
	} else {
		SDL_BlitSurface(play0, NULL, ecran, &btn1); 
	}
	//
	
	if (sourisSurbtn(btn2,event)) {
		SDL_BlitSurface(opts1, NULL, ecran, &btn2);
	} else {	
		SDL_BlitSurface(opts0, NULL, ecran, &btn2); }
	//
	
	if (sourisSurbtn(btn3,event)) {
		SDL_BlitSurface(credit1, NULL, ecran, &btn3);
	} else {
		SDL_BlitSurface(credit0, NULL, ecran, &btn3); 
	}
	//
	if (sourisSurbtn(btn4,event)) {
		SDL_BlitSurface(quit1, NULL, ecran, &btn4);
	} 
	else {
		SDL_BlitSurface(quit0, NULL, ecran, &btn4); 
	}
	//
		

}

void loadbtns(SDL_Surface **play0, SDL_Surface **play1 , SDL_Surface **opts0, SDL_Surface **opts1, SDL_Surface **credit0, SDL_Surface **credit1, SDL_Surface **quit0 , SDL_Surface **quit1) {
	*play0=IMG_Load("for ts/play_non.png");
	*play1=IMG_Load("for ts/play_hov.png");
	if ( *play1==NULL || *play0==NULL ) {
		printf("ERROR LOADING PLAY \n");
	}
	*opts0= IMG_Load("for ts/opt_non.png");
	*opts1=IMG_Load("for ts/opt_hov.png");
	if (*opts0==NULL || *opts1==NULL) {
		printf("ERROR LOADING OPTS \n");
	}
	*credit0=IMG_Load("for ts/credits_non.png");
	*credit1=IMG_Load("for ts/credits_hov.png");
	if (*credit0==NULL || *credit1==NULL){
		printf("ERROR LOADING CREDIT\n");
	}
	*quit0=IMG_Load("for ts/quit_non.png");
	*quit1=IMG_Load("for ts/quit_hov.png");
	if (*quit0==NULL || *quit1==NULL) {
		printf("ERORR LOADING QUIT\n");
	}

}

void loadlevel1(SDL_Surface *lvlback , SDL_Surface *ecran , SDL_Rect posback) {
	SDL_Surface *surftxt;
	SDL_Rect postxt;
	TTF_Font *font;
	SDL_Color txtcolor;

	if ( TTF_Init() !=0 ) {
		printf("ERROR INITILIZING TEXT \n");
	}
	postxt.x=829;
	postxt.y=100;
	txtcolor.r=255;
	txtcolor.g=255;
	txtcolor.b=255;
	font=TTF_OpenFont("CFGlitchCity-Regular.ttf",50);
	if (font ==NULL) {
		printf("Error loading font\n");
	}
	surftxt=TTF_RenderText_Solid(font,"YUMATECH",txtcolor);
	
	lvlback=IMG_Load("test.png"); // taswira lezm tkoun 1920*1080 
	//sonbref=Mix_LoadMUS("testlvl1.mp3");
	if (lvlback==NULL) {
		printf("ERORR LOADING TEST \n");
	} 
	else {
	 
		
		printf("LEVEL 1 \n");
		posback.x=0;
		posback.y=0;
		posback.h=lvlback->h;
		posback.w=lvlback->w;
		SDL_BlitSurface (lvlback,NULL,ecran,&posback);
		SDL_BlitSurface(surftxt,NULL,ecran,&postxt);
		//Mix_PlayMusic(sonbref,0);
		}
}

void loadtext(char text[] , char cheminfont[], int taille , int indcouleur, int x , int y , SDL_Surface *ecran) { // 1 red , 2 green , 3 blue , 0 white , -1 black 
	SDL_Surface *txtsurf;
	SDL_Rect postxtEcran;
	TTF_Font *font;
	SDL_Color txtcolor;
	 switch(indcouleur) {
	 	case 1:
	 	txtcolor.r=255;
	 	txtcolor.g=0;
	 	txtcolor.b=0;
	 	break;
	 	case 2:
	 	txtcolor.r =0;
	 	txtcolor.g=255;
	 	txtcolor.b=0;
	 	break;
	 	case 3:
	 	txtcolor.r=0;
	 	txtcolor.g=0;
	 	txtcolor.b=255;
	 	break;
	 	case 0:
	 	txtcolor.r=255;
	 	txtcolor.g=255;
	 	txtcolor.b=255;
	 	break;
	 	case -1:
	 	txtcolor.r=0;
	 	txtcolor.g=0;
	 	txtcolor.b=0;
	 	break;
	 }
	 postxtEcran.x=x;
	 postxtEcran.y=y;
	 font = TTF_OpenFont(cheminfont,taille);
	 if ( font ==NULL) {
	 	printf("ERROR LOADING FONT\n");
	 }
	 txtsurf=TTF_RenderText_Solid(font,text,txtcolor);
	 if (txtsurf==NULL) {
	 	printf("ERROR LOADING TEXT\n");
	 }
	 
	 SDL_BlitSurface(txtsurf,NULL,ecran,&postxtEcran);
	 
	
}
	
	
Button* loadoptions(SDL_Surface *ecran, SDL_Surface *backg, SDL_Rect posopt) {
    Button *btn = malloc(sizeof(Button) * 8); // allocation lel tableau
    if (btn == NULL) {
        printf("ERROR D'ALLOCATION \n");
        return NULL;
    }

    // initialize lkol fl NULL
    for (int i = 0; i < 8; i++) {
        btn[i].img[0] = NULL;
        btn[i].img[1] = NULL;
    }

    backg = IMG_Load("ts_opt/op1.png");
    if (backg == NULL) {
        printf("ERROR LOADING OPTIONS BACKGROUND \n");
        free(btn);
        return NULL;
    } else {
        printf("Background loaded successfully\n");
        posopt.x = 0;
        posopt.y = 0;
        posopt.w = backg->w;
        posopt.h = backg->h;
        SDL_BlitSurface(backg, NULL, ecran, &posopt);
    }

    //N7ELLOU TSAWR
    btn[0].img[0]=IMG_Load("ts_opt/on.png");
    btn[0].img[1] = IMG_Load("ts_opt/off.png");
    if (btn[0].img[1] == NULL) {
        printf("ERROR LOADING IMAGE 1\n");
    } else {
        printf("SUCCESS\n");
    }
printf("OKay \n");
		btn[1].img[0]=IMG_Load("ts_opt/foo_on.png");
		btn[1].img[1]=IMG_Load("ts_opt/foo.png");
			if ( btn[1].img[1] ==NULL || btn[1].img[0]==NULL) {
				printf("ERROR 2");
			}else {
				printf("SUCCES ");
			}
		
				printf("OKay \n");
		btn[4].img[0]=IMG_Load("ts_opt/full_non_hov.png");
		btn[4].img[1]=IMG_Load("ts_opt/full1.png");
			if ( btn[4].img[1]==NULL) {
				printf("ERROR 3");
			}else {
				printf("SUCCES ");
			}
				printf("OKay \n");
		btn[5].img[0]=IMG_Load("ts_opt/win_nonhov.png");
		btn[5].img[1]=IMG_Load("ts_opt/win1.png");
			if ( btn[5].img[1]==NULL) {
				printf("ERROR 4");
			}else {
				printf("SUCCES ");
			}
		
				printf("OKay \n");
		btn[6].img[0]=IMG_Load("ts_opt/4.png");
			if ( btn[6].img[0]==NULL) {
				printf("ERROR 5");
			}else {
				printf("SUCCES ");
			}
			printf("OKay \n");
			
		// initialisation des positions des boutons : 
		
		btn[0].pos.x=1327; // MUSIC OFF/ on
		btn[0].pos.y=407;
		btn[0].pos.w=btn[0].img[1]->w;
		btn[0].pos.h=btn[0].img[1]->h;
				printf("OKay \n");
		btn[1].pos.x=1327; // SFX OFF OU ON
		btn[1].pos.y=575;
			printf("OKay \n");
		btn[1].pos.w=btn[1].img[1]->w;
		btn[1].pos.h=btn[1].img[1]->h;
			printf("OKay \n");
		btn[2].pos.x=1335; // Flech droite mta3 el sout
		btn[2].pos.y=713;
		btn[2].pos.w=80;
		btn[2].pos.h=80;	
			printf("OKay \n");
		btn[3].pos.x=591;
		btn[3].pos.y=713; // fleche gauche mta3 el sout
		btn[3].pos.w=80;
		btn[3].pos.h=80;
			printf("OKay \n");
		
		btn[4].pos.x=375; // button fullscreen
		btn[4].pos.y=834;
		btn[4].pos.w=btn[4].img[1]->w;
		btn[4].pos.h=btn[4].img[1]->h;
		printf("%d\t %d\t %d\t %d\t ",btn[4].pos.w,btn[4].pos.h,btn[4].pos.x,btn[4].pos.y);
			printf("OKay \n");
		btn[5].pos.x=1000; // button windowed
		btn[5].pos.y=834;
		btn[5].pos.w=btn[5].img[1]->w;
		btn[5].pos.h=btn[5].img[1]->h;
			printf("OKay \n");
		btn[6].pos.x=621; // el slider mt3 el sout
		btn[6].pos.y=718;
		btn[6].pos.w=btn[6].img[0]->w;
		btn[6].pos.h=btn[6].img[0]->h;
			printf("OKay \n");

   
    return btn; // Return the array of buttons
}

Button* slider() {
int i;
	Button* tabs;
	tabs=malloc(4*sizeof(Button));
	for (i=0; i <4; i++) {
		tabs[i].img[0]=NULL;
	}
	
	tabs[0].img[0]=IMG_Load("ts_opt/1.png");
	tabs[1].img[0]=IMG_Load("ts_opt/2.png");
	tabs[2].img[0]=IMG_Load("ts_opt/3.png");
	tabs[3].img[0]=IMG_Load("ts_opt/4.png");
	
return tabs;
}

/*void loadoptions(SDL_Surface *ecran, SDL_Surface * backg, SDL_Rect posopt) {
	SDL_Event even;
	int i,compt; bool test=true;
	compt =1;
	int son=0;
	Button btn[8];
	for (i=0; i<8;i++) {
		btn[i].img[0]=NULL;
		btn[i].img[1]=NULL;
	}
	backg=IMG_Load("ts_opt/op1.png");

	if ( backg==NULL) {
		printf("ERROR LOADING OPTIONS BACKGROUND \n"); 
	} else {
		printf("OKay \n");
		posopt.x=0;
		posopt.y=0;
		posopt.w=backg->w;
		posopt.h=backg->h;
		SDL_BlitSurface(backg,NULL,ecran,&posopt);
		btn[0].img[1]=IMG_Load("ts_opt/off.png");
			if (btn[0].img[1]==NULL) {
				printf("ERREUR 1");
			} else {
				printf("SUCCES ");
			}
				printf("OKay \n");
		btn[1].img[1]=IMG_Load("ts_opt/foo.png");
			if ( btn[1].img[1] ==NULL) {
				printf("ERROR 2");
			}else {
				printf("SUCCES ");
			}
				printf("OKay \n");
		btn[4].img[1]=IMG_Load("ts_opt/full1.png");
			if ( btn[4].img[1]==NULL) {
				printf("ERROR 3");
			}else {
				printf("SUCCES ");
			}
				printf("OKay \n");
		btn[5].img[1]=IMG_Load("ts_opt/win1.png");
			if ( btn[5].img[1]==NULL) {
				printf("ERROR 4");
			}else {
				printf("SUCCES ");
			}
				printf("OKay \n");
		btn[6].img[0]=IMG_Load("ts_opt/4.png");
			if ( btn[6].img[0]==NULL) {
				printf("ERROR 5");
			}else {
				printf("SUCCES ");
			}
			printf("OKay \n");
			
		// initialisation des positions des boutons : 
		
		btn[0].pos.x=1118; // MUSIC OFF/ on
		btn[0].pos.y=416;
		btn[0].pos.w=btn[0].img[1]->w;
		btn[0].pos.h=btn[0].img[1]->h;
				printf("OKay \n");
		btn[1].pos.x=1118; // SFX OFF OU ON
		btn[1].pos.y=987;
			printf("OKay \n");
		btn[1].pos.w=btn[1].img[1]->w;
		btn[1].pos.h=btn[1].img[1]->h;
			printf("OKay \n");
		btn[2].pos.x=1335; // Flech droite mta3 el sout
		btn[2].pos.y=713;
		btn[2].pos.w=80;
		btn[2].pos.h=80;	
			printf("OKay \n");
		btn[3].pos.x=591;
		btn[3].pos.y=713; // fleche gauche mta3 el sout
		btn[3].pos.w=80;
		btn[3].pos.h=80;
			printf("OKay \n");
		
		btn[4].pos.x=492; // button fullscreen
		btn[4].pos.y=834;
		btn[4].pos.w=btn[4].img[1]->w;
		btn[4].pos.h=btn[4].img[1]->h;
		printf("%d\t %d\t %d\t %d\t ",btn[4].pos.w,btn[4].pos.h,btn[4].pos.x,btn[4].pos.y);
			printf("OKay \n");
		btn[5].pos.x=1129; // button windowed
		btn[5].pos.y=834;
		btn[5].pos.w=btn[5].img[1]->w;
		btn[5].pos.h=btn[5].img[1]->h;
			printf("OKay \n");
		btn[6].pos.x=621; // el slider mt3 el sout
		btn[6].pos.y=718;
		btn[6].pos.w=btn[6].img[0]->w;
		btn[6].pos.h=btn[6].img[0]->h;
			printf("OKay \n");


			printf(" POLLING EVENTS\n");
			
		switch (even.type) {
			printf("EVENT ACCESSED \n");
			
			case SDL_MOUSEMOTION:

			printf("ACCESSED MOUSE MOTION \n");
			
		if  (even.motion.x >= 492 && even.motion.x <= 492+btn[4].pos.w && 
	even.motion.y >=834 && even.motion.y <= 834 + btn[6].pos.h) {
			printf("OKay  in pos\n");
			SDL_BlitSurface(btn[4].img[1],NULL,ecran,&btn[4].pos);
		} else {
			printf("SOURIS NOT IN POS \n");
		}
		
			printf("OKay \n");
		if (sourisSurbtn(btn[5].pos,even)&& btn[5].img[1]!= NULL) {
			printf("OKay  in pos 2\n");
			SDL_BlitSurface(btn[5].img[1],NULL,ecran,&btn[5].pos);
		}
		
			printf("OKay \n");
			break;
			case SDL_MOUSEBUTTONDOWN:
			// TEST SUR CLICK : 
       	 		if (even.button.button == SDL_BUTTON_LEFT) {
       	 		printf("click");
       	 		
				if (even.motion.x >= 492 && even.motion.x <= 492+btn[6].pos.w && 
	even.motion.y >=718 && even.motion.y <= 718 + btn[6].pos.h) {
				printf("Music off\n");
				
					SDL_BlitSurface(btn[0].img[1],NULL,ecran,&btn[0].pos);
					
					
					} 
					else if ( sourisSurbtn(btn[1].pos,even)) {
					printf("SFX OFF\n");
						SDL_BlitSurface(btn[1].img[1],NULL,ecran,&btn[1].pos);
						
					}
					else if (sourisSurbtn(btn[2].pos,even)) {
					printf("SON ++\n");
					
						if ( compt<4 &&  son <=100) {
							compt++;
							son +=25;
						} 
							
					}
					else if (sourisSurbtn(btn[3].pos,even)) {
					printf("SON --\n");
					
						if ( compt >= 4 && son >=0) {
							compt--;
							son-=25;
					}
					}
					else if (sourisSurbtn(btn[4].pos,even)) {
						//fullscreen
						
						printf("FULLSCREEN\n");
					}
					else if (sourisSurbtn(btn[5].pos,even)) {
						test = false;
						//windowed
						printf("WINDOWED\n");
					
					}
					break;
					
					
}
}

	printf("OKay \n");



		

}
}

/*void detectbtnopt(SDL_Rect pos1, SDL_Rect pos2, SDL_Rect fg, SDL_Rect fd , SDL_Rect win, SDL_Rect full, SDL_Event event , SDL_Surface *bn1 , SDL_Surface * bn2, SDL_Surface *bn3 , SDL_Surface * bn4 , SDL_Surface * bn5 , SDL_Surface *bn6, SDL_Surface *ecran ) {

	if (event.motion.x >= pos1.x && event.motion.x <= pos1.x+pos1.w && 
	event.motion.y >=pos1.y && event.motion.y <= pos1.y + pos1.h) {
		SDL_BlitSurface(bn1,NULL,ecran,&pos1);
	





/*void hover(SDL_Rect posbtn, char chemin1[100] , char chemin0[100], SDL_Event event,SDL_Surface *ecran) {
	SDL_Surface *hov,*nonhov;
	hov = IMG_Load(chemin1);
	nonhov=IMG_Load(chemin0);
	
	if (sourisSurbtn(posbtn,event) ==true ) {
		SDL_BlitSurface(hov,NULL,ecran,&posbtn);
	}else {
		SDL_BlitSurface(nonhov,NULL,ecran,&posbtn);
	}
}*/


bool backspace(SDL_Event event ) {
	return (event.key.keysym.sym == SDLK_BACKSPACE);
}



SDL_Surface ** initAnimBack() {
		SDL_Surface * * tab;
		tab=malloc( 3 * sizeof(SDL_Surface));
		tab[0]= IMG_Load("for ts/anim1.png");
		tab[1]=IMG_Load("for ts/anim2.png");
		tab[2]=IMG_Load("for ts/anim3.png");
		
		int i;
		for ( i=0 ; i <3; i++) {
			if (tab[i]==NULL) {
				printf("ERROR LOADING ANIM %d ",i);
				free(tab);
			}
		}
	return tab;
}
	
bool sauvegarde_score(Uint32 score,const char *filename) {
	FILE* fich=NULL;
	fich=fopen(filename,"a+");
		if (fich==NULL) {
			printf("ERROR LOADING SCORE FILE (SAUVEGARDE SCORE) \n");
			return false;
		}else {
			fprintf(fich,"%u\n",score);
			fclose(fich);
			return true;
		}
}

Uint32 best_score(const char *filename) {
	FILE* fich=NULL;
	fich = fopen(filename,"r");
	Uint32 high_score=0,current_score;
	
	
	if ( fich==NULL) {
		printf("ERROR LOADING SCORE FILE (HIGHEST SCORE) \n");
		return 0;
		} else {
			while (fscanf(fich,"%u\n",&current_score) == 1 ) {
					if ( current_score > high_score) {
						high_score=current_score;
					}
				}
			fclose(fich);
			return high_score;
		}
	}
	
				
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
			



