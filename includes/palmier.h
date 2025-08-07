#ifndef _palmier_h
#define _palmier_h
#include "jeu.h"
#include "struct.h"


Palmier *init_palmier(SDL_Renderer* ecran, int x, int y);
ListePalmiers *ajouter_en_tete_palmier(ListePalmiers *listePalmiers, Palmier *palmier);
ListePalmiers *genere_Palmier(Game *game, AllGraphics *allGraphics, ListePalmiers *listePalmiers);
ListePalmiers *detruirePalmier(ListePalmiers *listePalmiers);
void dessine_palmier(SDL_Renderer *ecran,SDL_Texture *palmierTexture,int x, int y, int w, int h);
void detruireListePalmiers(ListePalmiers *listePalmiers);
void afficheEtDeplacePalmiers(Game *game, AllGraphics *allGraphics, ListePalmiers *listePalmier);
void collisionPalmier(AllGraphics *allGraphics, Joueur *joueur, Palmier *palmier);
void gestionPalmier(Game *game, AllGraphics *allGraphics, Joueur *joueur, ListePalmiers **listePalmier) ;

#endif

