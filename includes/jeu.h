
/*
Sorbonne Universite/LEEA/LU2EE21

Interface graphique simplifiee

Contributeurs : Xavier Clady, xavier.clady@sorbonne-uniersite.fr

version : 1.1
cr�ation : 03/2020

Derniere modif :
- utilisation des textures pour dessiner les diff�rents objets du jeu (sceneFixe, Viseur, Target,..)
- dessine ellipse pleine
- dessine ellipse vide

Ressources :
- SDL2
- bib libgraphic de Bruno Gas
- Lazy Foo' Productions: https://lazyfoo.net/tutorials/SDL
- https://fr.wikibooks.org/wiki/Programmation_avec_la_SDL/Les_textures
*/


#ifndef _jeu_h
#define _jeu_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL.h>

#include "struct.h"
#include "elephant.h"
#include "palmier.h"
#include "joueur.h"

// taille fenetre
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
// vrai/faux
#define FALSE 0
#define TRUE 1
// pi
#define PI 3.14159265359
// MS per
#define MS_PER_UPDATE 1./60
//couleurs pr�d�finies
#define rgb2pixel(r,g,b) 			((long) ( (( uint8_t )r)<<8 | (( uint8_t )g))<<8 | (( uint8_t )b) )
#define Black						rgb2pixel(0  ,0   ,   0)
#define White						rgb2pixel(255,255 , 255)
#define Gray 						rgb2pixel(190, 190, 190)
#define LightGrey					rgb2pixel(211, 211, 211)
#define DarkGray					rgb2pixel(169, 169, 169)
#define NavyBlue					rgb2pixel(  0,   0, 128)
#define RoyalBlue					rgb2pixel( 65, 105, 225)
#define SkyBlue						rgb2pixel(135, 206, 235)
#define Blue						rgb2pixel(0  , 0  , 255)
#define LightBlue					rgb2pixel(173, 216, 230)
#define MidnightBlue				rgb2pixel(25 , 25 , 112)
#define Cyan 						rgb2pixel(  0, 255, 255)
#define LightCyan					rgb2pixel(224, 255, 255)
#define DarkCyan					rgb2pixel(0  , 139, 139)
#define Green						rgb2pixel(0  , 255,   0)
#define DarkGreen					rgb2pixel(  0, 100,   0)
#define LightGreen					rgb2pixel(144, 238, 144)
#define YellowGreen					rgb2pixel(154, 205,  50)
#define LightYellow					rgb2pixel(255, 255, 224)
#define IndianRed					rgb2pixel(205,  92,  92)
#define Sienna						rgb2pixel(160, 82 ,  45)
#define Beige						rgb2pixel(245, 245, 220)
#define Brown						rgb2pixel(165,  42,  42)
#define Orange						rgb2pixel(255, 165,   0)
#define DarkOrange					rgb2pixel(255, 140,   0)
#define LightCoral					rgb2pixel(240, 128, 128)
#define Pink						rgb2pixel(255, 192, 203)
#define LightPink					rgb2pixel(255, 182, 193)
#define Red							rgb2pixel(255, 0  ,   0)
#define DarkRed						rgb2pixel(139, 0  ,   0)
#define VioletRed					rgb2pixel(208,  32, 144)
#define Magenta						rgb2pixel(255,   0, 255)
#define DarkMagenta					rgb2pixel(139,   0, 139)
#define Violet						rgb2pixel(238, 130, 238)
#define DarkViolet					rgb2pixel(148,   0, 211)
#define Purple						rgb2pixel(160,  32, 240)
#define Gold1						rgb2pixel(255, 215,   0)
#define Gold2						rgb2pixel(238, 201,   0)
#define Gold3						rgb2pixel(205, 173,   0)
#define Gold4						rgb2pixel(139, 117,   0)
#define Sable						rgb2pixel(235, 220,  80)





// init/close fenetre + ecran
void close(SDL_Window** gWindow,SDL_Renderer** gRenderer);
int init(SDL_Window** gWindow,SDL_Renderer** gRenderer, char* nameWindow);
AllGraphics *init_AllGraphics(SDL_Renderer* ecran, Joueur *joueur, Palmier *palmier);
Coeur *init_coeur(SDL_Renderer* ecran, int x);
Game *init_game();
void menu(Game* game, Joueur *joueur, AllGraphics *allGraphics);


void dessine_sceneFixe(SDL_Renderer *ecran, SDL_Texture *sceneFixe);
SDL_Texture *creerTextureSceneFixe(SDL_Renderer*ecran);
SDL_Texture* creerTextureGenerique(SDL_Renderer *ecran,char *nom_file_bmp,int *size_w, int *size_h);
SDL_Texture *creerTextureMenuStart(SDL_Renderer*ecran);
SDL_Texture *creerTextureGameOver(SDL_Renderer*ecran);

void destroyAll(Game *game, AllGraphics *allGraphics, ListePalmiers *listePalmier, Joueur *joueur, Elephant *elephant[3]);
void renderAll(Game *game, AllGraphics *allGraphics, ListePalmiers *listePalmier, Joueur *joueur, Elephant *elephant[3]);

void scoreAffichage(double lag, double previous);



void detectionMort(Game *game, Joueur *joueur);
void invincibleTime(AllGraphics *allGraphics, Joueur *joueur);
void dessine_vie(SDL_Renderer *ecran, AllGraphics *allGraphics, Joueur *joueur);

double getCurrentTimeMS();
void game_over(Game *game, Joueur *joueur, AllGraphics *allgraphics );
void gestionEtatJeu(Game *game, Joueur *joueur, AllGraphics *allGraphics);



#endif // _jeu_h
