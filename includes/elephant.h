#ifndef _elephant_h
#define _elephant_h
#include "jeu.h"


Elephant *init_elephant(SDL_Renderer* ecran, int x, int y);
void dessine_elephant(Game *game, AllGraphics *allGraphics, Elephant *elephant);
void deplace_elephant(Elephant *elephant);
void collisionElephant(AllGraphics *allGraphics, Joueur *joueur, Elephant *elephant);

#endif