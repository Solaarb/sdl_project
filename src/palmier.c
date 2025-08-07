#include "palmier.h"



Palmier *init_palmier(SDL_Renderer* ecran, int x, int y){
  Palmier* palmier = (Palmier*)malloc(sizeof(Palmier));
  palmier->x = x;
  palmier->y = y;
  palmier->h = 64;
  palmier->w = 34;
  palmier->vitesse = 3;
  return palmier; 
}

void dessine_palmier(SDL_Renderer *ecran,SDL_Texture *palmierTexture,int x, int y, int w, int h){
  // position ou on veut dessiner le palmier (sur l'ecran)
  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.h=h*2;
  position.w=w*2;
  // position du palmier dans la texture
  SDL_Rect pos_texture;
  pos_texture.x=0;
  pos_texture.y = 0;
  pos_texture.h=h;
  pos_texture.w=w;

  SDL_RenderCopy(ecran, palmierTexture,&pos_texture, &position);
}

ListePalmiers *ajouter_en_tete_palmier(ListePalmiers *listePalmiers, Palmier *palmier){
// on ajoute le palmier à la liste des palmiers
  if (listePalmiers == NULL){
    listePalmiers = malloc(sizeof(ListePalmiers));
    listePalmiers->palmier = palmier;
    listePalmiers->suivant = NULL;
  } else {
    ListePalmiers *NouvelleListePalmiers = malloc(sizeof(ListePalmiers));
    NouvelleListePalmiers->palmier = palmier;
    NouvelleListePalmiers->suivant = listePalmiers;
    listePalmiers = NouvelleListePalmiers;
  }
  return listePalmiers;
}

void detruireListePalmiers(ListePalmiers *listePalmiers){
  ListePalmiers *tmp;
  while (listePalmiers != NULL) {
    tmp = listePalmiers;
    listePalmiers = listePalmiers->suivant;
    free(tmp->palmier);
    free(tmp);
  }
}

    
    
ListePalmiers * genere_Palmier(Game *game, AllGraphics *allGraphics, ListePalmiers *listePalmiers){
  //pourcentage d'apparition : %
  int random = rand() % 1000;

  int y = -100; 
  int x = (rand() % (SCREEN_WIDTH - 100));

  if (random < 20){
    //printf("NOUVEAU PALMIER");
    Palmier *palmier = init_palmier(game->ecran,x,y);
    listePalmiers = ajouter_en_tete_palmier(listePalmiers, palmier);
  }

  return listePalmiers;
}
    
    

ListePalmiers *detruirePalmier(ListePalmiers *listePalmiers){
  ListePalmiers *suivant = listePalmiers->suivant;
  free(listePalmiers->palmier);
  free(listePalmiers);
  //printf("palmier detruit");
  return suivant;
}
      
void collisionPalmier(AllGraphics *allGraphics, Joueur *joueur, Palmier *palmier){

  SDL_Rect palmier_box = { palmier->x, palmier->y, allGraphics->palmier_box.w, allGraphics->palmier_box.h };
  SDL_Rect joueur_box = { joueur->x, joueur->y, allGraphics->joueur_box.w, allGraphics->joueur_box.h };

  if (SDL_HasIntersection(&joueur_box,&palmier_box) && joueur->invincible == FALSE) {
    //printf("Collision detectee!\n");
    joueur->pv -= 1;
    joueur->invincible = TRUE; // active l'invincibilité

    allGraphics->clockInvincible = SDL_GetTicks(); 

    //printf("pv : %d \n", joueur->pv);
  }
}
      
void afficheEtDeplacePalmiers(Game *game, AllGraphics *allGraphics, ListePalmiers *listePalmier){
  ListePalmiers *tmp = listePalmier;
  while (tmp) {
    // Affiche le palmier
    dessine_palmier(game->ecran, allGraphics->palmierTexture, tmp->palmier->x, tmp->palmier->y, allGraphics->palmier_box.w, allGraphics->palmier_box.h);
    // Déplace le palmier
    tmp->palmier->y += tmp->palmier->vitesse;
    tmp = tmp->suivant;
  }
}

void gestionPalmier(Game *game, AllGraphics *allGraphics, Joueur *joueur, ListePalmiers **listePalmier) {
  *listePalmier = genere_Palmier(game, allGraphics, *listePalmier);
  ListePalmiers **tmp = listePalmier;

  while (*tmp != NULL) {
      if ((*tmp)->palmier->y > SCREEN_HEIGHT) {
          *tmp = detruirePalmier(*tmp); // supprime et relie le suivant
      } else {
          if (!joueur->invincible) {
              collisionPalmier(allGraphics, joueur, (*tmp)->palmier);
          }
          tmp = &(*tmp)->suivant;
      }
  }
}


