#include <iostream>

#include "enum.h"
#include "constantes.h"
#include "structures.h"

#include "init.h"
#include "affichage.h"
#include "scene.h"
#include "piece.h"
#include "joueur.h"

#include "sauvegarde.h"
#include "bot.h"


int main(){

    std::string leFichierP("../Blokus/pieces.txt");
    std::string leFichierS("../Blokus/sauvegarde/blokus.data");

    std::string leMessage;
    std::string leMessageInfo;

    std::string laCommande;
    Case laScene[LIGNE_S][COLONNE_S];
    bool laFin = false;
    bool estUneSauvegarde;
    int leNbrJoueurs;
    int leNbrBots;
    int laMain;
    bool aJouer;

     estUneSauvegarde = nbrJoueurs(leNbrJoueurs, leNbrBots);
    Joueur lesJoueurs[4];

    init(laScene);
    init(lesJoueurs, leNbrJoueurs, leNbrBots,estUneSauvegarde ,leFichierP);

    if(estUneSauvegarde)
        charger(lesJoueurs, leNbrJoueurs, laScene, leFichierP, leFichierS);


    do{
        leMessage = '\n';
        laMain = joueurTour(lesJoueurs, leNbrJoueurs, 0);
        passeLeTour(lesJoueurs, leNbrJoueurs, laMain, laScene, leMessage);

        do{
            leMessageInfo = "";
            if(laCommande == "s")
                demandeSauvegarde(lesJoueurs, leNbrJoueurs, laScene, leFichierS, leMessageInfo);
            else if(laCommande == "l")
                demandeCharger(lesJoueurs, leNbrJoueurs, laScene, leFichierP, leFichierS, leMessageInfo, laMain);
            else if(laCommande == "/auto")
                for(int i = 0; i<leNbrJoueurs; i++)
                    lesJoueurs[i].estBot = true;

            clearPieces(laScene);
            piecesDansScene(laScene, lesJoueurs, leNbrJoueurs);
            afficher(laScene);

            std::cout<<leMessageInfo;
            std::cout<<leMessage;
            std::cout<<'['<<lesJoueurs[laMain].sonNom<<"] ";

            if(lesJoueurs[laMain].estBot){
                jouerBot(lesJoueurs[laMain], laScene, lesJoueurs, leNbrJoueurs);
                aJouer = true;
                std::cout<<std::endl;
            }else
                aJouer = jouer(lesJoueurs[laMain], laCommande,laScene);;
        }while(!aJouer);

        changeTour(lesJoueurs, leNbrJoueurs);
        laFin = estFini(lesJoueurs, leNbrJoueurs, laScene);

    }while(!laFin);


    sauvegarder(lesJoueurs, leNbrJoueurs, laScene, leFichierS);


    calculeScore(lesJoueurs, leNbrJoueurs);
    clearPieces(laScene);
    putScore(lesJoueurs, leNbrJoueurs, laScene);
    afficher(laScene);

    return 0;
}
