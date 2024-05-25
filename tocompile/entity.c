#include "perso.h"




void move_and_animate_drone(Entity *drone, Entity *laser) {
    Uint32 current_time = SDL_GetTicks();

    if (drone->state == 1) { // Moving
        drone->pos.x += drone->dx;

        // Bounce off the walls
        if (drone->pos.x <= 50) {
            drone->dx = 5;
        } else if (drone->pos.x >= 1800) {
            drone->dx = -5;
        }

        // Randomly decide to pause
        if (rand() % 200 < 1) { // Approx 1% chance per frame
            drone->state = 0;
            drone->txt_cour = current_time; // Using txt_cour as the pause start time

            // Drop the laser when pausing
            drop_laser(laser, drone);
        }

    } else if (drone->state == 0) { // Pausing
        if (current_time - drone->txt_cour >= 2000) { // Paused for 2 seconds
            drone->state = 1;
        }
    }

}

void drop_laser(Entity *laser, Entity *drone) {
    if (!laser->active) {
        laser->pos.x = drone->pos.x + drone->pos.w / 2 - laser->pos.w / 2;
        laser->pos.y = drone->pos.y + drone->pos.h;
        laser->active = true;
    }
}


void move_laser(Entity *laser) {
    if (laser->active) {
        laser->pos.y += 10; // Laser falling speed
        if (laser->pos.y >= 700) { // Assuming ground level is at y=480
            laser->pos.x=0;
            laser->pos.y=0;
            laser->active = false;
        }
    }
}

void handle_FB_health(Entity *hacker, SDL_Rect laser) {
    // Check for collision between hacker and player's laser
    if (checkCollision(&hacker->pos, &laser)) {
        // Decrease hacker's health when hit
        hacker->health -= 1; // Adjust damage amount as needed

        // Optionally, check if hacker's health drops to zero and handle defeat or other events
          
    }
}
void render_hacker_health(Entity *hacker, SDL_Surface *ecran, TTF_Font *font, Uint32 transitionDuration) {
    // Calculate position for health text in the middle of the screen
    

    // Render health text
    char health_text[30];
    snprintf(health_text, sizeof(health_text), "Final Boss's Health: %d", hacker->health);
    
    // Calculate transition progress (0 to 1)
    Uint32 currentTime = SDL_GetTicks();
    double progress = (currentTime % transitionDuration) / (double)transitionDuration;

    // Calculate text color based on transition progress
    SDL_Color textColor;
    if (progress <= 0.5) { // First half of transition, change to red
        int red = (int)(255 * (1 - 2 * progress)); // Fade to red
        textColor = (SDL_Color){255, red, red}; // Red color (fade)
    } else { // Second half of transition, change back to white
        int red = (int)(255 * (2 * progress - 1)); // Fade to white
        textColor = (SDL_Color){255, red, red}; // White color (fade)
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, health_text, textColor);
    int health_x = (ecran->w - textSurface->w) / 2; // Center horizontally
    int health_y = 1000; // Center vertically
    SDL_BlitSurface(textSurface, NULL, ecran, &(SDL_Rect){health_x, health_y, 0, 0});
    SDL_FreeSurface(textSurface);
}

void checkLaserCollision(SDL_Rect playerRect, SDL_Rect laserRect, int *playerHearts) {
    // Static variables to keep track of the last collision time and cooldown duration
    static Uint32 lastCollisionTime = 0;
    const Uint32 cooldownDuration = 1000; // Cooldown duration in milliseconds (adjust as needed)

    // Get the current time
    Uint32 currentTime = SDL_GetTicks();

    // Check if enough time has passed since the last collision
    if (currentTime - lastCollisionTime < cooldownDuration) {
        return; // Collision is still on cooldown
    }

    // Check if player rectangle intersects with the laser rectangle
    bool collision = (playerRect.x < laserRect.x + laserRect.w &&
                      playerRect.x + playerRect.w > laserRect.x &&
                      playerRect.y < laserRect.y + laserRect.h &&
                      playerRect.y + playerRect.h > laserRect.y);

    // If collision occurred, decrease player's number of hearts by 2 and update last collision time
    if (collision) {
        *playerHearts -= 2;
        lastCollisionTime = currentTime;
    }
}


void initColorFade(ColorFade *fade, Uint8 startR, Uint8 startG, Uint8 startB, Uint8 endR, Uint8 endG, Uint8 endB, Uint32 duration) {
    fade->startR = startR;
    fade->startG = startG;
    fade->startB = startB;
    fade->endR = endR;
    fade->endG = endG;
    fade->endB = endB;
    fade->startTime = SDL_GetTicks();
    fade->duration = duration;
}
void interpolateColor(Uint8 *r, Uint8 *g, Uint8 *b, Uint8 r1, Uint8 g1, Uint8 b1, Uint8 r2, Uint8 g2, Uint8 b2, float t) {
    *r = (Uint8)((1 - t) * r1 + t * r2);
    *g = (Uint8)((1 - t) * g1 + t * g2);
    *b = (Uint8)((1 - t) * b1 + t * b2);
}

// Function to update screen color
void updateScreenColor(SDL_Surface *screen, ColorFade *fade) {
    Uint32 currentTime = SDL_GetTicks();
    float t = (float)(currentTime - fade->startTime) / fade->duration;

    // Loop the animation
    if (t > 1.0f) {
        fade->startTime = SDL_GetTicks();
        Uint8 tempR = fade->startR, tempG = fade->startG, tempB = fade->startB;
        fade->startR = fade->endR; fade->startG = fade->endG; fade->startB = fade->endB;
        fade->endR = tempR; fade->endG = tempG; fade->endB = tempB;
        t = 0.0f;
    }

    // Interpolate the color
    Uint8 r, g, b;
    interpolateColor(&r, &g, &b, fade->startR, fade->startG, fade->startB, fade->endR, fade->endG, fade->endB, t);

    // Fill the screen with the current color
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, r, g, b));

    // Update the screen
    SDL_Flip(screen);
}