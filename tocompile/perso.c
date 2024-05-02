#include "perso.h"
#define BGWIDTH 3840


Person  InitPerso(Person  player ) {
	int i;
	
	
	for (i=0;i<15;i++) {
		player.texture[i]=NULL;
	}
	
	player.texture[0]=IMG_Load("anim perso test/1.png");
	player.texture[1]=IMG_Load("anim perso test/2.png");
	player.texture[2]=IMG_Load("anim perso test/3.png");
	player.texture[3]=IMG_Load("anim perso test/4.png");
	player.texture[4]=IMG_Load("anim perso test/5.png");
	player.texture[5]=IMG_Load("anim perso test/L1.png");
	player.texture[6]=IMG_Load("anim perso test/L2.png");
	player.texture[7]=IMG_Load("anim perso test/L3.png");
	player.texture[8]=IMG_Load("anim perso test/L4.png");
	player.texture[9]=IMG_Load("anim perso test/L5.png");
	player.texture[10]=IMG_Load("anim perso test/jump 1.png");
	player.texture[11]=IMG_Load("anim perso test/jump2.png");
	player.texture[12]=IMG_Load("anim perso test/jump1L.png");
	player.texture[13]=IMG_Load("anim perso test/jump2L.png");
	player.texture[14]=IMG_Load("anim perso test/dmg.png");

	
	
	
	
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
		
	player.vie[0]=IMG_Load("anim perso test/h1.png");
	player.vie[1]=IMG_Load("anim perso test/h2.png");
	player.vie[2]=IMG_Load("anim perso test/h3.png");
	
	for ( i =0 ; i<player.num_hearts ; i++) {
		if ( player.vie[i]==NULL) {
			printf("ERROR LOADING VIE n %d\n",i);
		}
	}
	
	player.posinit.x = 200; // a changer
   	player.posinit.y = ground;
   	
    	player.posvie.x=1596;
    	player.posvie.y=50;
  player.dx=20;
	
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

	
if ( TempsPasse >= 40 || DernierImage == 0) {
	DernierImage=TempsCourant;
	
	switch (direction) {
		case 1 :
		player->posinit.x+=player->dx;
		player->textcourant++;
			*currenttext=player->textcourant;
			if ( player->textcourant > 4) {
				player->textcourant =0;
			}
			
		break;
		case -1 :
		player->posinit.x-=(player->dx-10);
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
            player->posinit.x += a * player->acc * player->acc + c ;
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

///////////////////////////////////////////////////////TEST POUR COLLISION ///////////////////////////////////////////////////////////////////////////

int Collided(Person player, SDL_Rect enemyPos) { // COLLISION BOUNDING BOX

    int TolerancePiedY = 10; 
    int ToleranceTeteY = 50; 
    int ToleranceSaut=20;

    SDL_Rect playerBox = {player.posinit.x, player.posinit.y, player.posinit.w, player.posinit.h + TolerancePiedY};
    SDL_Rect enemyBox = {enemyPos.x, enemyPos.y - ToleranceTeteY, enemyPos.w, enemyPos.h + ToleranceTeteY};
    

    if ((playerBox.x + playerBox.w >= enemyBox.x) && (enemyBox.x + enemyBox.w >= playerBox.x) ) {

        if (playerBox.y + playerBox.h <= enemyBox.y && 
            playerBox.y + playerBox.h >= enemyBox.y - ToleranceSaut) {

            return 2;
        } else {

            return 1;
        }
    }

    return 0;
}

int InitES(SDL_Surface **ES, SDL_Surface **Coin,  char* cheminES, char *cheminCoin, SDL_Rect *poses , SDL_Rect * posCoin) {
    *ES = IMG_Load(cheminES);
    if (!(*ES)) {
        printf("ERROR LOADING ES \n");
        return 0; 
    }
    
    *Coin = IMG_Load(cheminCoin);
    if (!(*Coin)) {
        printf("ERROR LOADING COIN \n");
        SDL_FreeSurface(*ES); 
        return 0; 
    }

    poses->x = 1950;
    poses->y = 650;
		posCoin->x=2500;
		posCoin->y=ground+100;
		posCoin->w=(*Coin)->w;
		posCoin->h=(*Coin)->h;
		
		
    return 1; 
}

void afficherES(SDL_Surface *screen, SDL_Surface *ES, SDL_Surface *Coin, SDL_Rect poses_ES, SDL_Rect poses_Coin) {
    SDL_BlitSurface(ES, NULL, screen, &poses_ES); 
    SDL_BlitSurface(Coin, NULL, screen, &poses_Coin); 

}

void deplacerES(SDL_Rect * coin, SDL_Rect * es) {
	es->x-=10;
	coin->x-=3;
	if ( es->x == 0) {
	es->x = 1600;
	}
	if ( coin->y > 1000) {
			coin->y=ground+100;
			coin->x=2500;			
	}
}

	



double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}




int CollisionTrigo(SDL_Rect C, Person P) {
    // Determine the coordinates of the center and the radius of the circumscribed circle for the first object (C)
    int x1 = C.x + C.w / 2;
    int y1 = C.y + C.h / 2;
    int r1 = sqrt(pow(C.w / 2, 2) + pow(C.h / 2, 2));

    // Determine the coordinates of the center and the radius of the circumscribed circle for the second object (P)
    int x2 = P.posinit.x + P.posinit.w / 2;
    int y2 = P.posinit.y + P.posinit.h / 2;
    int r2 = sqrt(pow(P.posinit.w / 2, 2) + pow(P.posinit.h / 2, 2));

    // Calculate the distance between the centers of the circles
    double distance_centers = distance(x1, y1, x2, y2);

    // Compare the distance to the sum of the radii
    return (distance_centers <= (r1 + r2)) ? 1 : 0; // Collision detected if true, otherwise no collision
}
			
			
void HandleCollision_Player_Bonus (Person * p , SDL_Rect* C , int *score,Mix_Chunk * CoinSFX) {
		static unsigned int lastCollisionTime = 0; // Static variable to store the time of the last collision
    const unsigned int delay = 1000; // Delay between collisions in milliseconds

    unsigned int currentTime = SDL_GetTicks(); // Get the current time

    // Check if enough time has elapsed since the last collision
    if (currentTime - lastCollisionTime < delay) {
        return; // Exit early if the delay period has not elapsed
    }

    if (CollisionTrigo(*C, *p)) {
    			Mix_PlayChannel(-1,CoinSFX,0);
        if (p->num_hearts < 3) {
            p->num_hearts++;
            C->y = 1110;
            
        } else if (p->num_hearts == 3) {
            *score += 500;
            C->y = 1110;
        }
	
        // Update the time of the last collision
        lastCollisionTime = currentTime;
    }
}
	
					
			
				
	
	
	
	


	
	
	


	
	
	
	
	

