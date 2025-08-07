#ifndef _struct_h
#define _struct_h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL.h>

#define PV_MAX 5// nombre de coeurs max


typedef struct s_palmier{
    int x, y;
    int h,w;
    int vitesse;
} Palmier;

typedef struct s_liste_palmiers{
    int numero;
    Palmier *palmier;
    struct s_liste_palmiers *suivant;
} ListePalmiers;

typedef enum s_statutJeu{
    MENU,
    JEU,
    GAMEOVER,
    QUIT
} statutJeu;

typedef struct s_game {
    int success;
    int quit ;
    int nb_frames;
    SDL_Window* fenetre;
    SDL_Renderer* ecran;
    SDL_Event e;
    SDL_Texture* sceneFixeTexture;
    statutJeu etatJeu;
} Game;

typedef struct s_elephant{
    int x, y;
    int h,w;
    int direction; // 0 = diagonale gauche, 1 = bas, 2 = diagonale droite, 
    int vitesse;
    bool vivant;
} Elephant;



typedef struct s_coeur{
    int x, y;
    int h, w;
} Coeur;

typedef struct s_joueur{
    int x, y;
    int h, w;
    int pv;
    int vitesse;
    int invincible; //bool
    Coeur *tab_coeur[PV_MAX]; // tableau de 3 coeurs

} Joueur;

typedef struct s_graphics{
    SDL_Rect joueur_box, palmier_box, elephant_box, coeur_box;
    SDL_Texture* elephantTexture;
    SDL_Texture* joueurTexture;
    SDL_Texture* palmierTexture;
    SDL_Texture* coeurTexture;

    
    clock_t clockInvincible;
    int invincibleTime;
    int invincibleTimeMax;
    double elapsedTimeInv;
} AllGraphics;



#endif