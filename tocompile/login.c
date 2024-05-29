#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include<SDL/SDL_image.h>
#include "header.h"
#define MAX_CREDENTIAL_LENGTH 128
typedef	struct 
{
	char username[256];
	char password[256];
}user;

typedef struct {
    SDL_Surface *screen;
    SDL_Event event;
    bool running;
    char inputText[256];
    int textLength;
    bool isLogin; // true for login, false for signup
} AppState;

bool init_btn(Button * btn,char * chemin1,char * chemin2,int x , int y) {

    btn->img[0]=IMG_Load(chemin1);
    btn->img[1]=IMG_Load(chemin2);
    btn->pos.x=x;
    btn->pos.y=y;
    btn->pos.w=btn->img[0]->w;
    btn->pos.h=btn->img[1]->h;
    if ( !btn->img[0] || !btn->img[1]) {
            return false;
    }

return true;

}



bool initSDL(AppState *app) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    app->screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    if (!app->screen) {
        fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    SDL_WM_SetCaption("Login/Signup", NULL);
    app->running = true;
    app->textLength = 0;
    app->inputText[0] = '\0';
    app->isLogin = true; // Start with login screen

    return true;
}









bool verifyUser(const char *username, const char *password) {
    FILE *file = fopen("users.txt", "r");
    if (!file) return false;

    char storedUsername[256], storedPassword[256];
    while (fscanf(file, "%s %s", storedUsername, storedPassword) == 2) {
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}


bool signupUser(const char *username, const char *password) {
    FILE *file = fopen("users.txt", "a");
    if (!file) return false;

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    return true;
}


bool isButtonClicked(SDL_Event *event, SDL_Rect *button) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x = event->button.x;
        int y = event->button.y;

        if (x >= button->x && x <= (button->x + button->w) &&
            y >= button->y && y <= (button->y + button->h)) {
            return true;
        }
    }
    return false;
}


bool renderText(SDL_Surface *screen, const char *text, TTF_Font *font, SDL_Color color, int x, int y) {
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, color);
    if (!textSurface) {
        fprintf(stderr, "Unable to render text: %s\n", TTF_GetError());
        return false;
    }

    SDL_Rect textLocation = {x, y, 0, 0};
    SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
    SDL_FreeSurface(textSurface);

    return true;
}
int write_user(const char *filename, const char *username, const char *password) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        return -1;
    }
    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    return 0;
}

// Function to read users from a file (not used in this example)
void read_users(const char *filename, char users[][2][MAX_CREDENTIAL_LENGTH], int max_users) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return;
    }
    char username[MAX_CREDENTIAL_LENGTH], password[MAX_CREDENTIAL_LENGTH];
    int i = 0;
    while (fscanf(file, "%s %s", username, password) == 2 && i < max_users) {
        strcpy(users[i][0], username);
        strcpy(users[i][1], password);
        i++;
    }
    fclose(file);
}

bool isMouseHoveringOverButton(SDL_Event *event, SDL_Rect *button) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (x >= button->x && x <= (button->x + button->w) &&
        y >= button->y && y <= (button->y + button->h)) {
        return true;
    }
    return false;
}


void blitButton(SDL_Surface *ecran, Button *button,SDL_Event  event) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (isMouseHoveringOverButton(&event, &button->pos)) {
        SDL_BlitSurface(button->img[1], NULL, ecran, &button->pos);
    } else {
        SDL_BlitSurface(button->img[0], NULL, ecran, &button->pos);
    }
}

int game(SDL_Event  event,SDL_Surface * ecran) {
     SDL_Surface *backg = IMG_Load("src/login_sns_tn.png"); // Load your background image here if needed
     Button btn_login,btn_signup;
    init_btn(&btn_login,"src/login_1.png","src/login_0.png",370 , 821);
    init_btn(&btn_signup,"src/singup_1.png","src/signup_0.png",1130 , 813);

    int running = 1;
    SDL_Rect pos_lgn = {370, 821, 425,115};
    SDL_Rect pos_sign = {1130,813, 431, 125};
    char username[MAX_CREDENTIAL_LENGTH] = "*user";
    char password[MAX_CREDENTIAL_LENGTH] = "*pass";
    int active_input = 0; // 0 for username, 1 for password
    int state = 0; // 0 for login, 1 for signup, 2 for logged in
    SDL_Color active_color = {255, 0, 0}; // Red color for active input
    SDL_Color error_color={255,255,0};
    SDL_Rect Userbox={720,356,500,30};
    SDL_Rect Passbox={720,543,500,30};
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        fprintf(stderr, "Unable to initialize SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return;
    }

    // Load a font
    TTF_Font *font = TTF_OpenFont("/home/aziz/Desktop/Backup/Digital_Intrusion/arial.ttf", 50);
    if (!font) {
        fprintf(stderr, "Unable to open font: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_Color color = {255, 255, 255}; // White color

     /*printf("Username \n");
                        scanf("%s",username);
                        printf("PASSWORD\n");
                        scanf("%s",password);*/
    while(running) {
        //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); // Clear screen with black
        SDL_BlitSurface(backg, NULL, ecran, NULL);
        blitButton(ecran, &btn_login,event);
        blitButton(ecran, &btn_signup,event);

          //renderText(ecran, "Username:", font, color, 960, 50);
        renderText(ecran, username, font, active_input == 0 ? active_color : color, 720, 356);
        //renderText(ecran, "Password:", font, color, 960, 150);
        renderText(ecran, password, font, active_input == 1 ? active_color : color, 720, 543);

        SDL_Flip(ecran);
            while(SDL_PollEvent(&event)) {
                    if(isButtonClicked(&event,&pos_lgn)) {

                        printf("login\n");
                       state=0;

                    }

                    if(isButtonClicked(&event,&pos_sign)){
                            printf("SINGUP\n");
                            state=1;

                    } 
                   if(event.type == SDL_QUIT){
                        running=0;
                   }

                   else if (event.type == SDL_KEYDOWN) {
            char *target;
            if (active_input == 0) {
                target = username;
            } else {
                target = password;
            }

            int len = strlen(target);
            if (event.key.keysym.sym == SDLK_BACKSPACE && len > 1) {
                target[len - 1] = '\0';
            } else if (event.key.keysym.sym == SDLK_TAB) {
                active_input = (active_input == 0) ? 1 : 0; // Toggle between username and password input
            } else if (event.key.keysym.sym == SDLK_RETURN) {
                if (state == 0) { // Login state
                    if ( verifyUser(username,password)) {
                        printf("Login successful\n");
                        state = 2; // Logged in
                        return 1;
                    } else {
                    renderText(ecran, "This user doesnt exist", font, error_color, 678, 662);
                    SDL_Flip(ecran);
                    SDL_Delay(2000);

                    }
                } else if (state == 1) { // Signup state
                    if (write_user("users.txt", username, password) == 0) {
                    renderText(ecran, "Signup Successful", font, color, 678,662);
                    SDL_Flip(ecran);
                    SDL_Delay(2000);
                        //read_users("users.txt", username, 3);
                        state = 0; // Go back to login state
                        //return 1;
                    } else {
                    renderText(ecran, "Signup Failed", font, error_color, 678,662);
                    SDL_Flip(ecran);
                    SDL_Delay(2000);


                    }
                }
            }else if (event.key.keysym.sym == SDLK_ESCAPE){running=0;return 0;} else if (len < MAX_CREDENTIAL_LENGTH - 1) {
                char key = (char)event.key.keysym.unicode;
                if (key >= 32 && key <= 126) { // Printable characters
                    target[len] = key;
                    target[len + 1] = '\0';
                }
            }
               
            
        



                    }
                     if (isMouseHoveringOverButton(&event, &Userbox)) {
                    active_input = 0; // Set focus to username input
                } else if (isMouseHoveringOverButton(&event, &Passbox)) {
                    active_input = 1; // Set focus to password input
                }

            



    }



}
}




/*int main(int argc, char const *argv[])
{
     if (SDL_Init(SDL_INIT_EVERYTHING)) {
                printf("ERROR LOADING SDL \n");
        }
        SDL_Surface * ecran=SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE);
    SDL_Event event;
    if (game(event,ecran)==1) {
            printf("Done\n");
            SDL_Delay(500);
            SDL_Quit();
    }
    return 0;
}*/


