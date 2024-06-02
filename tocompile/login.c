#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include<SDL/SDL_image.h>
#include <SDL/SDL_syswm.h>

#include "header.h"
#include "perso.h"
#define MAX_CREDENTIAL_LENGTH 128


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


/*char *getTextFromClipboard() {
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    if (!SDL_GetWMInfo(&info)) {
        fprintf(stderr, "SDL_GetWMInfo failed: %s\n", SDL_GetError());
        return NULL;
    }

    Display *display = info.info.x11.display;
    Window window = info.info.x11.window;

    XConvertSelection(display, XA_PRIMARY, XA_STRING, XA_PRIMARY, window, CurrentTime);
    XFlush(display);

    XSync(display, False);
    XEvent response;

    if (XCheckTypedWindowEvent(display, window, SelectionNotify, &response)) {
        if (response.xselection.selection != XA_PRIMARY) {
            fprintf(stderr, "Selection is not PRIMARY\n");
            return NULL;
        }

        if (response.xselection.property == None) {
            fprintf(stderr, "No selection property available\n");
            return NULL;
        }

        Atom type;
        int format;
        unsigned long nitems, bytes_after;
        unsigned char *prop;
        XGetWindowProperty(display, window, response.xselection.property, 0, 0xFFFF, False, AnyPropertyType, &type, &format, &nitems, &bytes_after, &prop);
        if (prop != NULL && type == XA_STRING) {
            char *text = strdup((char *)prop);
            XFree(prop);
            XCloseDisplay(display); // Close the X11 display to release resources
            return text;
        }
    }

    fprintf(stderr, "Failed to get clipboard text\n");
    XCloseDisplay(display); // Close the X11 display to release resources
    return NULL;
}*/




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
    if (!file) {
        printf("Failed to open users.txt\n");
        return false;
    }

    char storedUsername[256], storedPassword[256], storedPfpPath[256];
    while (fscanf(file, "%s %s %[^\n]", storedUsername, storedPassword, storedPfpPath) == 3) {
        printf("Checking username: %s with password: %s\n", storedUsername, storedPassword);
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            printf("User found: %s\n", username);
            fclose(file);
            return true;
        }
    }

    printf("User not found: %s\n", username);
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
int user_exists(const char *filename, const char *username, const char *password) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return 0; // File doesn't exist or couldn't be opened, so user doesn't exist
    }
    
    char line[100]; // Assuming each line in the file is not longer than 100 characters
    while (fgets(line, sizeof(line), file)) {
        // Split the line into username and password
        char file_username[50], file_password[50];
        if (sscanf(line, "%s %s", file_username, file_password) == 2) {
            // Compare the provided username and password with the ones from the file
            if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
                fclose(file);
                return 1; // User exists in the file
            }
        }
    }
    
    fclose(file);
    return 0; // User doesn't exist in the file
}

int write_user(const char *filename, const char *username, const char *password, const char *pfp_path) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Error opening file");
        return -1;
    }
    if (user_exists(filename,username,password) == 1) {
            return -1;
    }

    // Write the username, password, and profile picture path to the file
    fprintf(file, "%s %s %s\n", username, password, pfp_path);

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

int game(SDL_Event  event,SDL_Surface * ecran, user * us) {
     SDL_Surface *backg = IMG_Load("login[1].png"); 
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
        renderText(ecran, username, font, active_input == 0 ? active_color : color, 720, 305);
        //renderText(ecran, "Password:", font, color, 960, 150);
        renderText(ecran, password, font, active_input == 1 ? active_color : color, 720, 495);

        SDL_Flip(ecran);
            while(SDL_PollEvent(&event)) {
                    

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
            } 
            else if (event.key.keysym.sym == SDLK_ESCAPE){running=0;return 0;} else if (len < MAX_CREDENTIAL_LENGTH - 1) {
                char key = (char)event.key.keysym.unicode;
                if (key >= 32 && key <= 126) { // Printable characters
                    target[len] = key;
                    target[len + 1] = '\0';
                }
            }
               
                          
        



                    }

                         if (isButtonClicked(&event, &pos_lgn)) {
                //if (state == 0) { // Login state
                    printf("CLicked\n" );
                    if ( verifyUser(username,password)) {
                        printf("Login successful\n");
                        state = 2; // Logged in
                        strcpy(us->username,username);
                        strcpy(us->password,password);
                        return 1;
                    } else {
                    renderText(ecran, "This user doesnt exist", font, error_color, 678, 662);
                    SDL_Flip(ecran);
                    SDL_Delay(1000);

                    }
                 }else if (isButtonClicked(&event, &pos_sign)) { // Signup state
    if (Handle_PP(event, ecran, us) == 1) {
        if (write_user("users.txt", username, password, us->pfp_path) == 0) {
            renderText(ecran, "Signup Successful", font, color, 678, 662);
            SDL_Flip(ecran);
            SDL_Delay(1000);
            state = 0; // Go back to login state
        } else {
            renderText(ecran, "This User Exists ", font, error_color, 678, 662);
            SDL_Flip(ecran);
            SDL_Delay(1000);
        }
    } else {
        renderText(ecran, "Profile Picture Selection Failed", font, error_color, 678, 662);
        SDL_Flip(ecran);
        SDL_Delay(1000);
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



// PAUSE ---------- SAVE ------- LOAD
bool saveGame(const char *filename, int score, int health, int energy, int level, int collectibles,  user *users) {
    FILE *file = fopen(filename, "a+"); // Open the file in append mode to preserve existing contents
    if (file == NULL) {
        fprintf(stderr, "Unable to open file for saving\n");
        return false;
    }

    // Write game state variables and user information to the file
    fprintf(file, "%s\t", users->username);
    fprintf(file, "%s\t", users->password);
    fprintf(file, "%d\t", score);
    fprintf(file, "%d\t", health);
    fprintf(file, "%d\t", energy);
    fprintf(file, "%d\t", level);
    fprintf(file, "%d\n", collectibles);
    
    fclose(file);
    return true;
}

bool loadGame(const char *filename, Person *player, int *level, int *collectibles, const user *currentUser) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file for loading\n");
        return;
    }

    char line[512];
    char username[256], password[256];
    int score, num_hearts, energy, file_level, file_collectibles;

    // Initialize variables to track the last found user's data
    int found = 0;

    // Iterate through each line of the file
    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse the line to extract the username, password, and game data
        if (sscanf(line, "%255s\t%255s\t%d\t%d\t%d\t%d\t%d", username, password, &score, &num_hearts, &energy, &file_level, &file_collectibles) == 7) {
            // Check if the username and password match the current user's credentials
            if (strcmp(username, currentUser->username) == 0 && strcmp(password, currentUser->password) == 0) {
                // Store the user's game data but do not break; continue searching
                player->score = score;
                player->num_hearts = num_hearts;
                player->energy = energy;
                *level = file_level;
                *collectibles = file_collectibles;
                found = 1;
            }
        }
    }

    fclose(file);

    if (!found) {
        printf("User data not found in save file.\n");
        return false;
    }
    return true;
}



void freeButton(Button *button) {
    SDL_FreeSurface(button->img[0]);
    SDL_FreeSurface(button->img[1]);
}

int handle_pause_menu(SDL_Event event, SDL_Surface * ecran,Person *player ,int level, int collected,user * US){
        Button resume,save_exit,exit;
        SDL_Surface*  backg=IMG_Load("3.png");
            if(!backg){
                    printf("Error loading pause menu background\n");
            }


        init_btn(&resume,"src/resume_0.png","src/resume_1.png",822,210);
        init_btn(&save_exit,"src/save_0.png","src/save_1.png",822,447);
        init_btn(&exit,"src/quit_0.png","src/quit_1.png",822,668);
        int running=1;
        while(running){
            SDL_BlitSurface(backg,NULL,ecran,NULL);
            blitButton(ecran,&resume,event);
            blitButton(ecran,&save_exit,event);
            blitButton(ecran,&exit,event);
            SDL_Flip(ecran);
            while(SDL_PollEvent(&event)){
                    if(event.type == SDL_QUIT){
                            running=0;
                            SDL_FreeSurface(backg);
                            SDL_Quit();
                    }
            if(isButtonClicked(&event,&resume.pos)){
                return 3;

            }

            if(isButtonClicked(&event,&save_exit.pos)){ // save
                if(saveGame("Saves.txt", player->score, player->num_hearts, player->energy,level,collected,US)){
                running=0;  
                return 1;



            } else {
                    printf("ERROR SAVING GAME \n");
                    return 0;
            }
        }
        if(isButtonClicked(&event,&exit.pos)){ // exit
                    running=0;

            }
            }
        }
freeButton(&resume);
freeButton(&save_exit);
freeButton(&exit);
                            return 2; // exit





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


int Handle_PP(SDL_Event event, SDL_Surface *ecran, user *us) {
    SDL_Surface *backg = IMG_Load("pfp/menu.png"); 
    Button PFP1, PFP2, PFP3;
    init_btn(&PFP1, "/home/aziz/Desktop/Digital_Intrusion/pfp/pfp_1_0.png", "/home/aziz/Desktop/Digital_Intrusion/pfp/pfp_1_1.png", 1342, 125);
    init_btn(&PFP2, "/home/aziz/Desktop/Digital_Intrusion/pfp/pfp_2_0.png", "/home/aziz/Desktop/Digital_Intrusion/pfp/pfp_2_1.png", 1342, 361);
    init_btn(&PFP3, "/home/aziz/Desktop/Digital_Intrusion/pfp/pfp_3_0.png", "/home/aziz/Desktop/Digital_Intrusion/pfp/pfp_3_1.png", 1342, 616);
    
    char PFP1_Path[MAX_CREDENTIAL_LENGTH] = "pfp/pfp_1_0.png";
    char PFP2_Path[MAX_CREDENTIAL_LENGTH] = "pfp/pfp_2_0.png";
    char PFP3_Path[MAX_CREDENTIAL_LENGTH] = "pfp/pfp_3_0.png";
    char IMG_Path[MAX_CREDENTIAL_LENGTH] = "pfp/";

    SDL_Color active_color = {169,169, 169}; // Red color for active input
    TTF_Font *font = TTF_OpenFont("/home/aziz/Desktop/Backup/Digital_Intrusion/arial.ttf", 50);
    if (!font) {
        fprintf(stderr, "Unable to open font: %s\n", TTF_GetError());
        return -1;
    }

    SDL_Color color = {255, 255, 255}; // Black color
    SDL_Rect pos_SideBar = {1312, 0, 608, 1080};
    int running = 1;
    int valid_image = 0; // Flag to check if a valid image is selected

    while (running) {
        SDL_BlitSurface(backg, NULL, ecran, &pos_SideBar);
        blitButton(ecran, &PFP1, event);
        blitButton(ecran, &PFP2, event);
        blitButton(ecran, &PFP3, event);
        
        renderText(ecran, "Upload PFP:", font, color, 1342, 818);
        renderText(ecran, IMG_Path, font, active_color, 1342, 962);
        SDL_Flip(ecran);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                char *target = IMG_Path;
                int len = strlen(target);
                if (event.key.keysym.sym == SDLK_BACKSPACE && len > 1) {
                    target[len - 1] = '\0';
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                    return 0;
                } else if (len < MAX_CREDENTIAL_LENGTH - 1) {
                    char key = (char)event.key.keysym.unicode;
                    if (key >= 32 && key <= 126) { // Printable characters
                        target[len] = key;
                        target[len + 1] = '\0';
                    }
                }

                if (event.key.keysym.sym == SDLK_RETURN) {
                    strcpy(us->pfp_path, target);
                    us->pfp = IMG_Load(us->pfp_path);
                    if (!us->pfp) {
                        printf("ERROR: Invalid path or failed to load profile picture\n");
                        renderText(ecran, "ERROR: Invalid path", font, active_color, 1342, 1050);
                        SDL_Flip(ecran);
                        SDL_Delay(1000);
                    } else {
                        valid_image = 1;
                        running = 0;
                    }
                }
            }

            if (isButtonClicked(&event, &PFP1.pos)) {
                strcpy(us->pfp_path, PFP1_Path);
                us->pfp = IMG_Load(us->pfp_path);
                if (us->pfp) {
                    valid_image = 1;
                    running = 0;
                }
            } else if (isButtonClicked(&event, &PFP2.pos)) {
                strcpy(us->pfp_path, PFP2_Path);
                us->pfp = IMG_Load(us->pfp_path);
                if (us->pfp) {
                    valid_image = 1;
                    running = 0;
                }
            } else if (isButtonClicked(&event, &PFP3.pos)) {
                strcpy(us->pfp_path, PFP3_Path);
                us->pfp = IMG_Load(us->pfp_path);
                if (us->pfp) {
                    valid_image = 1;
                    running = 0;
                }
            }
        }
    }

    if (!valid_image) {
        // Ensure there's a fallback to a default image if all attempts fail
        strcpy(us->pfp_path, "default/path/to/default_image.png");
        us->pfp = IMG_Load(us->pfp_path);
        if (!us->pfp) {
            printf("ERROR: Failed to load default profile picture\n");
        }
    }
    freeButton(&PFP1);
    freeButton(&PFP2);
    freeButton(&PFP3);
    return valid_image;
}
/*=========================================*/

int handle_Profile_menu(SDL_Event event, SDL_Surface * ecran){
        Button pf;
        SDL_Surface*  backg=IMG_Load("for ts/smn__profiles.png");
            if(!backg){
                    printf("Error loading  Profiles menu background pause menu background\n");
            }



        init_btn(&pf,"for ts/pfp_btn_0.png","for ts/pfp_btn_1.png",1546,43);
        SDL_Rect posBack={1308,0,backg->w,backg->h};        
        int running=1;
        while(running){

            SDL_BlitSurface(backg,NULL,ecran,&posBack);
            blitButton(ecran,&pf,event);
            show_high_score(ecran);
            SDL_Flip(ecran);
            while(SDL_PollEvent(&event)){
                    if(event.type == SDL_QUIT){
                            running=0;
                            SDL_FreeSurface(backg);
                            SDL_Quit();
                    }
            if(isButtonClicked(&event,&pf.pos)){
              running=0;
                return 1;

            }

            if(event.key.keysym.sym == SDLK_ESCAPE){
                   running=0;
                 return 0;
            }

            }
        }
freeButton(&pf);
SDL_FreeSurface(backg);
}

#define MAX_USERS 100




void loadTopUsers(user *users, int *count) {
    FILE *file = fopen("Saves.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open saves file\n");
        return;
    }

    char line[512];
    int score, num_hearts, energy, level, collectibles;

    while (fgets(line, sizeof(line), file) != NULL && *count < 3) {
        if (sscanf(line, "%255s\t%255s\t%d\t%d\t%d\t%d\t%d", users[*count].username, users[*count].password, &score, &num_hearts, &energy, &level, &collectibles) == 7) {
            users[*count].pfp = NULL; // Will be set later
            users[*count].score = score;
            (*count)++;
        }
    }

    fclose(file);
}

void loadProfilePictures(user *users, int count) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open users file\n");
        return;
    }

    char line[512];
    char username[256], password[256], pfp_path[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%255s\t%255s\t%255s", username, password, pfp_path) == 3) {
            for (int i = 0; i < count; i++) {
                if (strcmp(users[i].username, username) == 0) {
                    strcpy(users[i].pfp_path, pfp_path);
                    users[i].pfp = IMG_Load(users[i].pfp_path);
                    if (!users[i].pfp) {
                        fprintf(stderr, "Unable to load profile picture: %s\n", users[i].pfp_path);
                    }
                    break;
                }
            }
        }
    }

    fclose(file);
}

void renderTopUsersWithPictures(SDL_Surface *ecran, TTF_Font *font, user *users, int count) {
    // Sort the users by score in descending order
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (users[j].score < users[j + 1].score) {
                user temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }

    SDL_Rect Pos1={960,200,50,50};
    SDL_Rect Pos2={960,400,50,50};
    SDL_Rect Pos3={960,600,50,50};

    // Render the top 3 users with profile pictures
    SDL_Color color = {255, 255, 255}; // White color
   // for (int i = 0; i < 3 && i < count; i++) {
       // int yOffset = 200 + i * 150; // Adjust vertical spacing as needed

        // Load and render the profile picture
        //SDL_Rect dstRect = {50,yOffset, 0, 0}; // Adjust positions as needed
            SDL_BlitSurface(users[0].pfp, NULL, ecran, &Pos1);
            SDL_BlitSurface(users[1].pfp, NULL, ecran, &Pos2);
            SDL_BlitSurface(users[2].pfp, NULL, ecran, &Pos3);

        

        // Render the username
        renderText(ecran, users[0].username, font, color, 150, 200);
        renderText(ecran, users[1].username, font, color, 150, 400);
        renderText(ecran, users[2].username, font, color, 150, 600);


        // Render the score below the username
        char scoreText1[256],scoreText2[256],scoreText3[256];
        snprintf(scoreText1, sizeof(scoreText1), "%d", users[0].score);
        snprintf(scoreText2, sizeof(scoreText2), "%d", users[1].score);
        snprintf(scoreText3, sizeof(scoreText3), "%d", users[2].score);

        renderText(ecran, scoreText1, font, color, 150, 200);
        renderText(ecran, scoreText2, font, color, 150, 200);
        renderText(ecran, scoreText3, font, color, 150, 200);
    //}
}

int Profile_Menu(SDL_Event event, SDL_Surface *ecran) {
    // Load background
    SDL_Surface* backg = IMG_Load("/home/aziz/Desktop/Digital_Intrusion/3.png");
    if (!backg) {
        printf("Error loading Profiles menu background\n");
        return -1;
    }

    // Initialize button
    Button pf;
    init_btn(&pf, "for ts/pfp_btn_0.png", "for ts/pfp_btn_1.png", 1546, 43);

   // SDL_Rect posBack = {1308, 0, backg->w, backg->h};        

    // Initialize font
    TTF_Font *font = TTF_OpenFont("/home/aziz/Desktop/Backup/Digital_Intrusion/arial.ttf", 24);
    if (!font) {
        printf("Error loading font: %s\n", TTF_GetError());
        SDL_FreeSurface(backg);
        return -1;
    }

    // Load users and their scores
    user users[100];
    int count = 0;
    loadTopUsers(users, &count);
    loadProfilePictures(users, count);

    // Main loop
    int running = 1;
    while (running) {
        SDL_BlitSurface(backg, NULL, ecran, NULL);
       
       renderTopUsersWithPictures(ecran, font, users, count);

        SDL_Flip(ecran);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                running = 0;
            }
          
        }
    }

    // Cleanup
    SDL_FreeSurface(backg);
    TTF_CloseFont(font);

    return 0;
}

