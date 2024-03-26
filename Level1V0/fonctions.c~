#include "header.h"


Person  InitPerso(Person  player ) {
	int i;
	
	
	for (i=0;i<15;i++) {
		player.texture[i]=NULL;
	}
	
	player.texture[0]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/1.png");
	player.texture[1]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/2.png");
	player.texture[2]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/3.png");
	player.texture[3]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/4.png");
	player.texture[4]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/5.png");
	player.texture[5]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/L1.png");
	player.texture[6]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/L2.png");
	player.texture[7]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/L3.png");
	player.texture[8]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/L4.png");
	player.texture[9]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/L5.png");
	player.texture[10]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/jump 1.png");
	player.texture[11]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/jump2.png");
	player.texture[12]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/jump1L.png");
	player.texture[13]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/jump2L.png");
	player.texture[14]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/dmg.png");

	
	
	
	
	for (i=0;i<15;i++) {
		if (player.texture[i]==NULL) {
			printf("ERREUR LODING IMAGE n %d\n",i);
		} else {
			printf("SUCCES %d " , i);
		}
		
	}
	
	
	
	player.num_hearts=3;
	player.textcourant=0;
	player.acc = -0.1;
	
	for (i=0 ; i < player.num_hearts ; i++) {
		player.vie[i]=NULL;
	}
		
	player.vie[0]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/h1.png");
	player.vie[1]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/h2.png");
	player.vie[2]=IMG_Load("/home/aziz/Desktop/Integration (copy)/anim perso test/h3.png");
	
	for ( i =0 ; i<player.num_hearts ; i++) {
		if ( player.vie[i]==NULL) {
			printf("ERROR LOADING VIE n %d\n",i);
		}
	}
	
	player.posinit.x = 200; // a changer
   	player.posinit.y = ground;
   	
    	player.posvie.x=1596;
    	player.posvie.y=50;
	
	//player.dmg=IMG_Load("/home/aziz/Desktop/Integration/anim perso test/dmg.png");
	
    	
		


    	return player;
    	
		
}
	
void afficherPerso(Person * player, SDL_Surface * ecran) {
	SDL_BlitSurface(player->texture[player->textcourant],NULL,ecran,&player->posinit);
	SDL_BlitSurface(player->vie[player->num_hearts-1],NULL,ecran,&player->posvie);
	
}



void deplacerPerso(Person * player, int direction , int *  currenttext) { // 1 right -1 left 0 up 5 down 
	static Uint32 DernierImage = 0; // Duree mta3 e5r image + static besh matetbadlsh fl main 
	Uint32 TempsCourant = SDL_GetTicks(); // temps courant 
	Uint32 TempsPasse = TempsCourant - DernierImage;
	
	
if ( TempsPasse >= 70 || DernierImage == 0) {
	DernierImage=TempsCourant;
	
	switch (direction) {
		case 1 :
		player->posinit.x+=20;
		player->textcourant++;
			*currenttext=player->textcourant;
			if ( player->textcourant > 4) {
				player->textcourant =0;
			}
			
		break;
		case -1 :
		player->posinit.x-=8;
		player->textcourant++;
			*currenttext=player->textcourant;
			if ( player->textcourant >=9 || player->textcourant <= 4) {
				player->textcourant=5;
			}
			 
		break;
		case 0 :
		player->posinit.y-=2;
		break;
		case 5 :
		player->posinit.y+=3;
		break;
	}
}
}





void jumpPerso ( Person * player , int direction) { 
static double a = -0.01; 
    static int c = 220;     

    

    static Uint32 lastTime = 0;
    Uint32 currentTime = SDL_GetTicks();
    double dt = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;

	
    player->posinit.y = (int) (a * player->acc * player->acc + c);


    player->acc += 0.1; 
 
        switch (direction) {
        case 1:
            player->posinit.x += -a * player->acc * player->acc + c ;
            break;
        case -1:
            player->posinit.x -= -a * player->acc * player->acc + c ;
            break;
    }
    
}

////////////// TEST POUR AUTRE TACHE /////////////- 	
void afficher_score(int score ,  SDL_Rect * PosTxt, SDL_Surface * *SurfText , TTF_Font * font , SDL_Color txtCoul) {
		
		
		PosTxt->x=20;
		PosTxt->y=20;
		PosTxt->w=50;
		PosTxt->h=20;
		
		txtCoul.r=255;
		txtCoul.g=0;
		txtCoul.b=0;
		char Cscore[10];
		sprintf(Cscore,"%d",score);
		*SurfText=TTF_RenderText_Solid(font,Cscore,txtCoul);
}

	
	


	
	
	
	

