#include <fstream>
#include <iostream>

#include "enum.h"
#include "constantes.h"
#include "structures.h"

#include "sauvegarde.h"
#include "joueur.h"
#include "piece.h"
#include "scene.h"
#include "init.h"


void putNom(std::string &unNom, unsigned char &unOctet, int &unDecalage, std::ofstream &unFichier){
    int leNbr;
    for(int lIndex = 0; lIndex < unNom.length(); lIndex++){
        char leChar = unNom[lIndex];
        if (leChar >= 'A' && leChar <= 'Z')
            leNbr = leChar - 'A';
        else if (leChar >= 'a' && leChar <= 'z')
            leNbr = leChar - 'a' +26;

        else {
            switch(leChar){
            case '-': leNbr = 52; break;
            case '\'' : leNbr = 53; break;
            default : leNbr = 54;
            }
        }
        putFichier(leNbr, 6, unDecalage, unOctet, unFichier);
    }
}

void putCoin(Case uneScene[LIGNE_S][COLONNE_S], int &unDecalage, unsigned char &unOctet , std::ofstream &unFichier){
    int laValeur;
    for(int laLigne = 1; laLigne <= DIM+2; laLigne += DIM+1){
        for(int laColonne = 0; laColonne <= DIM+1; laColonne += DIM+1){
            laValeur = couleurToInt(uneScene[laLigne][laColonne].saCouleur);
            putFichier(laValeur, 2, unDecalage, unOctet, unFichier);
        }
    }
}

int couleurToInt(Couleur uneCouleur){
    int lEntier;
    switch (uneCouleur) {
    case BLEU : lEntier = 0; break;
    case JAUNE :lEntier = 1; break;
    case ROUGE : lEntier = 2; break;
    case VERT : lEntier = 3;
    }
    return lEntier;
}

Couleur intToCouleur(int unEntier){
    Couleur laCouleur;
    switch (unEntier) {
    case 0 : laCouleur = BLEU; break;
    case 1 :laCouleur = JAUNE; break;
    case 2 : laCouleur = ROUGE; break;
    case 3 : laCouleur = VERT;
    }
    return laCouleur;
}

void sauvegarder(Joueur desJoueurs[], int unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S], std::string &unNomFichierS){
    std::ofstream leFichier(unNomFichierS.c_str());
    unsigned char lOctet = 0;
    int leDecalage = 0;
    int leJoueur;
    int laCouleur;

    putCoin(uneScene, leDecalage, lOctet, leFichier);

    for(int lIndex = 0; lIndex < unNbrJoueurs; lIndex++){
        leJoueur = joueurTour(desJoueurs, unNbrJoueurs, lIndex);
        putNom(desJoueurs[leJoueur].sonNom, lOctet, leDecalage, leFichier);
        laCouleur = couleurToInt(desJoueurs[leJoueur].sesPieces[0].saCouleur)+55;
        putFichier(laCouleur, 6, leDecalage, lOctet, leFichier);
        putFichier((desJoueurs[leJoueur].sonScore >= 20 ), 1, leDecalage, lOctet, leFichier);
        for(int laPiece = 0; laPiece < NBR_PIECES; laPiece++){
            putFichier(desJoueurs[leJoueur].sesPieces[laPiece].saRotation, 3, leDecalage, lOctet, leFichier);
            if(desJoueurs[leJoueur].sesPieces[laPiece].estDispo)
                putFichier(1, 1, leDecalage, lOctet, leFichier);
            else{
                putFichier(0, 1, leDecalage, lOctet, leFichier);
                putFichier(desJoueurs[leJoueur].sesPieces[laPiece].saPosition, 9, leDecalage, lOctet, leFichier);
            }

        }
    }
    if(leDecalage>0)
        leFichier<<lOctet;

    leFichier.close();
}

void putFichier(int unNombre, int uneTaille, int &unDecalage, unsigned char &unOctet, std::ofstream &unFichier){

    int leNbrBit;
    do{
        leNbrBit = (uneTaille-8)+unDecalage;
        unOctet = unOctet | (unNombre << unDecalage);
        if(leNbrBit < 0){
            unDecalage += uneTaille;
        }else{
            unFichier<<unOctet;
            unOctet = 0;
            unDecalage = 0;
            unNombre = unNombre >> (uneTaille - leNbrBit);
            uneTaille = leNbrBit;
        }
    }while(leNbrBit > 0);
}


int getFichier(int uneTaille, int &unDecalage, unsigned char &unOctet, std::ifstream &unFichier){
    int leNombre = 0;
    int leNbrBit;
    int lEmplacement = 0;
    unsigned char leTemp;
    do{
        leNbrBit = (uneTaille-8)+unDecalage;
        if(leNbrBit < 0){
            leTemp = unOctet <<(-leNbrBit);
            leTemp = leTemp >>(-leNbrBit);
            leNombre = leNombre | ((leTemp>>unDecalage) << (lEmplacement));
            unDecalage += uneTaille;
        }else{
            leNombre = leNombre | ((unOctet>>unDecalage)<<lEmplacement);
            lEmplacement = 8 - unDecalage;
            unOctet = unFichier.get();
            unDecalage = 0;
            uneTaille = leNbrBit;
        }
    }while(leNbrBit > 0);
    return leNombre;
}

void charger(Joueur desJoueurs[], int& unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S],std::string &unNomFichierP, std::string &unNomFichierS){

    std::ifstream leFichier(unNomFichierS.c_str());
    unsigned char lOctet = leFichier.get();
    int leDecalage = 0;
    int uneCouleur;
    int leJoueur;
    setCoin(uneScene, leDecalage, lOctet, leFichier);

    for(leJoueur = 0; leJoueur <= 4 && !leFichier.eof(); leJoueur++){
        if(leJoueur < 4){
            setNom(desJoueurs[leJoueur], lOctet, leDecalage, uneCouleur, leFichier);

            desJoueurs[leJoueur].sonScore = getFichier(1, leDecalage, lOctet, leFichier)*5;
            setPieces(desJoueurs[leJoueur].sesPieces, lOctet, leDecalage, uneCouleur, leFichier, unNomFichierP, uneScene);
            desJoueurs[leJoueur].sonTour = leJoueur;
        }
    }

    unNbrJoueurs = leJoueur-1;
    for(leJoueur = 0; leJoueur < unNbrJoueurs; leJoueur++)
        ajoutScore(desJoueurs[leJoueur], -1);
    leFichier.close();
}


void setNom(Joueur &unJoueur, unsigned char &unOctet, int &unDecalage,int &uneValeur, std::ifstream &unFichier){
    std::string leNom("");
    do{
        uneValeur = getFichier(6, unDecalage, unOctet, unFichier);
        char leChar = uneValeur;

        if(uneValeur <= 54){
            if(uneValeur <= 25)
                leChar += 'A';
            else if(uneValeur <= 51)
                leChar = 'a' + uneValeur-26;
            else switch (uneValeur) {
            case 52 : leChar = '-'; break;
            case 53 : leChar = '\''; break;
            default : leChar = ' ';
            }
            leNom = leNom + leChar;
        }
    }while (uneValeur < 55);
    unJoueur.sonNom = leNom;
}

void setPieces(Piece desPieces[], unsigned char &unOctet, int &unDecalage, int uneCouleur, std::ifstream &unFichier, std::string &unNomFichierP, Case uneScene[LIGNE_S][COLONNE_S]){

    int laRotation;
    int laPosition;
    Couleur laCouleur;
    bool estDispo;

    laCouleur = intToCouleur(uneCouleur-55);
    resetPieces(desPieces);
    init(desPieces, laCouleur, unNomFichierP);

    for(int laPiece = 0; laPiece < NBR_PIECES; laPiece++){
        laRotation = getFichier(3, unDecalage, unOctet, unFichier);
        setRotation(desPieces[laPiece], laRotation);
        estDispo = getFichier(1,unDecalage, unOctet, unFichier)+0;
        if(!estDispo){
            laPosition = getFichier(9, unDecalage, unOctet, unFichier);
            setPosition(desPieces[laPiece], laPosition, uneScene);
        }
        desPieces[laPiece].estDispo = estDispo;
    }
}

void setPosition(Piece &unePiece, int unePosition, Case uneScene[LIGNE_S][COLONNE_S]){
        unePiece.saPosition = unePosition;
        placer(unePiece, uneScene, (unePosition/DIM) +2, (unePosition%DIM) + 1);
}

void resetPieces(Piece desPieces[]){
    for(int laPiece = 0; laPiece < NBR_PIECES; laPiece++){
        //On reset les informations de la piece (sinon y a des bugs)
        desPieces[laPiece].saRotation = 0;
        desPieces[laPiece].estDispo = true;
        desPieces[laPiece].saHauteur = 0;
        desPieces[laPiece].saLargeur = 0;
        desPieces[laPiece].saPosition = 400;
        desPieces[laPiece].sonNbrCases = 0;
        desPieces[laPiece].sonNumero = 0;

        for(int laLigne = 0; laLigne < 5; laLigne++){
            for(int laColonne = 0; laColonne < 5; laColonne++){
                desPieces[laPiece].saMatrice[laLigne][laColonne] = false;
            }
        }
    }
}

void setCoin(Case uneScene[LIGNE_S][COLONNE_S], int &unDecalage, unsigned char &unOctet , std::ifstream &unFichier){
    Couleur laCouleur;
    for(int laLigne = 1; laLigne <= DIM+2; laLigne += DIM+1){
        for(int laColonne = 0; laColonne <= DIM+1; laColonne += DIM+1){
            laCouleur = intToCouleur(getFichier(2, unDecalage, unOctet, unFichier));
            uneScene[laLigne][laColonne].saCouleur = laCouleur;
        }
    }
}


void demandeSauvegarde(Joueur desJoueurs[], int unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S], std::string &unNomFichierS, std::string &unMessage){
    std::string laReponse;
    std::cout<<"Voulez vous sauvegarder la partie et ecraser la precedente sauvegarde ? (O / N)"<<std::endl;
    std::getline(std::cin, laReponse);

    if(laReponse == "O" || laReponse == "o"){
        sauvegarder(desJoueurs, unNbrJoueurs, uneScene, unNomFichierS);
        unMessage = "[INFO] Partie sauvegarde !\n";
    }else if(laReponse == "N" || laReponse == "n")
        unMessage = "[INFO] La partie n'est pas sauvergarde.\n";
    else
        unMessage = "[INFO] Saisie inccorecte, la partie n'est pas sauvegarde.\n";
}


void demandeCharger(Joueur desJoueurs[], int& unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S],std::string &unNomFichierP, std::string &unNomFichierS, std::string &unMessage, int &uneMain){
    std::string laReponse;
    std::cout<<"Voulez vous charger une partie et quitter celle en cours ? (O / N)"<<std::endl;
    std::getline(std::cin, laReponse);

    if(laReponse == "O" || laReponse == "o"){
        init(uneScene);
        charger(desJoueurs, unNbrJoueurs, uneScene, unNomFichierP, unNomFichierS);
        uneMain = 0;
        unMessage = "[INFO] La partie est chargee !\n";
    }else if(laReponse == "N" || laReponse == "n")
        unMessage = "[INFO] Annulation du chargement de la partie.\n";
    else
        unMessage = "[INFO] Saisie inccorecte, annulation du chargement.\n";
}
