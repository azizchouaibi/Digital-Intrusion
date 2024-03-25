#include "header.h"

Person  InitPerso(Person  player ) {
	int i;
	
	
	for (i=0;i<14;i++) {
		player.texture[i]=NULL;
	}
	
	player.texture[0]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/1.png");
	player.texture[1]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/2.png");
	player.texture[2]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/3.png");
	player.texture[3]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/4.png");
	player.texture[4]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/5.png");
	player.texture[5]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/L1.png");
	player.texture[6]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/L2.png");
	player.texture[7]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/L3.png");
	player.texture[8]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/L4.png");
	player.texture[9]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/L5.png");
	player.texture[10]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/jump 1.png");
	player.texture[11]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/jump2.png");
	player.texture[12]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/jump1L.png");
	player.texture[13]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/jump2L.png");
	
	
	
	
	
	for (i=0;i<14;i++) {
		if (player.texture[i]==NULL) {
			printf("ERREUR LODING IMAGE n %d\n",i);
		} else {
			printf("SUCCES %d " , i);
		}
		
	}
	
	player.jump=false;
	player.acc=0.1;
	player.vt=10;
	
	player.num_hearts=3;
	player.textcourant=0;
	
	for (i=0 ; i < player.num_hearts ; i++) {
		player.vie[i]=NULL;
	}
		
	player.vie[0]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/h1.png");
	player.vie[1]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/h2.png");
	player.vie[2]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/anim perso test/h3.png");
	
	for ( i =0 ; i<player.num_hearts ; i++) {
		if ( player.vie[i]==NULL) {
			printf("ERROR LOADING VIE n %d\n",i);
		}
	}
	
	player.posinit.x = 200; // a changer
   	player.posinit.y = 100;
   	
    	player.posvie.x=270;
    	player.posvie.y=8;
    	
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
	
	
if ( TempsPasse >= 45 || DernierImage == 0) {
	DernierImage=TempsCourant;
	
	switch (direction) {
		case 1 :
		player->posinit.x+=8;
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





void jumpPerso ( Person * player , int direction) { // Right ou Left 

static double a = -0.04; 
    static int c = -100;     

    

    static Uint32 lastTime = 0;
    Uint32 currentTime = SDL_GetTicks();
    double dt = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;


    player->posinit.y = (int) (a * player->acc * player->acc + c);


    player->acc += 0.1; 
 
        switch (direction) {
        case 1:
            player->posinit.x += 10;
            break;
        case -1:
            player->posinit.x -= 10;
            break;
    }
    
}
	        
	        
	        


		



////////////// TEST POUR AUTRE TACHE /////////////- 	
Backg initBack(Backg  Back) {
 int i ;
 	for (i=0 ; i<3 ; i++) {
 		Back.back[i]=NULL;
 	}
 	Back.back[0]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/back.png");
 	Back.back[1]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/back2.png");
 	Back.back[2]=IMG_Load("/home/aziz/Desktop/Travail/game mechanics/back3.png");
 	
 	for (i = 0  ; i <3 ; i++) {
 		if ( Back.back[i]==NULL) {
 			printf("ERROR LOADING n %d\n",i);
 		}
 	}
 	
 	Back.posarr.x=0;
 	Back.posarr.y=0;
 	Back.posarr.w=600;
 	Back.posarr.h=400;
 	
 	Back.indback=0;
 	return Back;
 }	
	
	
	
	

