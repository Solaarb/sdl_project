#ifndef _joueur_h
#define _joueur_h

#include "jeu.h"

Joueur *init_joueur(SDL_Renderer* ecran);
void dessine_joueur(SDL_Renderer *ecran,SDL_Texture *joueurTexture,int x, int y, int w, int h, Joueur *joueur);
int event_joueur (Game *game, Joueur *joueur, SDL_Event event, AllGraphics *allGraphics);

#endif