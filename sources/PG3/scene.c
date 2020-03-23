#include <stdio.h>
#include "string.h"

#include "enum.h"
#include "constantes.h"
#include "structures.h"

#include "scene.h"
#include "joueur.h"


void piecesDansScene(Case uneScene[LIGNE_S][COLONNE_S], Joueur desJoueurs[], int unNbrJoueurs){
    int laLigneTableau = 2;
    int laColonneTableau = DIM+3;
    int leJoueur;
    String laPieceSTR = str_new("xx");
    int laHauteurMax;


    for(int leTour = 0; leTour < unNbrJoueurs; leTour++){
        leJoueur = joueurTour(desJoueurs, unNbrJoueurs, leTour);
        laHauteurMax = 0;
        ecrireMot(desJoueurs[leJoueur].sonNom, uneScene, laLigneTableau-2, laColonneTableau);
        Piece* lesPieces = desJoueurs[leJoueur].sesPieces;

        for(int lIndex = 0; lIndex < NBR_PIECES; lIndex++){
            if(lesPieces[lIndex].estDispo){
              sprintf(laPieceSTR, "%d", lesPieces[lIndex].sonNumero);
              //TO DO  laPieceSTR = std::to_string(lesPieces[lIndex].sonNumero);
                ecrireMot(laPieceSTR,uneScene,laLigneTableau-1,laColonneTableau);
                //On récupere la hauteur de la piece avec la hauteur la plus haute (pour le décalage de la ligne suivante)
                if(lesPieces[lIndex].saHauteur > laHauteurMax)
                    laHauteurMax = lesPieces[lIndex].saHauteur;


                placer(lesPieces[lIndex], uneScene, laLigneTableau, laColonneTableau);
                laColonneTableau += lesPieces[lIndex].saLargeur +1;
            }
        }
        laLigneTableau += laHauteurMax+3;
        laColonneTableau = DIM+3;
    }

    str_delete(laPieceSTR);
}


void clearPieces(Case uneScene[LIGNE_S][COLONNE_S]){
    for(int laLigne = 0; laLigne < LIGNE_S; laLigne++){
        for(int laColonne = DIM+3; laColonne < COLONNE_S; laColonne++){
            uneScene[laLigne][laColonne].saCouleur = DEFAULT;
            uneScene[laLigne][laColonne].sonChar = ' ';
        }
    }
}


void ecrireMot(String unMot,Case uneScene[LIGNE_S][COLONNE_S] ,int uneLigne, int uneColonne){
    char leChar = unMot[0];
    int leIndex = 0;
    while(leChar != '\0'){
        uneScene[uneLigne][uneColonne+leIndex].sonChar = leChar;
        leChar = unMot[++leIndex];
    }

}


void placer(Piece unePiece, Case uneScene[LIGNE_S][COLONNE_S], int uneLigne, int uneColonne){
    for(int laLigne = 0; laLigne < unePiece.saHauteur; laLigne++){
        for(int laColonne = 0; laColonne < unePiece.saLargeur; laColonne++){
            if(unePiece.saMatrice[laLigne][laColonne] == true){
                uneScene[uneLigne+laLigne][uneColonne+laColonne].sonChar = ' ';
                uneScene[uneLigne+laLigne][uneColonne+laColonne].saCouleur = unePiece.saCouleur;
            }
        }
    }
}


bool estPlacable(Piece unePiece, Case uneScene[LIGNE_S][COLONNE_S], int uneLigne, int uneColonne){
    bool aUnCoin = false;
    bool estPlacable = true;
    char leChar;


    for(int laLigne = 0; laLigne < unePiece.saHauteur && estPlacable; laLigne++){
        for(int laColonne = 0; laColonne < unePiece.saLargeur && estPlacable; laColonne++){
            int laLigneScene = uneLigne+laLigne;
            int laColonneScene = uneColonne+laColonne;
            leChar = uneScene[laLigneScene][laColonneScene].sonChar;

            if(uneLigne > 1 && uneLigne+unePiece.saHauteur < DIM+3 && uneColonne > 0 && uneColonne+unePiece.saLargeur < DIM+2){
                if(unePiece.saMatrice[laLigne][laColonne] == true){
                    if(leChar == '.'
                            && uneScene[laLigneScene+1][laColonneScene].saCouleur != unePiece.saCouleur
                            && uneScene[laLigneScene-1][laColonneScene].saCouleur != unePiece.saCouleur
                            && uneScene[laLigneScene][laColonneScene+1].saCouleur != unePiece.saCouleur
                            && uneScene[laLigneScene][laColonneScene-1].saCouleur != unePiece.saCouleur){
                        //On test si la piece possede un coin voisin de même couleur
                        if(uneScene[laLigneScene+1][laColonneScene+1].saCouleur == unePiece.saCouleur
                                ||uneScene[laLigneScene-1][laColonneScene+1].saCouleur == unePiece.saCouleur
                                ||uneScene[laLigneScene-1][laColonneScene-1].saCouleur == unePiece.saCouleur
                                ||uneScene[laLigneScene+1][laColonneScene-1].saCouleur == unePiece.saCouleur){

                            aUnCoin = true;
                        }
                    }else{
                        estPlacable = false;
                    }
                }
            }
        }
    }
    //Si la piece est placable et qu'elle possede un coin de meme couleur -> return true
    return estPlacable && aUnCoin;
}


void putScore(Joueur desJoueurs[], int unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S]){
    int laLigne, laColonne;
    int leJoueur;

    int lesJoueursTri[] = {0,1,2,3};
    int lIndexMax = unNbrJoueurs-1;


    String laString = str_new("-============- SCORE -============-");

    ecrireMot(laString, uneScene, 6, DIM+10);
    sprintf(laString, "-=================================-");
    ecrireMot(laString, uneScene, unNbrJoueurs*2+8, DIM+10);

    for(int lIndex = 0; lIndex < unNbrJoueurs; lIndex++){
        leJoueur = max(desJoueurs, lesJoueursTri, &lIndexMax);

        laLigne = 8+(lIndex*2);
        laColonne = DIM+15;

        uneScene[laLigne][laColonne].saCouleur = desJoueurs[leJoueur].sesPieces[0].saCouleur;
        ecrireMot(desJoueurs[leJoueur].sonNom, uneScene, laLigne, laColonne+2);
        sprintf(laString, ": %d", desJoueurs[leJoueur].sonScore);
        ecrireMot(laString, uneScene, laLigne, laColonne+15);
    }

    str_delete(laString);

}
