#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

#include "enum.h"
#include "constantes.h"
#include "structures.h"

#include "string.h"
#include "init.h"
/**

#include "affichage.h"
#include "scene.h"
#include "piece.h"
#include "joueur.h"

#include "sauvegarde.h"
#include "bot.h"
**/

int main(){

    srand(time(NULL));
    String leFichierP = str_new("../Blokus/pieces.txt");
    String leFichierS = str_new("../Blokus/sauvegarde/blokus.data");

    String leMessage = str_new("");
    String leMessageInfo = str_new("");

    String laCommande = str_new("");
    Case laScene[LIGNE_S][COLONNE_S];
    bool laFin = false;
    bool estUneSauvegarde;
    int leNbrJoueurs;
    int leNbrBots;
    int laMain;
    bool aJouer;

    
    estUneSauvegarde = nbrJoueurs(&leNbrJoueurs, &leNbrBots);
    Joueur lesJoueurs[4];

    init_Scene(laScene);
    init_Joueur(lesJoueurs, leNbrJoueurs, leNbrBots,estUneSauvegarde , &leFichierP);

    //if(estUneSauvegarde)
        //charger(lesJoueurs, leNbrJoueurs, laScene, leFichierP, leFichierS);


    do{
        //str_set(&leMessage, "\n");
        //laMain = joueurTour(lesJoueurs, leNbrJoueurs, 0);
        //passeLeTour(lesJoueurs, leNbrJoueurs, laMain, laScene, leMessage);

        do{
            //leMessageInfo = "";

            if(strcmp(laCommande, "s") == 0){
                printf("DEMANDE_SAVE\n");
                //demandeSauvegarde(lesJoueurs, leNbrJoueurs, laScene, leFichierS, leMessageInfo);
            }else if(strcmp(laCommande, "l") == 0){
                //demandeCharger(lesJoueurs, leNbrJoueurs, laScene, leFichierP, leFichierS, leMessageInfo, laMain);
                printf("Demande Charger\n");
            }else if(strcmp(laCommande,"/auto") == 0){
                for(int i = 0; i<leNbrJoueurs; i++){}
                    //lesJoueurs[i].estBot = true;
            }

            printf("aaa\n");
            //clearPieces(laScene);
            //piecesDansScene(laScene, lesJoueurs, leNbrJoueurs);
            //afficher(laScene);


            //printf("%s%s[%s]\n", leMessageInfo, leMessage, "a");
            printf("PASSE\n");
            return 0;

            //std::cout<<leMessageInfo;
            //std::cout<<leMessage;
            //std::cout<<'['<<lesJoueurs[laMain].sonNom<<"] ";

            /*
            if(lesJoueurs[laMain].estBot){
                //jouerBot(lesJoueurs[laMain], laScene, lesJoueurs, leNbrJoueurs);
                //aJouer = true;
                //std::cout<<std::endl;
            }else
                printf("bbbb\n");
                //aJouer = jouer(lesJoueurs[laMain], laCommande,laScene);;
                */
            
        }while(!aJouer);

        //changeTour(lesJoueurs, leNbrJoueurs);
        //laFin = estFini(lesJoueurs, leNbrJoueurs, laScene);

    }while(!laFin);


    //sauvegarder(lesJoueurs, leNbrJoueurs, laScene, leFichierS);


    //calculeScore(lesJoueurs, leNbrJoueurs);
    //clearPieces(laScene);
    //putScore(lesJoueurs, leNbrJoueurs, laScene);
    //afficher(laScene);

    return 0;
}
