#include <stdio.h>
#include <math.h>
#include "string.h"
#include "enum.h"
#include "constantes.h"
#include "structures.h"

#include "scene.h"
#include "piece.h"
#include "joueur.h"
#include "bot.h"


void jouerBot(Joueur *unJoueur, Case uneScene[LIGNE_S][COLONNE_S], Joueur desJoueurs[], int unNbrJoueurs){
    int laPiece;
    bool peutJouer = false;

    long laValeur;

    long laValeurMax = -9999;
    int laPieceMax;
    int laLigneMax;
    int laColonneMax;
    int laRotationMax;

    for(laPiece = 0; laPiece < NBR_PIECES; laPiece++){
        if(unJoueur->sesPieces[laPiece].estDispo){
            for(int laRot = 0; laRot < 2; laRot++){
                for(int laRotB = 0; laRotB < 4; laRotB++){
                    for(int laLigne = 2; laLigne < DIM+2; laLigne++){
                        for(int laColonne = 1; laColonne < DIM+1; laColonne++){
                            peutJouer = estPlacable(unJoueur->sesPieces[laPiece], uneScene, laLigne, laColonne);
                            if(peutJouer){
                                laValeur = evaluerCoup(unJoueur->sesPieces[laPiece], uneScene, laLigne, laColonne, desJoueurs, unNbrJoueurs);
                                if(laValeur > laValeurMax){
                                    laValeurMax = laValeur;
                                    laPieceMax = laPiece;
                                    laLigneMax = laLigne;
                                    laColonneMax = laColonne;
                                    laRotationMax = unJoueur->sesPieces[laPiece].saRotation;
                                }
                            }
                        }
                    }
                    rotation(&unJoueur->sesPieces[laPiece]);
                }
                vertical(&unJoueur->sesPieces[laPiece]);
            }
        }
    }


    setRotation(&unJoueur->sesPieces[laPieceMax], laRotationMax);
    placer(unJoueur->sesPieces[laPieceMax], uneScene, laLigneMax, laColonneMax);
    unJoueur->sesPieces[laPieceMax].saPosition = (laColonneMax) + (laLigneMax-2)*DIM;
    unJoueur->sesPieces[laPieceMax].estDispo = false;
    ajoutScore(unJoueur, unJoueur->sesPieces[laPieceMax].sonNbrCases);

}


long evaluerCoup(Piece unePiece, Case uneScene[LIGNE_S][COLONNE_S], int uneLigne, int uneColonne, Joueur desJoueurs[], int unNbrJoueurs){
    long laSomme = 0;
    int laDistanceP = 100/distancePiecesMin(unePiece, uneScene, uneLigne, uneColonne);
    int laDistanceC = 200/distanceCentreMin(unePiece, uneLigne, uneColonne);
    int lesCoins = 1000*piecesBloquees(unePiece, uneLigne, uneColonne, desJoueurs, unNbrJoueurs, uneScene);
    laSomme += unePiece.sonNbrCases + lesCoins+laDistanceP+laDistanceC;
    if(unePiece.sonNbrCases == 1)
        laSomme -= 900;

    return laSomme;
}


int distanceCentreMin(Piece unePiece, int uneLigne, int uneColonne){
    int laDistanceMin = 400;
    int laDistance;
    int leCentre = DIM/2;

    for(int laLigneP = 0 ; laLigneP < unePiece.saHauteur; laLigneP++ ){
        for(int laColonneP = 0; laColonneP < unePiece.saLargeur; laColonneP++){
            if(unePiece.saMatrice[laLigneP][laColonneP]){
                laDistance = sqrt(pow(laLigneP + uneLigne - leCentre,2) + pow(laColonneP + uneColonne - leCentre,2))+1;
                if (laDistance < laDistanceMin)
                    laDistanceMin = laDistance;
            }
        }
    }
    return laDistanceMin;
}


int distancePiecesMin(Piece unePiece, Case uneScene[LIGNE_S][COLONNE_S], int uneLigne, int uneColonne){
    int laDistanceMin = pow(DIM,2)*2;
    int laDistance;
    for(int laLigne = 2; laLigne < DIM+2; laLigne++){
        for(int laColonne = 1; laColonne < DIM +2; laColonne++){
            if(uneScene[laLigne][laColonne].saCouleur != unePiece.saCouleur && uneScene[laLigne][laColonne].saCouleur != DEFAULT){
                for(int laLigneP = 0 ; laLigneP < unePiece.saHauteur; laLigneP++ ){
                    for(int laColonneP = 0; laColonneP < unePiece.saLargeur; laColonneP++){
                        if(unePiece.saMatrice[laLigneP][laColonneP]){
                            laDistance = sqrt(pow(laLigneP + uneLigne - laLigne,2) + pow(laColonneP + uneColonne - laColonne,2))+1;
                            if (laDistance < laDistanceMin)
                                laDistanceMin = laDistance;
                        }
                    }
                }
            }
        }
    }
    return laDistanceMin;
}


int piecesBloquees(Piece unePiece, int uneLigne, int uneColonne, Joueur desJoueurs[], int unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S]){
    int laLigne;
    int laColonne;
    int leNbrCoins = 0;
    for(int laLigneP = 0 ; laLigneP < unePiece.saHauteur; laLigneP++ ){
        for(int laColonneP = 0; laColonneP < unePiece.saLargeur; laColonneP++){
            laLigne = uneLigne + laLigneP;
            laColonne = uneColonne + laColonneP;
            if(unePiece.saMatrice[laLigneP][laColonneP]){

                for(int leJoueur = 0; leJoueur < unNbrJoueurs; leJoueur++){
                    if(desJoueurs[leJoueur].sesPieces[0].saCouleur != unePiece.saCouleur){
                        for(int laPiece = 0; laPiece < NBR_PIECES; laPiece++){
                            for(int laLignePJ = 0; laLignePJ < desJoueurs[leJoueur].sesPieces[laPiece].saHauteur; laLignePJ++){
                                for(int laColonnePJ = 0; laColonnePJ < desJoueurs[leJoueur].sesPieces[laPiece].saLargeur; laColonnePJ++){
                                    for(int laRot = 0; laRot < 2; laRot++){
                                        for(int laRotB = 0; laRotB < 4; laRotB++){
                                            if(desJoueurs[leJoueur].sesPieces[laPiece].saMatrice[laLignePJ][laColonnePJ]){
                                                if(estPlacable(desJoueurs[leJoueur].sesPieces[laPiece], uneScene, laLigne - laLignePJ, laColonne - laColonnePJ))
                                                    leNbrCoins++;
                                            }
                                            rotation(&desJoueurs[leJoueur].sesPieces[laPiece]);
                                        }
                                        vertical(&desJoueurs[leJoueur].sesPieces[laPiece]);
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    return leNbrCoins;
}
