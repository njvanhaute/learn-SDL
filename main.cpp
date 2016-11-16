//
//  main.cpp
//  learnSDL
//
//  Created by Nicholas Vanhaute on 11/15/16.
//  Copyright © 2016 Nicholas Vanhaute. All rights reserved.
//

// Using SDL and stdio
#include <SDL2/SDL.h>
#include <stdio.h>

// The window we'll be rendering to
SDL_Window *gWindow = NULL;
// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;
// The image we will load and show on the screen
SDL_Surface *gHelloWorld = NULL;

// Screen dimension constants
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window
bool init(void);
// Loads media
bool loadMedia(void);
// Frees media and shuts down SDL
void close(void);

int main(int argc, char **argv) {
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        // Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        }
        else {
            // Apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
            SDL_Delay(2000);
        }
    }
    close();
    return 0;
}

bool init(void) {
    // Initialization flag
    bool success = true;
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Create a window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!gWindow) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia(void) {
    // Loading success flag
    bool success = true;
    // Load splash image
    gHelloWorld = SDL_LoadBMP("hello.bmp");
    if (!gHelloWorld) {
        printf("Unable to load image! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

void close(void) {
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}
