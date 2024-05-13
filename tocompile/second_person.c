

#include "perso.h"
#define SPRITE_WIDTH 50
#define SPRITE_HEIGHT 48
#define NUM_FRAMES 3
#define NUM_DIRECTIONS 4 
#define dx 150
#define dy 150
#define  COLLISION_RESET_TIME 3000

void loadPlayerSpriteSheet(Person *p1, const char *filename, SDL_Surface *screen) {
    SDL_Surface *spriteSheet = IMG_Load(filename);
    if (!spriteSheet) {
        printf("ERROR LOADING SPRITE");
        exit(1);
    }

    // Set transparent color (if necessary)
    /*Uint32 colorkey = SDL_MapRGB(spriteSheet->format, 0, 0, 0);
    SDL_SetColorKey(spriteSheet, SDL_SRCCOLORKEY, colorkey);*/

    // Store the entire sprite sheet surface
    p1->spriteSheet = spriteSheet;

    // Calculate the number of frames in each direction
    int framesPerDirection = 3;
        printf("Frames per direction %d",framesPerDirection);

    // Divide the sprite sheet into frames for each direction
    for (int dir = 0; dir < NUM_DIRECTIONS; ++dir) {
        for (int frame = 0; frame < framesPerDirection; ++frame) {
            SDL_Rect clipRect;
            clipRect.x = frame * SPRITE_WIDTH;
            clipRect.y = dir * SPRITE_HEIGHT;
            clipRect.w = SPRITE_WIDTH;
            clipRect.h = SPRITE_HEIGHT;

            // Store the clip rectangle for each frame
            p1->frameClips[dir][frame] = clipRect;
        }
    }

    p1->num_hearts = 2;
    p1->posinit.w = SPRITE_WIDTH;
    p1->posinit.h = SPRITE_HEIGHT;
}


void renderPlayerFrame(Person *p1, SDL_Surface *screen,TTF_Font * font) {
    SDL_Rect dest;
    dest.x = p1->posinit.x ;
    dest.y = p1->posinit.y;
    dest.w = SPRITE_WIDTH;
    dest.h = SPRITE_HEIGHT;
           







    // Render frame for the current direction
    SDL_BlitSurface(p1->spriteSheet,&p1->frameClips[p1->direction][p1->frame], screen, &dest);
}

void deplacerEntite_MULTIJOUEUR(Person P, Entity *Dot, SDL_Rect playZone) {
    // Calculate the maximum x and y coordinates within the play zone
    int maxX = playZone.x + playZone.w ;
    int maxY = playZone.y + playZone.h ;

    // Move the dot to a random position within the play zone
    Dot->pos.x = playZone.x + (rand() % maxX);
    Dot->pos.y = playZone.y + (rand() % maxY);
    if ( Dot -> pos.x > maxX) {Dot->pos.x = maxX - 100;}
    if ( Dot->pos.y > maxY) {Dot->pos.y = maxY - 100;}
}
bool checkCollision(SDL_Rect playerRect, SDL_Rect circleRect) {
    // Calculate the center of the player rectangle
    int playerCenterX = playerRect.x + playerRect.w / 2;
    int playerCenterY = playerRect.y + playerRect.h / 2;

    // Calculate the center of the circle rectangle
    int circleCenterX = circleRect.x + circleRect.w / 2;
    int circleCenterY = circleRect.y + circleRect.h / 2;

    // Calculate the distance between the centers of the player and the circle
    int distanceX = abs(playerCenterX - circleCenterX);
    int distanceY = abs(playerCenterY - circleCenterY);

    // Calculate the half-widths and half-heights of the player and the circle
    int playerHalfWidth = playerRect.w / 2;
    int playerHalfHeight = playerRect.h / 2;
    int circleHalfWidth = circleRect.w / 2;
    int circleHalfHeight = circleRect.h / 2;

    // Check if the distance between the centers is less than the sum of the half-widths and half-heights
    bool collisionX = distanceX <= (playerHalfWidth + circleHalfWidth);
    bool collisionY = distanceY <= (playerHalfHeight + circleHalfHeight);

    return collisionX && collisionY;
}









void Deplacer_ET_NON_COLLISION(Person *P, Entity *Dot, SDL_Rect PlayZone, Uint32 *lastMoveTime, Uint32 currentTime, Uint32 moveInterval) {
    static int collisionOccurred = 0; // Flag to track if collision occurred

    if (!collisionOccurred) {
        // Move the dot only if no collision has occurred
        if (currentTime - *lastMoveTime >= moveInterval) {
            deplacerEntite_MULTIJOUEUR(*P, Dot, PlayZone);
            *lastMoveTime = currentTime;
        }
    } else {
        // Reset the collision flag after a certain period of time
        if (currentTime - *lastMoveTime >= COLLISION_RESET_TIME) {
            collisionOccurred = 0;
        }
    }

    // Check for collision
    if (!collisionOccurred && checkCollision(P->posinit,Dot->pos) == 1) {
        P->score++;
        printf("COLLIDED \n");
        deplacerEntite_MULTIJOUEUR(*P, Dot, PlayZone);
        printf("X:%d\n Y: %d\n" , Dot->pos.x , Dot->pos.y);
        *lastMoveTime = currentTime;
        collisionOccurred = 1; // Set collision flag
    }
}

int timer(Uint32 Time , TTF_Font * font , SDL_Rect PosVie, SDL_Surface * ecran) {
        int time_in_s = 120 - (Time / 1000);
        char CTime[3];
        SDL_Surface * SurfTime;
                if ( time_in_s <= 0) {time_in_s = 0; return 0;}
        sprintf(CTime,"%d",time_in_s);
        SDL_Color txtCoul={255,0,255};
        SurfTime = TTF_RenderText_Solid(font,CTime,txtCoul);
        SDL_BlitSurface(SurfTime,NULL,ecran,&PosVie);
        
}


void handleMPGameState (int scoreP1 , int scoreP2 , SDL_Rect PlayerZone_1 , SDL_Rect PlayerZone_2 , SDL_Surface * ecran,  bool * mainmenu) {
    SDL_Rect PosWinner,PosLoser;
    SDL_Surface * Winner , *loser;
    Winner = IMG_Load("");
    loser = IMG_Load("");
    
        if (!Winner || !loser) {
                printf("ERROR LOADING WINNER OR LOSER PHOTO\n");
        }

    PosWinner = scoreP1 > scoreP2 ? PlayerZone_1 : PlayerZone_2;
    PosLoser = scoreP1 > scoreP2 ? PlayerZone_2 : PlayerZone_1;

    SDL_BlitSurface(Winner , NULL,ecran,&PosWinner);
    SDL_BlitSurface(loser,NULL,ecran,&PosLoser);
    SDL_Flip(ecran);
 Uint32 start_time = SDL_GetTicks();

    while (SDL_GetTicks() - start_time < 3000) {
    }
        *mainmenu = true;


}