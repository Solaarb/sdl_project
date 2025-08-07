#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "jeu.h"


int init(SDL_Window** gWindow,SDL_Renderer** gRenderer, char* nameWindow) {
	//Initialization flag
	int success = TRUE;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = FALSE;
	} else {
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			printf( "Warning: Linear texture filtering not enabled!" );
		//Create window
		*gWindow = SDL_CreateWindow(nameWindow, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( *gWindow == NULL) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = FALSE;
		} else {
			//Create vsynced renderer for window
			*gRenderer = SDL_CreateRenderer( *gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( *gRenderer == NULL) {
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = FALSE;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor( *gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	return success;
}

Game *init_game(){
    Game *game = (Game*)malloc(sizeof(Game));
    game->success = FALSE;
    game->fenetre = NULL;
    game->ecran = NULL;
    game->quit = FALSE;
    game->nb_frames = 0;
    game->sceneFixeTexture=NULL;
    game->etatJeu = MENU;
    return game;
}



void close(SDL_Window** gWindow,SDL_Renderer** gRenderer)
{


	//Destroy window
	SDL_DestroyRenderer( *gRenderer );
	SDL_DestroyWindow(* gWindow );
	*gWindow = NULL;
	*gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


double getCurrentTimeMS()
{
    double clo=clock();
    return 1000.*clo/CLOCKS_PER_SEC;
}

SDL_Texture* creerTextureGenerique(SDL_Renderer *ecran,char *nom_file_bmp,int *size_w, int *size_h)
{
    SDL_Surface* image = SDL_LoadBMP(nom_file_bmp);
    if(!image)
    {
      printf("Erreur de chargement de l'image : %s",SDL_GetError());
      return NULL;
    }

    SDL_Texture* monImage = SDL_CreateTextureFromSurface(ecran,image);
    SDL_FreeSurface(image);

    if(NULL == monImage)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    SDL_QueryTexture(monImage, NULL, NULL,size_w,size_h); // on recup�re la taille de l'image


    return monImage;
}

void dessine_rect_plein(SDL_Renderer *gRenderer,SDL_Rect *rect,long c)
{
   int r = ( uint8_t )(c >> 16);
   int g = ( uint8_t )(c >>  8);
   int b = (  uint8_t  )c;
   SDL_SetRenderDrawColor( gRenderer,r,g,b,255);
   SDL_RenderFillRect( gRenderer,rect);
}

void dessine_cercle(SDL_Renderer *gRenderer,int centreX,int centreY,int radius, long c)
{
  const int32_t diameter = (radius * 2);

  int32_t x = (radius - 1);
  int32_t y = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - diameter);

  int r = ( uint8_t )(c >> 16);
  int g = ( uint8_t )(c >>  8);
  int b = (  uint8_t  )c;
  SDL_SetRenderDrawColor( gRenderer,r,g,b,255);

  while (x >= y)
  {
    // Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(gRenderer, centreX + x, centreY - y);
    SDL_RenderDrawPoint(gRenderer, centreX + x, centreY + y);
    SDL_RenderDrawPoint(gRenderer, centreX - x, centreY - y);
    SDL_RenderDrawPoint(gRenderer, centreX - x, centreY + y);
    SDL_RenderDrawPoint(gRenderer, centreX + y, centreY - x);
    SDL_RenderDrawPoint(gRenderer, centreX + y, centreY + x);
    SDL_RenderDrawPoint(gRenderer, centreX - y, centreY - x);
    SDL_RenderDrawPoint(gRenderer, centreX - y, centreY + x);

    if (error <= 0)
    {
      ++y;
      error += ty;
      ty += 2;
    }

    if (error > 0)
    {
      --x;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

void ligneHorizontale(SDL_Renderer *gRenderer,int x, int y, int w, long c)
{
  SDL_Rect rect;
  int r = ( uint8_t )(c >> 16);
  int g = ( uint8_t )(c >>  8);
  int b = (  uint8_t  )c;

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = 1;

  SDL_SetRenderDrawColor( gRenderer,r,g,b,255);
  SDL_RenderFillRect( gRenderer,&rect);
}

void dessine_disque(SDL_Renderer *gRenderer,int cx, int cy, int rayon, long coul)
{
  int d, y, x;

  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;

  while (y >= x) {
    ligneHorizontale(gRenderer,cx - x, cy - y, 2 * x + 1, coul);
    ligneHorizontale(gRenderer,cx - x, cy + y, 2 * x + 1, coul);
    ligneHorizontale(gRenderer,cx - y, cy - x, 2 * y + 1, coul);
    ligneHorizontale(gRenderer,cx - y, cy + x, 2 * y + 1, coul);

    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }

    x++;
  }
}



SDL_Texture *creerTextureMenuStart(SDL_Renderer*ecran){
  SDL_Texture* sceneFixe=NULL;
  sceneFixe=SDL_CreateTexture(ecran,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);
  SDL_SetRenderTarget(ecran, sceneFixe); //on modifie la texture

  SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Texture* startMenuTexture = creerTextureGenerique(ecran, "./img/startMenu.bmp", &rect.w, &rect.h);
  if (startMenuTexture) {
    SDL_RenderCopy(ecran, startMenuTexture, NULL, &rect);
    SDL_DestroyTexture(startMenuTexture);
  }
  SDL_SetRenderTarget(ecran, NULL);

  return sceneFixe;// Dor�navant, on modifie � nouveau le renderer
}

SDL_Texture *creerTextureGameOver(SDL_Renderer*ecran){
  SDL_Texture* sceneFixe=NULL;
  sceneFixe=SDL_CreateTexture(ecran,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);
  SDL_SetRenderTarget(ecran, sceneFixe); //on modifie la texture

  SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Texture* startMenuTexture = creerTextureGenerique(ecran, "./img/gameOver.bmp", &rect.w, &rect.h);
  if (startMenuTexture) {
    SDL_RenderCopy(ecran, startMenuTexture, NULL, &rect);
    SDL_DestroyTexture(startMenuTexture);
  }
  SDL_SetRenderTarget(ecran, NULL);

  return sceneFixe;// Dor�navant, on modifie � nouveau le renderer
}


SDL_Texture *creerTextureSceneFixe(SDL_Renderer*ecran)
{
    SDL_Texture* sceneFixe=NULL;

    sceneFixe=SDL_CreateTexture(ecran,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL_SetRenderTarget(ecran, sceneFixe); //on modifie la texture
    
    // dessine sol
    SDL_Rect sol={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    dessine_rect_plein(ecran,&sol,Sable);
    
    SDL_SetRenderTarget(ecran, NULL);

    return sceneFixe;// Dor�navant, on modifie � nouveau le renderer
}

void dessine_sceneFixe(SDL_Renderer *ecran, SDL_Texture *sceneFixe)
{
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    SDL_QueryTexture(sceneFixe, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(ecran, sceneFixe, NULL, &position);
}





void destroyAll(Game *game, AllGraphics* allGraphics, ListePalmiers *listePalmier, Joueur *joueur, Elephant *elephant[3]) {
  // destruction des textures
  if (game->sceneFixeTexture){
    SDL_DestroyTexture(game->sceneFixeTexture);game->sceneFixeTexture=NULL;
  }
  if (allGraphics->elephantTexture) {
    SDL_DestroyTexture(allGraphics->elephantTexture);allGraphics->elephantTexture=NULL;
  }
  if (allGraphics->joueurTexture) {
    SDL_DestroyTexture(allGraphics->joueurTexture);allGraphics->joueurTexture=NULL;
  }
  if (allGraphics->palmierTexture){
    SDL_DestroyTexture(allGraphics->palmierTexture);allGraphics->palmierTexture=NULL;
  }
  //if (sorbonneTexture) {SDL_DestroyTexture(sorbonneTexture);sorbonneTexture=NULL;}

  detruireListePalmiers(listePalmier);
  for (int i = 0; i < 3; i++) {
    free(elephant[i]);
  }
  free(joueur);
  free(allGraphics);
  free(game);
  
  // ferme ecran et fenetre
  close(&game->fenetre,&game->ecran);
}



void renderAll(Game *game, AllGraphics *allGraphics, ListePalmiers *listePalmier, Joueur *joueur, Elephant *elephant[3]) {
  //nettoie �cran
  SDL_SetRenderDrawColor( game->ecran, 0xFF, 0xFF, 0xFF, 0xFF );
  SDL_RenderClear(game->ecran);

  // dessine la scene/decor de fond
  dessine_sceneFixe(game->ecran, game->sceneFixeTexture);

  // Affiche et déplace tous les palmiers
  afficheEtDeplacePalmiers(game, allGraphics, listePalmier);

  // Affiche les éléphants
  for (int i = 0; i < 3; i++) {
    dessine_elephant(game, allGraphics, elephant[i]);
  }

  // Affiche le joueur
  dessine_joueur(game->ecran, allGraphics->joueurTexture, joueur->x, joueur->y, allGraphics->joueur_box.w, allGraphics->joueur_box.h, joueur);
  
  //affiche les coeurs
  dessine_vie(game->ecran, allGraphics, joueur);

  SDL_RenderPresent(game->ecran);
  game->nb_frames++;
}


Coeur *init_coeur(SDL_Renderer* ecran, int x){
  Coeur *coeur = (Coeur*)malloc(sizeof(Coeur));
  coeur->x = x+10;
  coeur->y = 10;
  coeur->h = 64/2;
  coeur->w = 64/2;
  return coeur;
}

AllGraphics *init_AllGraphics(SDL_Renderer* ecran, Joueur *joueur, Palmier *palmier){
  AllGraphics *graphics = (AllGraphics*)malloc(sizeof(AllGraphics));
  graphics->elephantTexture = creerTextureGenerique(ecran,"./img/elephant.bmp",&graphics->elephant_box.w, &graphics->elephant_box.h);
  graphics->joueurTexture = creerTextureGenerique(ecran,"./img/joueur.bmp",&graphics->joueur_box.w, &graphics->joueur_box.h);
  graphics->palmierTexture = creerTextureGenerique(ecran,"./img/palmier.bmp",&graphics->palmier_box.w, &graphics->palmier_box.h);
  graphics->coeurTexture = creerTextureGenerique(ecran,"./img/coeur.bmp",&graphics->coeur_box.w, &graphics->coeur_box.h);
  graphics->invincibleTime = 0;
  graphics->invincibleTimeMax = 2; // 2s d'invincibilite
  graphics->elapsedTimeInv = 0.5;
  return graphics;
}

void menu(Game* game, Joueur *joueur, AllGraphics *allGraphics) {
  gestionEtatJeu(game, joueur, allGraphics);

  // ecran press space to start
  SDL_SetRenderDrawColor( game->ecran, 0xFF, 0xFF, 0xFF, 0xFF );
  SDL_RenderClear(game->ecran);
  game->sceneFixeTexture=creerTextureMenuStart(game->ecran);
  dessine_sceneFixe(game->ecran, game->sceneFixeTexture);
  SDL_RenderPresent(game->ecran);
}













void detectionMort(Game *game, Joueur *joueur){
  if (joueur->pv <= 0){
    printf("\nVous etes mort !\n");
    game->etatJeu= GAMEOVER;
  }
}






// void gameplay( Game **game, AllGraphics **allGraphics, ListePalmiers **listePalmier, Joueur **joueur, double previous, double lag) {
//       // controle du temps pour les update (partie2)
//       double current = getCurrentTimeMS();
//       double elapsed = current - previous;
//       previous = current;
//       lag += elapsed;

//       //animation_joueur(game,joueur,previous);

//       /* ENTREES/INPUT */
//       while (SDL_PollEvent(&(*game)->e)) {
//           if ((*game)->e.type == SDL_QUIT) {
//               (*game)->quit = TRUE;
//           }
//           event_joueur(*game, *joueur,(*game)->e, *allGraphics);
//       }
      
//       while (lag >= MS_PER_UPDATE)
//       {
//           /* MISE A JOUR/UPDATE */
//           lag -= MS_PER_UPDATE;
//       }

//       *listePalmier = genere_Palmier(*game, *allGraphics, *listePalmier);
//       ListePalmiers **tmp = listePalmier;

//       while (*tmp != NULL) {
//           //detection collision palmier
//           if ((*tmp)->palmier->y > SCREEN_HEIGHT) {
//               *tmp = detruirePalmier(*tmp); // Supprime l'élément et met à jour le pointeur
//           } else {
//               if (!(*joueur)->invincible) { // Vérifie si le joueur n'est pas invincible
//                   collisionPalmier(*allGraphics, *joueur, (*tmp)->palmier);
//               }
//               tmp = &(*tmp)->suivant; // Passe à l'élément suivant
//           }
//       }
//       invincibleTime(*allGraphics, *joueur);
//       detectionMort(*game, *joueur);
//       renderAll(*game, *allGraphics, *listePalmier, *joueur, elephant);
//   }

void dessine_vie(SDL_Renderer *ecran, AllGraphics *allGraphics, Joueur *joueur) {
  for (int i = 0; i < joueur->pv; i++) {
    Coeur *coeur = joueur->tab_coeur[i];
    SDL_Rect vieBox = { coeur->x, coeur->y, coeur->w, coeur->h };
    SDL_RenderCopy(ecran, allGraphics->coeurTexture, NULL, &vieBox);
  }
}

void invincibleTime(AllGraphics *allGraphics, Joueur *joueur) {
  if (joueur->invincible) {
      double currentTime = SDL_GetTicks(); // Temps actuel en millisecondes
      double elapsedTime = (currentTime - allGraphics->clockInvincible) / 1000.0; // Temps écoulé en secondes

      if (elapsedTime >= allGraphics->invincibleTimeMax) { // Vérifie si le temps d'invincibilité est écoulé
          joueur->invincible = FALSE; 
          //printf("Invincibilité terminée\n");
      }
  }
}
  
void game_over(Game *game, Joueur *joueur, AllGraphics *allGraphics){

  gestionEtatJeu(game, joueur, allGraphics);

  // affichage ecran game over
  SDL_SetRenderDrawColor( game->ecran, 0xFF, 0xFF, 0xFF, 0xFF );
  SDL_RenderClear(game->ecran);
  game->sceneFixeTexture=creerTextureGameOver(game->ecran);
  dessine_sceneFixe(game->ecran, game->sceneFixeTexture);
  
  SDL_RenderPresent(game->ecran);
  game->nb_frames++;
}



void gestionEtatJeu(Game *game, Joueur *joueur, AllGraphics *allGraphics) {
  while (SDL_PollEvent(&game->e)) {
    if (game->e.type == SDL_QUIT) {
        game->quit = TRUE;
    }
    switch (game->e.type) {
      case SDL_KEYDOWN:
      {
        switch (game->e.key.keysym.sym) {
          case SDLK_SPACE:
            if(game->etatJeu == MENU) 
              game->etatJeu = JEU;

            else if (game->etatJeu == GAMEOVER) 
              game->quit = TRUE;
          
            break;
          case SDLK_ESCAPE:
            game->quit = TRUE;
            break;
        }
        event_joueur(game, joueur,game->e, allGraphics);
      }
    }
  }
}


void scoreAffichage(double lag, double previous){
  double current = getCurrentTimeMS();
  double elapsed = current - previous;
  previous = current;
  lag += elapsed;
  lag /= 700;
  
  printf("\rScore : %.0f", lag);
}
