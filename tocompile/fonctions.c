#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>
#include <SDL/SDL_ttf.h>
#include "perso.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

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
    } 

		btn[1].img[0]=IMG_Load("ts_opt/foo_on.png");
		btn[1].img[1]=IMG_Load("ts_opt/foo.png");
			if ( btn[1].img[1] ==NULL || btn[1].img[0]==NULL) {
				printf("ERROR 2");
			}
		

		btn[4].img[0]=IMG_Load("ts_opt/full_non_hov.png");
		btn[4].img[1]=IMG_Load("ts_opt/full1.png");
			if ( btn[4].img[1]==NULL) {
				printf("ERROR 3");
			}

		btn[5].img[0]=IMG_Load("ts_opt/win_nonhov.png");
		btn[5].img[1]=IMG_Load("ts_opt/win1.png");
			if ( btn[5].img[1]==NULL) {
				printf("ERROR 4");
			}
		

		btn[6].img[0]=IMG_Load("ts_opt/4.png");
			if ( btn[6].img[0]==NULL) {
				printf("ERROR 5");
			}
			
		// initialisation des positions des boutons : 
		
		btn[0].pos.x=1327; // MUSIC OFF/ on
		btn[0].pos.y=407;
		btn[0].pos.w=btn[0].img[1]->w;
		btn[0].pos.h=btn[0].img[1]->h;

		btn[1].pos.x=1327; // SFX OFF OU ON
		btn[1].pos.y=575;

		btn[1].pos.w=btn[1].img[1]->w;
		btn[1].pos.h=btn[1].img[1]->h;

		btn[2].pos.x=1335; // Flech droite mta3 el sout
		btn[2].pos.y=713;
		btn[2].pos.w=80;
		btn[2].pos.h=80;	

		btn[3].pos.x=591;
		btn[3].pos.y=713; // fleche gauche mta3 el sout
		btn[3].pos.w=80;
		btn[3].pos.h=80;

		
		btn[4].pos.x=375; // button fullscreen
		btn[4].pos.y=834;
		btn[4].pos.w=btn[4].img[1]->w;
		btn[4].pos.h=btn[4].img[1]->h;
		printf("%d\t %d\t %d\t %d\t ",btn[4].pos.w,btn[4].pos.h,btn[4].pos.x,btn[4].pos.y);

		btn[5].pos.x=1000; // button windowed
		btn[5].pos.y=834;
		btn[5].pos.w=btn[5].img[1]->w;
		btn[5].pos.h=btn[5].img[1]->h;

		btn[6].pos.x=621; // el slider mt3 el sout
		btn[6].pos.y=718;
		btn[6].pos.w=btn[6].img[0]->w;
		btn[6].pos.h=btn[6].img[0]->h;


   
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

int best_score(const char *filename) {
    FILE* fich = fopen(filename, "r");
    if (fich == NULL) {
        printf("ERROR LOADING SCORE FILE (HIGHEST SCORE)\n");
        return 0;
    }

    int high_score = 0, current_score;
    while (fscanf(fich, "%d\n", &current_score) == 1) {
        if (current_score > high_score) {
            high_score = current_score;
        }
    }

    fclose(fich);
    return high_score;
}

				
void show_high_score(SDL_Surface *ecran) {
    int score = best_score("score.txt");

    char high[50];
    sprintf(high, "Best Score: %d", score);

    TTF_Font *font = TTF_OpenFont("FOnt.ttf", 50);
    if (!font) {
        printf("ERROR LOADING FONT FOR HIGH SCORE: %s\n", TTF_GetError());
        return;
    }

    SDL_Color txtcolor = {255,255,255};
    SDL_Surface *SurfText = TTF_RenderText_Solid(font, high, txtcolor);
    if (SurfText == NULL) {
        printf("ERROR LOADING TEXT SURFACE FOR HIGHEST SCORE: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect postxtEcran = {1409,948, 0, 0};
    SDL_BlitSurface(SurfText, NULL, ecran, &postxtEcran);
    SDL_Flip(ecran);

    SDL_FreeSurface(SurfText);
    TTF_CloseFont(font);
}




void Pass_to_Next_Level(SDL_Surface *Loading[3], SDL_Surface *ecran, Mix_Chunk **SFX, Person *p, Background *TabBack[3], int indlvl) {
    // Load images
    Loading[0] = IMG_Load("for ts/lo.png");
    Loading[1] = IMG_Load("for ts/lod2.png");
    Loading[2] = IMG_Load("for ts/lod3.png");

    // Check for errors in loading images
    if (!Loading[0] || !Loading[1] || !Loading[2]) {
        printf("ERROR LOADING NEXT LEVEL TRANSITION IMAGES\n");
        // Clean up resources and return
        for (int i = 0; i < 3; i++) {
            if (Loading[i]) {
                SDL_FreeSurface(Loading[i]);
                Loading[i] = NULL;
            }
        }
        return;
    }

    // Load audio
    *SFX = Mix_LoadWAV("nxtlvlSFX.wav");
    // Check for errors in loading audio
    if (!(*SFX)) {
        printf("ERROR LOADING NEXT LEVEL TRANSITION AUDIO\n");
        // Clean up resources and return
        for (int i = 0; i < 3; i++) {
            if (Loading[i]) {
                SDL_FreeSurface(Loading[i]);
                Loading[i] = NULL;
            }
        }
        return;
    }

    // Play audio
    Mix_PlayChannel(-1, *SFX, 0);


    for (int i = 0; i < 32; i++) {
        SDL_BlitSurface(Loading[i % 3], NULL, ecran, NULL);
        SDL_Flip(ecran);
        SDL_Delay(90);
    }


    p->num_hearts = 3;
    p->posinit.x = 200;
    p->posinit.y = 500;


    if (indlvl >= 1 && indlvl <= 3) {
        TabBack[indlvl - 1]->camera_pos.x = 0;
        TabBack[indlvl - 1]->camera_pos.y = 0;
        TabBack[indlvl - 1]->camera_pos.w = ecran->w;
        TabBack[indlvl - 1]->camera_pos.h = ecran->h;
    }


    SDL_Delay(1500);


   
}

void InitCutscene( SDL_Surface ** Tab ) {
    Tab[0]=IMG_Load("p1.png");
    Tab[1]=IMG_Load("p2.png");
    Tab[2]=IMG_Load("p3.png");
    Tab[3]=IMG_Load("p4.png");

        for ( int i = 0 ; i< 4 ; i++) {
                if(Tab[i] == NULL) {
                    printf("Error loading Cutscene image n %d\n",i);
                }

        }

}


void handleGameLoss(SDL_Surface *ecran, bool *mainmenu, Mix_Music *MenuMusic) {
    SDL_Surface *pic = IMG_Load("pic.png");
    if (!pic) {
        printf("ERROR LOADING GAME LOSS PICTURE");
        return;
    }

    SDL_Surface *ThankYou = IMG_Load("thank_you_img.png");
    if (!ThankYou) {
        printf("ERROR LOADING THANK YOU \n");
        return;
    }

    Mix_Chunk *lossSFX = Mix_LoadWAV("gameLossSFX.wav");
    if (!lossSFX) {
        printf("ERROR LOADING GAME LOSS SFX");
        return;
    }

    SDL_BlitSurface(pic, NULL, ecran, NULL);
    SDL_Flip(ecran);
    Mix_HaltMusic();
    Mix_PlayChannel(-1, lossSFX, 0);

    Uint32 start_time = SDL_GetTicks();

    while (SDL_GetTicks() - start_time < 6000) {
    }

    SDL_BlitSurface(ThankYou, NULL, ecran, NULL);
    SDL_Flip(ecran);
    start_time = SDL_GetTicks();

    while (SDL_GetTicks() - start_time < 6000) {
    }
    Mix_ResumeMusic();
    Mix_PlayMusic(MenuMusic, -1);

    *mainmenu = true;
}


void handleGameMode(int * num_j ,SDL_Surface* ecran ) {
	SDL_Surface * ChooseMode = IMG_Load("selec_game_mode.png");
	SDL_Surface * Story0=IMG_Load("for ts/story_mode_0.png");
	SDL_Surface *Story1=IMG_Load("for ts/story_1.png");
	SDL_Surface *MP0=IMG_Load("for ts/mp_0.png");
	SDL_Surface *MP1=IMG_Load("for ts/mp1.png");


	SDL_Rect Story_Mode={450,450,Story0->w,Story0->h};
	SDL_Rect Multiplayer_Mode={1050,450,MP0->w,MP0->h};
	bool PosSouris;
		if ( !ChooseMode || !Story0 || !Story1 || !MP0 || ! MP1  ) {
				printf("ERROR CHOOSING MODE \n");
		}
	 bool quit = false;
    SDL_Event event;
    SDL_BlitSurface(ChooseMode,NULL,ecran,NULL);
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEMOTION) {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;

                if (mouseX >= Story_Mode.x && mouseX <= Story_Mode.x + Story_Mode.w &&
                    mouseY >= Story_Mode.y && mouseY <= Story_Mode.y + Story_Mode.h) {
                    SDL_BlitSurface(Story1, NULL, ecran, &Story_Mode);
                } else {
                    SDL_BlitSurface(Story0, NULL, ecran, &Story_Mode);
                }

                if (mouseX >= Multiplayer_Mode.x && mouseX <= Multiplayer_Mode.x + Multiplayer_Mode.w &&
                    mouseY >= Multiplayer_Mode.y && mouseY <= Multiplayer_Mode.y + Multiplayer_Mode.h) {
                    SDL_BlitSurface(MP1, NULL, ecran, &Multiplayer_Mode);
                } else {
                    SDL_BlitSurface(MP0, NULL, ecran, &Multiplayer_Mode);
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                if (mouseX >= Story_Mode.x && mouseX <= Story_Mode.x + Story_Mode.w &&
                    mouseY >= Story_Mode.y && mouseY <= Story_Mode.y + Story_Mode.h) {
                    *num_j = 1;
                    quit = true; 
                }
                
                if (mouseX >= Multiplayer_Mode.x && mouseX <= Multiplayer_Mode.x + Multiplayer_Mode.w &&
                    mouseY >= Multiplayer_Mode.y && mouseY <= Multiplayer_Mode.y + Multiplayer_Mode.h) {
                    *num_j = 2;
                    quit = true; 
                }
            }
        }


        SDL_Flip(ecran);
    }
SDL_FreeSurface(ChooseMode);
SDL_FreeSurface(Story0);
SDL_FreeSurface(Story1);
SDL_FreeSurface(MP0);
SDL_FreeSurface(MP1);
}
bool SAVE_SCORE_MP(int scoreP1 , int scoreP2 ,const char *filename) {
	FILE* fich=NULL;
	fich=fopen(filename,"a+");
		if (fich==NULL) {
			printf("ERROR LOADING SCORE FILE (SAUVEGARDE SCORE) \n");
			return false;
		}else {
			fprintf(fich,"%d\t%d\n",scoreP1,scoreP2);
			fclose(fich);
			return true;
		}
}
void Blit_Top_Scores(const char *filename, int *scoresP1, int *scoresP2) {
    FILE *fich = fopen(filename, "r");
    if (fich == NULL) {
        printf("ERROR OPENING SCORE FILE\n");
        return;
    }

    // Initialize scores arrays
    for (int i = 0; i < 3; i++) {
        scoresP1[i] = 0;
        scoresP2[i] = 0;
    }

    int scoreP1, scoreP2;
    int i;

    while (fscanf(fich, "%d %d", &scoreP1, &scoreP2) != EOF) {
        // Update top 3 scores for player 1
        for (i = 0; i < 3; i++) {
            if (scoreP1 > scoresP1[i]) {
                // Shift scores down to make room for the new score
                for (int j = 2; j > i; j--) {
                    scoresP1[j] = scoresP1[j - 1];
                }
                scoresP1[i] = scoreP1;
                break;
            }
        }

        // Update top 3 scores for player 2
        for (i = 0; i < 3; i++) {
            if (scoreP2 > scoresP2[i]) {
                // Shift scores down to make room for the new score
                for (int j = 2; j > i; j--) {
                    scoresP2[j] = scoresP2[j - 1];
                }
                scoresP2[i] = scoreP2;
                break;
            }
        }
    }

    fclose(fich);
}

void High_SCORE_MP(SDL_Surface *ecran, SDL_Surface *SurfText, int *scores, int num_scores, int start_x, int start_y) {
    TTF_Font *font;
    SDL_Color txtcolor;
    SDL_Rect postxtEcran;
    postxtEcran.x = start_x;
    postxtEcran.y = start_y;
    txtcolor.r = 255;
    txtcolor.g = 255;
    txtcolor.b = 255;
    font = TTF_OpenFont("FOnt.ttf", 50);
    if (!font) {
        printf("ERROR LOADING FONT FOR HIGH SCORE\n");
        return;
    }

    for (int i = 0; i < num_scores; i++) {
        char high[20];
        sprintf(high, "Score Rank %d: %d", i + 1, scores[i]);
        SurfText = TTF_RenderText_Solid(font, high, txtcolor);
        if (SurfText == NULL) {
            printf("ERROR LOADING TEXT SURFACE FOR HIGH SCORE\n");
            continue;
        }
        SDL_BlitSurface(SurfText, NULL, ecran, &postxtEcran);
        postxtEcran.y += 250; // Adjust the y position for the next score
        SDL_FreeSurface(SurfText); // Free the surface after blitting
    }

    TTF_CloseFont(font);
}

int FinalCutscene(SDL_Surface *ecran) {
    SDL_Surface *Tab[3];
    Tab[0] = IMG_Load("Frame1.png");
    Tab[1] = IMG_Load("Frame2.png");
    Tab[2] = IMG_Load("Frame3.png");

    if (!Tab[0] || !Tab[1] || !Tab[2]) {
        printf("Error loading final cutscene images\n");
        return -1;
    }

    SDL_Surface *ThankYou = IMG_Load("thank_you_img.png");
    if (!ThankYou) {
        printf("ERROR LOADING THANK YOU\n");
        for (int i = 0; i < 3; ++i) {
            if (Tab[i]) SDL_FreeSurface(Tab[i]);
        }
        return -1;
    }

    Uint32 frame_duration = 500; 
    Uint32 start_time;

    for (int i = 0; i < 10; ++i) {
        start_time = SDL_GetTicks();
        SDL_BlitSurface(Tab[i % 2], NULL, ecran, NULL);
        SDL_Flip(ecran);

        while (SDL_GetTicks() - start_time < frame_duration) {
            SDL_Delay(10); 
        }
    }

    // Display Tab[2] for 1.5 seconds
    start_time = SDL_GetTicks();
    SDL_BlitSurface(Tab[2], NULL, ecran, NULL);
    SDL_Flip(ecran);

    while (SDL_GetTicks() - start_time < 2500) {
        SDL_Delay(10); // Small delay to prevent busy-waiting
    }

    SDL_BlitSurface(ThankYou, NULL, ecran, NULL);
    SDL_Flip(ecran);

    start_time = SDL_GetTicks();
    while (SDL_GetTicks() - start_time < 2500) {
        SDL_Delay(10); 
    }

    // Clean up surfaces
    for (int i = 0; i < 3; ++i) {
        if (Tab[i]) SDL_FreeSurface(Tab[i]);
    }
    SDL_FreeSurface(ThankYou);

    return 1;
}



void handleGameWin(SDL_Surface *ecran, bool *mainmenu, Mix_Music *MenuMusic) {
    SDL_Surface *pic = IMG_Load("pic.png");
    ColorFade fade;
    initColorFade(&fade, 255, 0, 0, 0, 0, 255, 2000);
    if (!pic) {
        printf("ERROR LOADING GAME LOSS PICTURE");
        return;
    }

   

    Mix_Chunk *WinSFX = Mix_LoadWAV("gameLossSFX.wav");
    if (!WinSFX) {
        printf("ERROR LOADING GAME WIN SFX");
        return;
    }

    

    SDL_Flip(ecran);
    Mix_HaltMusic();
    Mix_PlayChannel(-1, WinSFX, 0);

    Uint32 start_time = SDL_GetTicks();

    while (SDL_GetTicks() - start_time < 3000) {
    	updateScreenColor(ecran, &fade);
    }

    SDL_Flip(ecran);
    start_time = SDL_GetTicks();
     if( FinalCutscene(ecran)!= -1 ) {  
   	

    Mix_ResumeMusic();
    Mix_PlayMusic(MenuMusic, -1);

    *mainmenu = true;
}

}


void saveGameTime(const char* filename, Uint32 gameTime) {
    FILE* file = fopen(filename, "a+");
    if (!file) {
        printf("Error opening file for writing\n");
        return;
    }

    fprintf(file, "%u\n", gameTime);

    fclose(file);
}
	
	
			
Uint32 loadGameTime(const char* filename) {
    Uint32 gameTime = 0;

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading\n");
        return 0;
    }

    fscanf(file, "%u", &gameTime);

    fclose(file);

    return gameTime;
}

Uint32 getTimeDifference(Uint32 startTime, Uint32 endTime) {
    // Calculate the difference between endTime and startTime
    return endTime - startTime;
}
void findMinMaxGameTimes(const char* filename, uint32_t* minTime, uint32_t* maxTime) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading\n");
        return;
    }

    uint32_t gameTime;
    *minTime = UINT32_MAX;
    *maxTime = 0;

    while (fscanf(file, "%u", &gameTime) == 1) {
        if (gameTime < *minTime) {
            *minTime = gameTime;
        }
        if (gameTime > *maxTime) {
            *maxTime = gameTime;
        }
    }

    fclose(file);
}


void formatTime(Uint32 milliseconds, char* formattedTime) {
    Uint32 seconds = milliseconds / 1000;
    Uint32 minutes = seconds / 60;
    Uint32 hours = minutes / 60;

    seconds %= 60;
    minutes %= 60;

    snprintf(formattedTime, 256, "%02u:%02u:%02u:%03u", hours, minutes, seconds, milliseconds % 1000);
}


void send_message(int fd, const char *message) {
    // Calculate the length of the message
    size_t message_length = strlen(message);
    
    // Allocate memory for the modified message
    char *modified_message = (char *)malloc(message_length * 2 + 3);
    if (modified_message == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    
    // Index to track the position in the modified message
    int index = 0;
    
    // Check if the message contains an asterisk at the beginning
    int has_start_asterisk = (message[0] == '*');
    // Check if the message contains an asterisk at the end
    int has_end_asterisk = (message[message_length - 1] == '*');
    
    // Add '*' at the beginning of the message if it's not already present
    if (!has_start_asterisk) {
        modified_message[index++] = '*';
    }
    
    // Copy the original message content
    strcpy(modified_message + index, message);
    index += message_length;
    
    // Add '*' at the end of the message if it's not already present
    if (!has_end_asterisk) {
        modified_message[index++] = '*';
    }
    
    // Add '\n' at the end of the message
    modified_message[index++] = '\n';
    
    // Write the modified message to the serial port
    write(fd, modified_message, index);
    
    // Free the allocated memory
    free(modified_message);
}

int read_joystick(int fd, int *x, int *y, enum ControllerPlayerCommands *command) {
    char buffer[128];
    int n = read(fd, buffer, sizeof(buffer));
    if (n > 0) {
        buffer[n] = '\0';
        sscanf(buffer, "X:%d,Y:%d", x, y);

        // Default to no command
        *command = NONE;

        // Check for specific commands in the buffer
        if (strstr(buffer,"CLK")) {
            *command = SHOOT;
            printf("CLICKED CLK\n");
        } else {
        	*command=NONE;
        }

        if (strstr(buffer, "BD")) {
        	printf("SLIDING\n");
            *command = SLIDE;
        } else {
        	*command=NOSLIDE;
        }


        if (strstr(buffer, "BL")) {
            *command = JUMP;
        } else {
        		*command=NOJUMP;
        }

        return 1;
    }
    
    return 0;
}


void draw_square(SDL_Surface* screen, int x, int y) {
	SDL_Surface * cursor=IMG_Load("/home/aziz/Desktop/Digital_Intrusion/mini_joueur.png");

    SDL_Rect square;
    square.x = x;
    square.y = y;
    square.w = 10; // Width of the square
    square.h = 10; // Height of the square

    // Fill the square with a color (white)
	    SDL_BlitSurface(cursor,NULL,screen,&square);

    // Update the screen

	    	SDL_FreeSurface(cursor);
}



void ProcessControllerEvent(SDL_Event *event, int arduino_fd, enum State currentState, SDL_Surface *ecran, int *x, int *y, char buffer[128], int *mouseX, int *mouseY) {

    // Update mouseX and mouseY based on joystick input
    *mouseX += (*x - 512) / 100; // Adjust mapping as needed
    *mouseY += (*y - 512) / 100; // Adjust mapping as needed

    // Constrain the cursor within the screen boundaries
    if (*mouseX < 0) *mouseX = 0;
    if (*mouseX > 1919) *mouseX = 1919;
    if (*mouseY < 0) *mouseY = 0;
    if (*mouseY > 1079) *mouseY = 1079;

    switch (currentState) {
        case PLAYING:
            // Add logic for the PLAYING state if necessary
            break;
        case OPTIONSMENU:
            // Add logic for the OPTIONSMENU state if necessary
            break;
        case PROFILESMENU:
            // Add logic for the PROFILESMENU state if necessary
            break;
        case MAINMENU:
            {
                // Create and push a mouse motion event
                SDL_Event mouseMotionEvent;
                mouseMotionEvent.type = SDL_MOUSEMOTION;
                mouseMotionEvent.motion.x = *mouseX;
                mouseMotionEvent.motion.y = *mouseY;
                SDL_PushEvent(&mouseMotionEvent);

                // Check for a click event in the buffer
                if (strstr(buffer, "CLK")) {
                    SDL_Event mouseClickEvent;

                    // Create and push a mouse button down event
                    mouseClickEvent.type = SDL_MOUSEBUTTONDOWN;
                    mouseClickEvent.button.button = SDL_BUTTON_LEFT;
                    mouseClickEvent.button.x = *mouseX;
                    mouseClickEvent.button.y = *mouseY;
                    SDL_PushEvent(&mouseClickEvent);

                    // Create and push a mouse button up event
                    mouseClickEvent.type = SDL_MOUSEBUTTONUP;
                    SDL_PushEvent(&mouseClickEvent);
                }
                draw_square(ecran, *mouseX, *mouseY);
            }
            break;
    }

    SDL_Flip(ecran);
}

