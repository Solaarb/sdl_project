#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "jeu.h"

int main (int argc, char** argv){
    srand(time(NULL));
    Game *game = init_game();
    game->success=init(&game->fenetre,&game->ecran,"Mon Jeu");

    int x = (rand() % (SCREEN_WIDTH - 100)); 
    int y = -50; 
    
    Palmier *palmier = init_palmier(game->ecran,x,y);
    ListePalmiers *listePalmier = ajouter_en_tete_palmier(NULL, palmier);

    Elephant *elephant[3];
    Joueur *joueur = init_joueur(game->ecran);
    AllGraphics *allGraphics = init_AllGraphics(game->ecran,joueur, palmier);

    //initialisation des coeurs
    for (int i = 0; i < joueur->pv; i++) {
        joueur->tab_coeur[i] = init_coeur(game->ecran, i*40);
    }

    //initialisation des 3 elephants
    for(int i = 0; i < 3; i++){
        x = (rand() % (SCREEN_WIDTH - 100));
        y = (rand() % (SCREEN_HEIGHT - 100));
        elephant[i] = init_elephant(game->ecran,x,y);
    }

    if( !game->success ) {
        fprintf(stderr,"Erreur de creation de la fenetre: %s\n",
        SDL_GetError());
    } else {

        // tirage aleatoire
        srand(time(NULL));

        // controle du temps pour le score
        double previous = getCurrentTimeMS();
        double lag = 0.0;

        /* BOUCLE DU JEU / GAME LOOP */
        while( !game->quit ){
            
            if(game->etatJeu == MENU)   
                menu(game, joueur, allGraphics);
            else if(game->etatJeu == JEU)
            {             
                // ecran jeu 
                game->sceneFixeTexture=creerTextureSceneFixe(game->ecran);

                gestionEtatJeu(game, joueur, allGraphics);
                scoreAffichage(lag,previous);
                gestionPalmier(game, allGraphics, joueur, &listePalmier);
                invincibleTime(allGraphics, joueur);
                detectionMort(game, joueur);
                for(int i = 0; i < 3; i++) {
                    deplace_elephant(elephant[i]);
                    collisionElephant(allGraphics, joueur, elephant[i]);
                }
                renderAll(game, allGraphics, listePalmier, joueur, elephant);
            }

            
            else if(game->etatJeu == GAMEOVER)
                game_over(game,joueur,allGraphics);   
        }
    }
    destroyAll(game,allGraphics,listePalmier,joueur, elephant);
    
    return 0;
}
