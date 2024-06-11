

#include "perso.h"
#define SPRITE_WIDTH 50
#define SPRITE_HEIGHT 48
#define NUM_FRAMES 3
#define NUM_DIRECTIONS 4 
#define dx 150
#define dy 150
#define  COLLISION_RESET_TIME 3000
#define MAX_FRAMES    3
#define MAX_DIRECTIONS 4
#define MAX_CREDENTIAL_LENGTH 128
void loadPlayerSpriteSheet(Person *p1, const char *filename) {
    SDL_Surface *spriteSheet = IMG_Load(filename);
    if (!spriteSheet) {
        printf("ERROR LOADING SPRITE");
        exit(1);
    }

 
    p1->spriteSheet = spriteSheet;

    // Calculate the number of frames in each direction
    int framesPerDirection = 3;

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


void renderPlayerFrame(Person *p1, SDL_Surface *ecran) {
      // Check if p1 and screen are not NULL
    if (p1 == NULL || ecran == NULL) {
        printf("Error: Null pointer passed to renderPlayerFrame.\n");
        return;
    }

    // Check if p1->spriteSheet is not NULL
    if (p1->spriteSheet == NULL) {
        printf("Error: spriteSheet is NULL in renderPlayerFrame.\n");
        return;
    }

    // Check if direction and frame are within valid range
    if (p1->direction < 0 || p1->direction >= MAX_DIRECTIONS ||
        p1->frame < 0 || p1->frame >= MAX_FRAMES) {
        printf("Error: Invalid direction or frame in renderPlayerFrame.\n");
        return;
    }


    SDL_Rect dest;
    dest.x = p1->posinit.x ;
    dest.y = p1->posinit.y;
    dest.w = SPRITE_WIDTH;
    dest.h = SPRITE_HEIGHT;
           

    // Render frame for the current direction
    SDL_BlitSurface(p1->spriteSheet,&p1->frameClips[p1->direction][p1->frame],ecran, &dest);
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
        deplacerEntite_MULTIJOUEUR(*P, Dot, PlayZone);
        *lastMoveTime = currentTime;
        collisionOccurred = 1; // Set collision flag
    }
}

int timer(time_t startTime, int countdown, TTF_Font *font, SDL_Rect PosVie, SDL_Surface *ecran) {
    // Calculate the remaining time
    time_t currentTime = time(NULL);
    int elapsedTime = difftime(currentTime, startTime);
    int remainingTime = countdown - elapsedTime;

    if (remainingTime <= 0) {
        remainingTime = 0; // Ensure the remaining time doesn't go below 0
        return 0;
    }

    // Convert remaining time to string
    char CTime[4]; // Adjust size if you expect more than 3 digits
    sprintf(CTime, "%d", remainingTime);

    // Render the text surface
    SDL_Color txtCoul = {255, 0, 255};
    SDL_Surface *SurfTime = TTF_RenderText_Solid(font, CTime, txtCoul);
    if (SurfTime == NULL) {
        printf("Error rendering text: %s\n", TTF_GetError());
        return -1;
    }

    // Blit the text surface onto the screen
    SDL_BlitSurface(SurfTime, NULL, ecran, &PosVie);
    SDL_FreeSurface(SurfTime);

    return 1;
}


void handleMPGameState (int scoreP1 , int scoreP2 , SDL_Rect PlayerZone_1 , SDL_Rect PlayerZone_2 , SDL_Surface * ecran,  bool * mainmenu , bool *Playing) {
    SDL_Rect PosWinner,PosLoser;
    SDL_Surface * Winner , *loser;
    Winner = IMG_Load("win1.png");
    loser = IMG_Load("lose1.png");
    
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
        *Playing=false;
        *mainmenu = true;


}


bool verifyUsername(const char *username) {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("Failed to open users.txt\n");
        return false;
    }

    char storedUsername[256], storedPassword[256], storedPfpPath[256];
    while (fscanf(file, "%s %s %[^\n]", storedUsername, storedPassword, storedPfpPath) == 3) {
        printf("Checking username: %s\n", storedUsername);
        if (strcmp(username, storedUsername) == 0) {
            printf("User found: %s\n", username);
            fclose(file);
            return true;
        }
    }

    printf("User not found: %s\n", username);
    fclose(file);
    return false;
}



int HandleMPAuthentication(SDL_Surface *ecran, SDL_Event event) {
    SDL_Surface *backg = IMG_Load("/home/aziz/Desktop/Digital_Intrusion/mp_login.png");

    if (!backg) {
        printf("Error loading background image\n");
        return -1;
    }

    int running = 1;
    char Name1[MAX_CREDENTIAL_LENGTH] = "-";
    char Name2[MAX_CREDENTIAL_LENGTH] = "-";
    int active_input = 0; // 0 for Name1, 1 for Name2
    SDL_Color active_color = {255, 255, 0}; // Yellow color for active input
    SDL_Color error_color = {255, 255, 0};
    SDL_Rect User1box = {720, 356, 500, 30};
    SDL_Rect User2box = {720, 543, 500, 30};

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        fprintf(stderr, "Unable to initialize SDL_ttf: %s\n", TTF_GetError());
        SDL_FreeSurface(backg);
        SDL_Quit();
        return -1;
    }

    // Load a font
    TTF_Font *font = TTF_OpenFont("/home/aziz/Desktop/Backup/Digital_Intrusion/arial.ttf", 50);
    if (!font) {
        fprintf(stderr, "Unable to open font: %s\n", TTF_GetError());
        SDL_FreeSurface(backg);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    SDL_Color color = {255, 255, 255}; // White color

    while (running) {
        SDL_BlitSurface(backg, NULL, ecran, NULL);

        renderText(ecran, "Player 1 Name:", font, active_color, 1220, 400);
        renderText(ecran, Name1, font, active_input == 0 ? active_color : color, 1220, 500);
        renderText(ecran, "Player 2 Name:", font, active_color, 268, 400);
        renderText(ecran, Name2, font, active_input == 1 ? active_color : color, 268, 500);

        SDL_Flip(ecran);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                char *target;
                if (active_input == 0) {
                    target = Name1;
                } else {
                    target = Name2;
                }

                int len = strlen(target);
                if (event.key.keysym.sym == SDLK_BACKSPACE && len > 1) {
                    target[len - 1] = '\0';
                } else if (event.key.keysym.sym == SDLK_TAB) {
                    active_input = (active_input == 0) ? 1 : 0; // Toggle between Name1 and Name2
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                    return 0;
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (strlen(Name1) > 1 && strlen(Name2) > 1) {
                        char validName1[MAX_CREDENTIAL_LENGTH];
                        char validName2[MAX_CREDENTIAL_LENGTH];
                        strcpy(validName1, Name1);
                        strcpy(validName2, Name2);
                        for (int i = 0; i < strlen(validName1); i++) {
                            if (validName1[i] == '-') validName1[i] = '*';
                        }
                        for (int i = 0; i < strlen(validName2); i++) {
                            if (validName2[i] == '-') validName2[i] = '*';
                        }
                        if (verifyUsername(validName1) && verifyUsername(validName2)) {
                            return 1; // Authentication successful
                        } else {
                            renderText(ecran, "Names not found", font, error_color, 960, 200);

                        }
                    } else {
                        renderText(ecran, "Please Provide Names", font, error_color, 960, 1000);
                    }
                } else if (len < MAX_CREDENTIAL_LENGTH - 1) {
                    char key = (char)event.key.keysym.unicode;
                    if (key >= 32 && key <= 126) { // Printable characters
                        target[len] = key;
                        target[len + 1] = '\0';
                    }
                }
            } else if (isMouseHoveringOverButton(&event, &User1box)) {
                active_input = 0; // Set focus to Name1 input
            } else if (isMouseHoveringOverButton(&event, &User2box)) {
                active_input = 1; // Set focus to Name2 input
            }
        }
                SDL_Flip(ecran);

    }

    // Cleanup
    SDL_FreeSurface(backg);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

