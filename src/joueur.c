#include "joueur.h"

Joueur *init_joueur(SDL_Renderer* ecran){
  Joueur* joueur = (Joueur*)malloc(sizeof(Joueur));
  joueur->x = SCREEN_WIDTH/2 - 32;
  joueur->y = SCREEN_HEIGHT/1.5;
  joueur->h = 64;
  joueur->w = 64;
  joueur->vitesse = 10;
  joueur->pv = PV_MAX;
  joueur->invincible = FALSE; //bool
  return joueur;
}

void dessine_joueur(SDL_Renderer *ecran,SDL_Texture *joueurTexture,int x, int y, int w, int h, Joueur *joueur)
{

  // position o� on veut dessiner le joueur (sur l'�cran)
  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.h=h;
  position.w=w;
  // position du joueur numero *numero_joueur dans la texture
  SDL_Rect pos_texture;
  pos_texture.x = 0;
  pos_texture.y = 0;
  pos_texture.h=h;
  pos_texture.w=w;

  if (joueur->invincible) {
    SDL_SetTextureColorMod(joueurTexture, 255, 0, 0); // Change la couleur en rouge
  } else {
    SDL_SetTextureColorMod(joueurTexture, 255, 255, 255); // Couleur normale
  }


  SDL_RenderCopy(ecran, joueurTexture,&pos_texture, &position);
}



int event_joueur(Game *game, Joueur *joueur, SDL_Event event, AllGraphics *allGraphics ) {
  switch (game->e.key.keysym.sym) {

    case SDLK_UP:
    case SDLK_z:
      joueur->y -= joueur->vitesse;
      if (joueur->y < 0) 
        joueur->y = 0; // bord haut
      return 1;

    case SDLK_DOWN:
    case SDLK_s:
      joueur->y += joueur->vitesse;
      if (joueur->y > SCREEN_HEIGHT - allGraphics->joueur_box.h) 
        joueur->y = SCREEN_HEIGHT - allGraphics->joueur_box.h; // bord bas
      return 1;

    case SDLK_LEFT:
    case SDLK_q:
      joueur->x -= joueur->vitesse;
      if (joueur->x < -allGraphics->joueur_box.w) 
        joueur->x = SCREEN_WIDTH; // bord gauche
      return 1;
      
    case SDLK_RIGHT:
    case SDLK_d:
      joueur->x += joueur->vitesse;
      if (joueur->x > SCREEN_WIDTH) 
        joueur->x = -allGraphics->joueur_box.h; // bord droite
      return 1;

    case SDLK_ESCAPE:
      game->quit=TRUE; 
    return 1;
  }
  return 0;
}



