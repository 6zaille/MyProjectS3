#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Utilisation : %s <angle_en_degres> <nom_image>\n", argv[0]);
        return 1;
    }

    double angle = atof(argv[1]); // Récupérer l'angle en tant qu'argument en degrés
    char* imageFileName = argv[2]; // Récupérer le nom du fichier image en tant qu'argument

    if (angle < 0 || angle > 360) {
        printf("L'angle doit être compris entre 0 et 360 degrés.\n");
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* image = IMG_Load(imageFileName);
    if (!image) {
        SDL_Log("Erreur lors du chargement de l'image : %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Rotation d'image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, image->w, image->h, 0);
    if (!window) {
        SDL_Log("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_FreeSurface(image);
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_FreeSurface(image);
        SDL_Quit();
        return 1;
    }

    SDL_RenderCopyEx(renderer, SDL_CreateTextureFromSurface(renderer, image), NULL, NULL, angle, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(image);
    SDL_Quit();

    return 0;
}
