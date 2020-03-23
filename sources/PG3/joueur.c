#include <stdio.h>
#include "string.h"

#include "enum.h"
#include "constantes.h"
#include "structures.h"

#include "scene.h"
#include "piece.h"
#include "joueur.h"


int joueurTour(Joueur desJoueurs[], int unNbrJoueurs, int unTour){
    for(int leJoueur = 0; leJoueur < unNbrJoueurs; leJoueur++){
        if(unTour == desJoueurs[leJoueur].sonTour){
            return leJoueur;
          }
    }
}

void passeLeTour(Joueur desJoueurs[], int unNbrJoueurs, int *uneMain, Case uneScene[LIGNE_S][COLONNE_S], String *unMessage){
    do{
        if(desJoueurs[*uneMain].estFini){
            if(desJoueurs[*uneMain].sonScore>0)
                //unMessage += '[' + desJoueurs[uneMain].sonNom + "] A deja pose toutes ses pieces !\n";
                sprintf(*unMessage, "%s[%s] A deja pose toutes ses pieces !\n", *unMessage, desJoueurs[*uneMain].sonNom );
            else
                //unMessage += '[' + desJoueurs[uneMain].sonNom + "] Passe son tour il est bloque !\n";
                sprintf(*unMessage, "%s[%s] Passe son tour il est bloque !\n", *unMessage, desJoueurs[*uneMain].sonNom );
            changeTour(desJoueurs, unNbrJoueurs);
            *uneMain = joueurTour(desJoueurs, unNbrJoueurs, 0);
            peutJouer(&desJoueurs[*uneMain], uneScene);
        }else
            peutJouer(&desJoueurs[*uneMain], uneScene);
    }while(desJoueurs[*uneMain].estFini); //Vraiment utile ?
}


void changeTour(Joueur desJoueurs[], int unNbrJoueurs){
    int leTour;

    for(int leJoueur = 0; leJoueur < unNbrJoueurs; leJoueur++){
        leTour =  desJoueurs[leJoueur].sonTour;
        leTour--;

        if(leTour < 0){
            leTour = unNbrJoueurs-1;
        }
        desJoueurs[leJoueur].sonTour = leTour;
    }
}



bool peutJouer(Joueur* unJoueur, Case uneScene[LIGNE_S][COLONNE_S]){
    bool peutJouer = false;
    for(int laPieceI = 0; laPieceI < NBR_PIECES && !peutJouer; laPieceI++){
        Piece laPiece = unJoueur->sesPieces[laPieceI];
        peutJouer = false;
        if(laPiece.estDispo){
            for(int laRot = 0; laRot < 2 && !peutJouer; laRot++){
                for(int laRotB = 0; laRotB < 4 && !peutJouer; laRotB++){
                    for(int laLigne = 2; laLigne < DIM+2 && !peutJouer; laLigne++){
                        for(int laColonne = 1; laColonne < DIM+1 && !peutJouer; laColonne++)
                            peutJouer = estPlacable(laPiece, uneScene, laLigne, laColonne);
                    }
                    rotation(&laPiece);
                }
                vertical(&laPiece);
            }
        }
    }
    unJoueur->estFini = !peutJouer;
    return peutJouer;
}



bool jouer(Joueur* unJoueur,String * uneCommande ,Case uneScene[LIGNE_S][COLONNE_S]){
    int lePlacement[3] = {-1};
    bool estCorrect = true;
    String lesRotations = str_new("");

    printf("Veuillez entrer une sequence de la forme 12rrh3vR8 : \n" );
    scanf("%s", *uneCommande);

    if((*uneCommande)[0] == '\0')
        estCorrect = false;
    else{
        analyser(*uneCommande, &lesRotations, lePlacement);
        estCorrect = executer(lesRotations, unJoueur->sesPieces);


        int laPiece = lePlacement[0];
        int laLigne = lePlacement[1]+2;
        int laColonne = lePlacement[2]+1;

        if(estCorrect && laPiece >= 0 && laPiece < NBR_PIECES){
            if(unJoueur->sesPieces[laPiece].estDispo == true)
                estCorrect = estPlacable(unJoueur->sesPieces[laPiece], uneScene, laLigne, laColonne);
            else
                estCorrect = false;
        }else
            estCorrect = false;

        if(estCorrect){
            placer(unJoueur->sesPieces[laPiece], uneScene, laLigne, laColonne);
            unJoueur->sesPieces[laPiece].estDispo = false;
            unJoueur->sesPieces[laPiece].saPosition = (laColonne-1) + (laLigne-2)*DIM;
            ajoutScore(unJoueur, unJoueur->sesPieces[laPiece].sonNbrCases);
        }
    }

    str_delete(lesRotations);
    return estCorrect;
}


void analyser(String uneCommande, String *desRotations, int unPlacement[3]){
    char leChar;
    String leNombreStr = str_new("");
    int leNombre = -1;
    int leIndex = 0;
    bool estFin = false;

    do{
        leChar = uneCommande[leIndex++];

        if(leChar >= '0' && leChar <= '9' ){
            //On récupere le nombre
            sprintf(leNombreStr, "%s%c", leNombreStr, leChar);
            sscanf(leNombreStr, "%d", &leNombre);
            leNombre--;
        }else{
            if (leChar == 'v' || leChar == 'h' || leChar == 'r' && unPlacement[0] == -1 && leNombre >=0){
                sprintf(*desRotations, "%s%d%c", *desRotations, leNombre, leChar);
            }else if(leChar >= 'A' && leChar < 'A' + DIM && unPlacement[0] == -1){
                unPlacement[0] = leNombre;
                unPlacement[1] = leChar - 'A';
                leNombre = -1;

            }else{
                unPlacement[2] = leNombre;
                estFin = true;
            }
            sprintf(leNombreStr, "");
        }

    }while(leChar != '\0' && !estFin);

    str_delete(leNombreStr);

}


void ajoutScore(Joueur *unJoueur, int unNombre){
    if(!aEncorePiece(*unJoueur)){
        if(unNombre == 1)
            unJoueur->sonScore += 20;
        else
            unJoueur->sonScore += 15;
        unJoueur->estFini = true;
    }
}


bool aEncorePiece(Joueur unJoueur){
    bool aUnePiece = false;
    for(int laPiece = 0; laPiece < NBR_PIECES && !aUnePiece; laPiece++)
        aUnePiece = unJoueur.sesPieces[laPiece].estDispo;
    return aUnePiece;
}



bool estFini(Joueur desJoueurs[],int unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S]){
    bool estFini = true;
    for(int leJoueur = 0; leJoueur < unNbrJoueurs && estFini; leJoueur++){
        if(!desJoueurs[leJoueur].estFini){
            peutJouer(&desJoueurs[leJoueur], uneScene);
            estFini = desJoueurs[leJoueur].estFini;

        }
    }
    return estFini;
}


void calculeScore(Joueur desJoueurs[], int unNbrJoueurs){
    for(int leJoueur = 0; leJoueur < unNbrJoueurs; leJoueur++){
        for(int laPiece = 0; laPiece < NBR_PIECES; laPiece++){
            if(desJoueurs[leJoueur].sesPieces[laPiece].estDispo)
                desJoueurs[leJoueur].sonScore -= desJoueurs[leJoueur].sesPieces[laPiece].sonNbrCases;
        }
    }
}


int max(Joueur desJoueurs[], int desJoueursTri[], int *unIndexMax){
    int leJoueur;
    int leJoueurMax;
    int leScoreMax = desJoueurs[desJoueursTri[0]].sonScore;
    int lIndexScoreMax;
    for(int lIndex = 0; lIndex <= *unIndexMax; lIndex++){
        leJoueur = desJoueursTri[lIndex];
        if(desJoueurs[leJoueur].sonScore >= leScoreMax){
            leScoreMax = desJoueurs[leJoueur].sonScore;
            lIndexScoreMax = lIndex;
        }
    }
    leJoueurMax = desJoueursTri[lIndexScoreMax];
    desJoueursTri[lIndexScoreMax] = desJoueursTri[(*unIndexMax)--];
    return leJoueurMax;
}
