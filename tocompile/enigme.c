
#include "enigme.h"

void init_enig_fichier(enig_fichier* en, SDL_Color Color)
{
    // Load the background image
    en->image_enig_fichier = IMG_Load("bg_enigme.png");
    if (en->image_enig_fichier == NULL)
    {
        fprintf(stderr, "Failed to load background image: %s\n", IMG_GetError());
        // Handle error if necessary
    }

    // Set the position of the background image
    en->position_enig_fichier.x = 0;
    en->position_enig_fichier.y = 0;

    // Initialize resultat to 0 (no result)
    en->resultat = 0;

    // Load the correct and wrong images
    en->correct = IMG_Load("correct.png");
    if (en->correct == NULL)
    {
        fprintf(stderr, "Failed to load correct image: %s\n", IMG_GetError());
        // Handle error if necessary
    }
    en->wrong = IMG_Load("wrong .png");
    if (en->wrong == NULL)
    {
        fprintf(stderr, "Failed to load wrong image: %s\n", IMG_GetError());
        // Handle error if necessary
    }

    // Set the positions of the correct and wrong images
    en->position_correct.x = 240;
    en->position_correct.y = 255;
    en->position_wrong.x = 240;
    en->position_wrong.y = 255;

    // Open the font for the answers and questions
    en->police = TTF_OpenFont("police.ttf", 50);
    if (en->police == NULL)
    {
        fprintf(stderr, "Failed to open font: %s\n", TTF_GetError());
        // Handle error if necessary
    }
    en->police_q = TTF_OpenFont("police.ttf", 45);
    if (en->police_q == NULL)
    {
        fprintf(stderr, "Failed to open font: %s\n", TTF_GetError());
        // Handle error if necessary
    }

    // Initialize the surfaces for the answers and questions to NULL
    en->reponse_1 = NULL;
    en->reponse_2 = NULL;
    en->reponse_3 = NULL;
    en->question = NULL;

    // Set the positions of the answers and questions
    en->pos_reponse_1.x = 200;
    en->pos_reponse_1.y = 500;
    en->pos_reponse_2.x = 450;
    en->pos_reponse_2.y = 500;
    en->pos_reponse_3.x = 700;
    en->pos_reponse_3.y = 500;
    en->pos_question.x = 200;
    en->pos_question.y = 250;

    // Initialize alea to 0
 
   en->alea = 0;
en->current_timer_index = 0;
}



void blit_enig_fichier (enig_fichier *en, SDL_Surface* screen)
{
    // Blit the background image
    SDL_BlitSurface(en->image_enig_fichier, NULL, screen, &en->position_enig_fichier);

    // Blit the timer images
    SDL_BlitSurface(en->timer[en->current_timer_index], NULL, screen, &en->pos_timer); // Assuming the timer images are already loaded into en->timer array

    // Blit the answers and question surfaces
    SDL_BlitSurface(en->reponse_1, NULL, screen, &en->pos_reponse_1);
    SDL_BlitSurface(en->reponse_2, NULL, screen, &en->pos_reponse_2);
    SDL_BlitSurface(en->reponse_3, NULL, screen, &en->pos_reponse_3);
    SDL_BlitSurface(en->question, NULL, screen, &en->pos_question);
}


void free_surface_enig_fichier( enig_fichier *en )
{
    SDL_FreeSurface(en->image_enig_fichier);
    SDL_FreeSurface(en->correct);
    SDL_FreeSurface(en->wrong);
    SDL_FreeSurface(en->reponse_1);
    SDL_FreeSurface(en->reponse_2);
    SDL_FreeSurface(en->reponse_3);
    SDL_FreeSurface(en->question);
    TTF_CloseFont(en->police);
    TTF_CloseFont(en->police_q);
}

void alea_enig_fichier(enig_fichier *en, SDL_Color Color)
{
    FILE* fichier = NULL;
    FILE* fichier_reponse = NULL;
    char ques[60] = {0};
    char rep1[20] = {0};
    char rep2[20] = {0};
    char rep3[20] = {0};
    int caracterelu_question, caracterelu_reponses, ligne = 1, ligne_reponse = 1;
    srand(time(0));
    do
    {
        en->alea = rand() % 2 + 1;
    } while (en->alea < 1 || en->alea > 2);

    fichier_reponse = fopen("reponse.txt", "r"); // r = read
    fichier = fopen("question.txt", "r");         // r = read
    if (fichier != NULL && fichier_reponse != NULL)
    {
        while (caracterelu_question != EOF && ligne < en->alea)
        {
            caracterelu_question = fgetc(fichier);
            if (caracterelu_question == '\n')
                ligne++;
        }
        fgets(ques, 45, fichier);
        fclose(fichier);
        while (caracterelu_reponses != EOF && ligne_reponse < en->alea)
        {
            caracterelu_reponses = fgetc(fichier_reponse);
            if (caracterelu_reponses == '\n')
                ligne_reponse++;
        }
        fscanf(fichier_reponse, "%s %s %s", rep1, rep2, rep3);
        fclose(fichier_reponse);
        
        // Load timer images
        char timer_path[30];
        for (int i = 0; i < 10; i++) {
            sprintf(timer_path, "img/timer/%d.gif", i);
            en->timer[i] = IMG_Load(timer_path);
            if (en->timer[i] == NULL)
            {
                fprintf(stderr, "Failed to load timer image %d: %s\n", i, IMG_GetError());
                // Handle error if necessary
            }
        }

        // Set position of the timer
        en->pos_timer.x = 560;
        en->pos_timer.y = 14;

        // Start the timer animation
        SDL_TimerID timerID = SDL_AddTimer(1000, timerCallback, en);
        if (timerID == 0) {
            fprintf(stderr, "Failed to start timer animation: %s\n", SDL_GetError());
            // Handle error if necessary
        }
    }

    // Print the read question and answers for debugging
    printf("Question: %s\n", ques);
    printf("Answer 1: %s\n", rep1);
    printf("Answer 2: %s\n", rep2);
    printf("Answer 3: %s\n", rep3);

    en->question = TTF_RenderText_Blended(en->police_q, ques, Color);
    en->reponse_1 = TTF_RenderText_Blended(en->police, rep1, Color);
    en->reponse_2 = TTF_RenderText_Blended(en->police, rep2, Color);
    en->reponse_3 = TTF_RenderText_Blended(en->police, rep3, Color);
}

// Timer callback function to update timer image index
Uint32 timerCallback(Uint32 interval, void *param)
{
    enig_fichier *en = (enig_fichier *)param;

    // Increment timer index
    en->current_timer_index++;
    if (en->current_timer_index >= 10) {
        en->current_timer_index = 0;
    }

    return interval;
}



int quiz1(enig_fichier *en, SDL_Surface* screen )
{

    SDL_Event event;
    int continuer=1;
    SDL_Color Color = {255,255,255};
    alea_enig_fichier(en,Color);
    while(continuer == 1)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer=0;

            break;

        case SDL_MOUSEBUTTONDOWN:
        {
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT:
            {
                if ( event.button.x>200 && event.button.x<350 && event.button.y>500 && event.button.y<600) //reponse1
                {
                    if ( en->alea == 1 )
                    {
                        en->resultat= 1;
                    }
                    else if ( en->alea == 2)
                    {
                        en->resultat = 2;
                    }
                    else if ( en->alea == 3)
                    {
                        en->resultat = 3;
                    }
                    
                }
                if ( event.button.x>450 && event.button.x<600 && event.button.y>500 && event.button.y<600) //reponse2
                {
                    if ( en->alea == 1 )
                    {
                        en->resultat= 2;
                    }
                    else if ( en->alea == 2)
                    {
                        en->resultat = 2;
                    }
                    else if ( en->alea == 3)
                    {
                        en->resultat = 2;
                    }
                }
                if ( event.button.x>700 && event.button.x<850 && event.button.y>500 && event.button.y<600) //reponse3
                {
                    if ( en->alea == 1 )
                    {
                        en->resultat= 2;
                    }
                    else if ( en->alea == 2)
                    {
                        en->resultat = 1;
                    }
                    else if ( en->alea == 3)
                    {
                        en->resultat = 2;
                    }
                }
            }
            break; //button left
            }
        }
        break;

        }// taskiret les events mtaa les boutons

        blit_enig_fichier ( en, screen);

        if ( en->resultat == 1 )
        {
            SDL_BlitSurface(en->correct,NULL, screen, &en->position_correct );
            //SDL_Flip(screen);
            //SDL_Delay(1000);
            continuer = 0;
    
        return 1;
        }
        else if ( en->resultat == 2 )
        {
            SDL_BlitSurface(en->wrong,NULL, screen, &en->position_wrong );
            SDL_Flip(screen);
            continuer = 0;

        return 2;
        }
        
        SDL_Flip(screen);


    }

}



int enig_fichier_avec_fichier(){
   
   
    SDL_Surface *screen =NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    screen=SDL_SetVideoMode(1000,600, 32,SDL_HWSURFACE| SDL_DOUBLEBUF);
    SDL_WM_SetCaption("game",NULL);
    TTF_Init();
    SDL_Color Color={255,255,255};
    enig_fichier en;
    init_enig_fichier(&en,Color);

    int res = quiz1(&en,screen );
    
    //free_surface_enig_fichier( &en );
    //SDL_Quit();

    //return EXIT_SUCCESS ;
}







/*#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "enigme.h"

void initexte(text *A) {
    A->position.x = 610;
    A->position.y = 30;
    A->textColor.r = 255;
    A->textColor.g = 255;
    A->textColor.b = 255;

    A->font = TTF_OpenFont("fonts/police.ttf", 20);
}


void init_enigme(enigme *e) {
    int i = 1;
    char nomimage[20];

    e->p.x = 360;
    e->p.y = 140;
    e->img = NULL;

    // Exemple de génération d'un numéro aléatoire pour l'énigme
    generate_afficher(&e->num_enigme);

    // Charger l'image de l'énigme depuis un fichier
    FILE *f = fopen("enigme.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %d\n", nomimage, &e->reponsevrai) != EOF && i != e->num_enigme) {
            i++;
        }
        e->img = IMG_Load(nomimage);
        fclose(f);
    } else {
        printf("ERROR loading file\n");
    }
}
// Afficher le résultat (win ou lose) avec un délai de 5 secondes
void afficher_resultat(SDL_Surface *screen, int s, int r, enigme *en) {
    if (r == s) {
        en->res = IMG_Load("img/win.jpg");
    } else {
        en->res = IMG_Load("img/lose.jpg");
    }

    SDL_BlitSurface(en->res, NULL, screen, &(en->p));
    SDL_Flip(screen);

    // Délai de 5 secondes
    //SDL_Delay(3000); // Attendre 5 secondes
    //SDL_FreeSurface(en->img);
}
void generate_afficher(int *alea) {
    int test = *alea; // Variable temporaire
    srand(SDL_GetTicks()); // Initialiser le générateur de nombres aléatoires avec SDL_GetTicks

    do {
        *alea = 1 + rand() % 12; // Générer un nombre entre 1 et 12
    } while (*alea == test); // S'assurer qu'il n'est pas le même que le précédent
}

// Boucle de jeu avec sortie après délai
int enigme_play(SDL_Surface* screen) {
    enigme e;
    e.num_enigme = -1;
    int r = 0;
    int running = 1; // Le jeu est initialement en cours d'exécution
    int boucle = 1; // Boucle principale du jeu
    char cc[30] = "0";
    text tt;

    init_enigme(&e);
    initexte(&tt);

   while (boucle) {
        SDL_BlitSurface(e.img, NULL, screen, &e.p);
        SDL_Flip(screen);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                boucle = 0; // Quitter la boucle
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    boucle = 0; // Quitter la boucle sur ESC
                    break;
                }
                
                switch (event.key.keysym.sym) {
                case SDLK_a:
                    r = 1;
                    running = 0; // Indiquer que le jeu doit arrêter après résultat
                    break;
                case SDLK_z:
                    r = 2;
                    running = 0;
                    break;
                case SDLK_e:
                    r = 3;
                    running = 0;
                    break;
                case SDLK_r:
                    r = 4;
                    running = 0;
                    break;
                default:
                    break;
                }
            }
        }

        if (running == 0) {
            // Afficher le résultat et quitter après 5 secondes
            afficher_resultat(screen, e.reponsevrai, r, &e);
            boucle = 0; // Quitter la boucle après affichage
        }
    }
	
    
    if (r == e.reponsevrai) {
        return 1; // Bonne réponse
    } else {
        return 0; // Mauvaise réponse
    }
    
    
     SDL_FreeSurface(e.img);
    for (int i = 0; i < 10; i++) {
        SDL_FreeSurface(e.timer[i]);
    }
    SDL_FreeSurface(tt.surfaceTexte);
}
*/




