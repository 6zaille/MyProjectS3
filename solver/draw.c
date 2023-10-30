#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 768
#define HEIGHT 768
#define CELL_SIZE (WIDTH / 9)

void drawSudokuNumbers(SDL_Surface *surface, TTF_Font *font, const char *filename, const char *original) {
    FILE *file = fopen(filename, "r");
    FILE *origFile = fopen(original, "r");
    if (!file || !origFile) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char line[11];
    char origLine[11];
    SDL_Color initialTextColor = {0, 0, 0, 255};  // Noir pour les chiffres initiaux
    SDL_Color algorithmTextColor = {255, 0, 0, 255};  // Rouge pour les chiffres ajoutés par l'algorithme
    
    for (int y = 0; y < 9; y++) {
        fgets(line, sizeof(line), file);
        fgets(origLine, sizeof(origLine), origFile);
        
        for (int x = 0; x < 9; x++) {
            if (line[x * 2] != ' ') {
                char numStr[2] = {line[x * 2], '\0'};
                SDL_Color currentColor = (line[x * 2] == origLine[x * 2]) ? initialTextColor : algorithmTextColor;
                
                SDL_Surface *textSurface = TTF_RenderText_Solid(font, numStr, currentColor);
                if(!textSurface) {
                    printf("Error with character: %c\n", line[x*2]);
                    continue;
                }

                SDL_Rect destRect = {
                    (CELL_SIZE * x) + (CELL_SIZE / 2) - (textSurface->w / 2),
                    (CELL_SIZE * y) + (CELL_SIZE / 2) - (textSurface->h / 2),
                    textSurface->w, 
                    textSurface->h
                };
                
                SDL_BlitSurface(textSurface, NULL, surface, &destRect);
                SDL_FreeSurface(textSurface);
            }
        }
    }

    fclose(file);
    fclose(origFile);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1 || IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("/nix/store/5767wphpxwfgsh0d9ijn254bg58gn39k-liberation-fonts-2.1.0/share/fonts/truetype/LiberationSans-Regular.ttf", 48);
    if (font == NULL) {
        printf("Erreur chargement font: %s\n", TTF_GetError());
        return 1;
    }
    
    SDL_Surface *baseSurface = IMG_Load("empty_grid_9x9.jpeg");
    if (!baseSurface) {
        printf("Erreur chargement image: %s\n", IMG_GetError());
        return 1;
    }

    drawSudokuNumbers(baseSurface, font, argv[1], argv[2]);  // Ajout d'un second fichier en argument qui contient la grille initiale

    char outputfilename[256];
    strncpy(outputfilename, argv[1], sizeof(outputfilename) - 5);
    strcat(outputfilename, ".jpeg");
    
    IMG_SaveJPG(baseSurface, outputfilename, 100); 

    SDL_FreeSurface(baseSurface);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}