#include <stdio.h>
#include "string.h"
#include "enum.h"
#include "constantes.h"
#include "structures.h"

#include "piece.h"


void horizontal(Piece* unePiece){
    bool leTemp;
    for(int laLigne = 0; laLigne < (*unePiece).saHauteur/2; laLigne++){
        for(int laColonne = 0; laColonne < (*unePiece).saLargeur; laColonne++){
            leTemp = (*unePiece).saMatrice[(*unePiece).saHauteur - laLigne-1][laColonne];
            (*unePiece).saMatrice[(*unePiece).saHauteur - laLigne-1][laColonne] = (*unePiece).saMatrice[laLigne][laColonne];
            (*unePiece).saMatrice[laLigne][laColonne] = leTemp;
        }
    }

    switch ((*unePiece).saRotation) {
    case 0: case 2: case 5: case 7:
        (*unePiece).saRotation = ((*unePiece).saRotation +5)%10; break;
        default:
        (*unePiece).saRotation = ((*unePiece).saRotation +3)%6;
    }
}

void vertical(Piece* unePiece){
    bool leTemp;
    for(int laLigne = 0; laLigne < (*unePiece).saHauteur; laLigne++){
        for(int laColonne = 0; laColonne < (*unePiece).saLargeur/2; laColonne++){
            leTemp = (*unePiece).saMatrice[laLigne][(*unePiece).saLargeur - laColonne-1];
            (*unePiece).saMatrice[laLigne][(*unePiece).saLargeur - laColonne-1] = (*unePiece).saMatrice[laLigne][laColonne];
            (*unePiece).saMatrice[laLigne][laColonne] = leTemp;
        }
    }
    (*unePiece).saRotation = 7-(*unePiece).saRotation;
}

void rotation(Piece* unePiece){
    int leTemp;
    for(int laLigne = 0; laLigne < 5; laLigne++){
        for(int laColonne = 0; laColonne < laLigne; laColonne++){
            leTemp = (*unePiece).saMatrice[laLigne][laColonne];
            (*unePiece).saMatrice[laLigne][laColonne] = (*unePiece).saMatrice[laColonne][laLigne];
            (*unePiece).saMatrice[laColonne][laLigne] = leTemp;
        }
    }
    leTemp = (*unePiece).saHauteur;
    (*unePiece).saHauteur = (*unePiece).saLargeur;
    (*unePiece).saLargeur = leTemp;

    leTemp = (*unePiece).saRotation;
    vertical(unePiece);
    (*unePiece).saRotation = (leTemp+1)%4+4*(leTemp>=4); //Formule magique


}


bool executer(String desRotations,Piece* desPieces){
    bool estCorrect=true;
    int lIndex=0;
    int laPiece=0;
    char leChar;
    String strPiece = str_new("");

    do{
        leChar = desRotations[lIndex++];
        if(leChar != '\0'){
            if(leChar >= '0' && leChar <= '9'){
                sprintf(strPiece,"%d%c", laPiece, leChar);
                sscanf(strPiece, "%d",&laPiece);
            }else if(desPieces[laPiece].estDispo == true){
                switch (leChar) {
                case 'r': rotation(&desPieces[laPiece]); break;
                case 'v': vertical(&desPieces[laPiece]); break;
                case 'h': horizontal(&desPieces[laPiece]);
                }


                laPiece = 0;
            }else
                estCorrect = false;
        }
    }while(leChar != '\0' && estCorrect);
    str_delete(strPiece);
    return estCorrect;
}


void setRotation(Piece *unePiece, int uneRotation){
    if(uneRotation > 3 ){
        for(int laRotationA = 0; laRotationA < (7-uneRotation)%4; laRotationA++)
            rotation(unePiece);
        vertical(unePiece);
    }else{
        for(int laRotationA = 0; laRotationA < uneRotation; laRotationA++)
            rotation(unePiece);
    }
}
