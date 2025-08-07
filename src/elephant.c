#include "elephant.h"


Elephant *init_elephant(SDL_Renderer* ecran, int x, int y){
    Elephant* elephant = (Elephant*)malloc(sizeof(Elephant));
    elephant->x = x;
    elephant->y = y;
    elephant->h = 64;
    elephant->w = 64;
    elephant->direction = rand() % 3; // 0 = diagonale gauche, 1 = bas, 2 = diagonale droite
    elephant->vitesse = 3;
    return elephant;
}

void dessine_elephant(Game *game, AllGraphics *allGraphics, Elephant *elephant){
    // position de l'elephant 
    SDL_Rect position;
    position.x = elephant->x;
    position.y = elephant->y;
    position.h=elephant->h;
    position.w=elephant->w;
  
    SDL_Rect pos_texture;
    pos_texture.x = 0;
    pos_texture.y = 0;
    pos_texture.h=elephant->h;
    pos_texture.w=elephant->w;
  
    SDL_RenderCopy(game->ecran, allGraphics->elephantTexture,&pos_texture, &position);
}


void deplace_elephant(Elephant *elephant){
    switch (elephant->direction) {
      case 0: // Diagonale gauche
        elephant->x -= elephant->vitesse;
        elephant->y += elephant->vitesse;
        break;
      case 1: // Bas
        elephant->y += elephant->vitesse*2.2;
        break;
      case 2: // Diagonale droite
        elephant->x += elephant->vitesse;
        elephant->y += elephant->vitesse;
        break;
    }
    // Change de direction si l'éléphant atteint le bord de l'écran
    if (elephant->x < 0 || elephant->x > SCREEN_WIDTH - elephant->w) {
      elephant->direction = (elephant->direction + 1) % 3; // Change de direction
    }
    if (elephant->y > SCREEN_HEIGHT + elephant->h) {
      elephant->y = -1000 + rand() % 951; // Valeur entre -2000 et -50
      elephant->x = rand() % (SCREEN_WIDTH - 100); 
      elephant->direction = rand() % 3; // Change de direction aléatoire
    }
  
}


void collisionElephant(AllGraphics *allGraphics, Joueur *joueur, Elephant *elephant) {

    SDL_Rect elephant_box = { elephant->x, elephant->y, allGraphics->elephant_box.w, allGraphics->elephant_box.h };
    SDL_Rect joueur_box = { joueur->x, joueur->y, allGraphics->joueur_box.w, allGraphics->joueur_box.h };


    if (SDL_HasIntersection(&joueur_box,&elephant_box) && joueur->invincible == FALSE) {
        //printf("Collision detectee!\n");
        joueur->pv -= 1;
        joueur->invincible = TRUE; // active l'invincibilité

        allGraphics->clockInvincible = SDL_GetTicks(); 

        //printf("pv : %d \n", joueur->pv);
    }
}