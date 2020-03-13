#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "enum.h"
#include "constantes.h"
#include "structures.h"

#include "string.h"
#include "init.h"


void init_Scene(Case uneScene[LIGNE_S][COLONNE_S]){

    for(int laLigne = 0; laLigne < DIM; laLigne++){
        for(int laColonne = 0; laColonne < DIM; laColonne++){
            uneScene[laLigne+2][laColonne+1].sonChar = '.';
            uneScene[laLigne+2][laColonne+1].saCouleur = DEFAULT;
        }
    }

    for(int lIndex = 1; lIndex <= DIM; lIndex++){
        if(lIndex >= 10)
            uneScene[0][lIndex].sonChar = lIndex/10 + '0';
        uneScene[1][lIndex].sonChar = lIndex%10 + '0';
        uneScene[lIndex+1][0].sonChar = lIndex + 'A'-1;
    }

    
    int lIndexMax = 3;
    Couleur laListeCouleur[] = {ROUGE,VERT,BLEU,JAUNE};

    for(int laLigne = 1; laLigne <= DIM+2; laLigne += DIM+1){
        for(int laColonne = 0; laColonne <= DIM+1; laColonne += DIM+1)
            uneScene[laLigne][laColonne].saCouleur = randomColor(laListeCouleur, &lIndexMax);
    }
    

}

Couleur randomColor(Couleur uneListeCouleur[], int * unIndexMax){
    int lAlea;

    Couleur laCouleur;
    int lindex = *unIndexMax;
    lAlea = rand()%(lindex+1);
    laCouleur = uneListeCouleur[lAlea];

    //On retire la couleur tirée puis réduction de l'index maximum du tableau.
    uneListeCouleur[lAlea] = uneListeCouleur[lindex--];
    *unIndexMax = lindex;


    return laCouleur;
}


void init_Piece(Piece desPieces[NBR_PIECES], Couleur uneCouleur, String* unNomFichier){
    /*
    std::ifstream leFlux(unNomFichier.c_str());
    std::string laLigneStr;

    bool ilExiste(!leFlux.fail());
    //SI le fichier existe:
    if(ilExiste){
        int laLigne(0), laColonne(0), leIndex(0), laLargeurMax(0);

        do{
            std::getline(leFlux, laLigneStr);

            if(laLigneStr.length()>0){
                for(laColonne = 0; laColonne < laLigneStr.length(); laColonne++){
                    if(laLigneStr[laColonne] == 'x'){
                        desPieces[leIndex].saMatrice[laLigne][laColonne] = true;
                        desPieces[leIndex].sonNbrCases++;
                    }
                }
                if(laColonne > laLargeurMax)
                    laLargeurMax = laColonne;
                laLigne++;
            }
            if(laLigneStr.length()==0 || leFlux.eof()){
                desPieces[leIndex].saHauteur = laLigne;
                desPieces[leIndex].saLargeur = laLargeurMax;
                desPieces[leIndex].sonNumero = leIndex+1;
                desPieces[leIndex].saCouleur = uneCouleur;
                leIndex++;
                laLigne = 0;
                laLargeurMax = 0;
            }

        }while(!leFlux.eof());
    }else
        std::cout<<"[Erreur]  Impossible d'ouvrir le fichier "<<unNomFichier<<" !\n";
    leFlux.close();
    */
}


bool nbrJoueurs(int *unNbrJoueurs, int *unNbrBots){
    int unNbrJoueursVal = *unNbrJoueurs;
    int unNbrBotsVal = *unNbrBots;

    //String pour eviter de boucler à l'infini si entree != un nombre
    bool estUneSauvegarde = false;
    int uneEntree;
    do{
        printf("Combien de joueurs ? (Ou tapez '0' pour charger une partie depuis le fichier de sauvegarde) : \n");
        scanf("%d",&uneEntree);
        if(uneEntree == 0)
            return true;
        
        if(!((uneEntree > 1 && uneEntree < 5) || uneEntree == 60))
            printf("Oops ! Saisir un nombre de joueurs entre 2 et 4 !\n");

    }while(!((uneEntree > 1 && uneEntree < 5) || uneEntree == 60));

    if(uneEntree != 0)
        unNbrBotsVal = demandeNbrBots(uneEntree);
        
        
    *unNbrJoueurs = unNbrJoueursVal;
    *unNbrBots = unNbrBotsVal; 
    return estUneSauvegarde;
}

int demandeNbrBots(int unNbrJoueurs){
    int leNbrBots = 0;
    do{
        printf("Combien de bots ? (entre 0 et %d ) : \n", unNbrJoueurs);
        scanf("%d", &leNbrBots);
        if(!(leNbrBots >= 0 && leNbrBots <= unNbrJoueurs))
            printf("Oops ! Saisir un nombre de bots entre 0 et %d !\n", unNbrJoueurs);

    }while(!(leNbrBots >= 0 && leNbrBots <= unNbrJoueurs));
    return leNbrBots;
    
}


void init_Joueur(Joueur desJoueurs[], int unNbrJoueurs, int unNbrBots, bool estUneSauvegarde, String * unFichierP){
    
    int lIndexMax = unNbrJoueurs-1;
    Couleur laListeCouleur[] = {BLEU, JAUNE, ROUGE, VERT};
    Couleur laCouleur;
    int lOrdre;
    bool estCorrect;
    String leNom = str_new("");

    desJoueurs[0].sonNom = str_new("BOT- GLaDOS");
    desJoueurs[1].sonNom = str_new("BOT- HAL 9000");
    desJoueurs[2].sonNom = str_new("BOT- R2D2");
    desJoueurs[3].sonNom = str_new("BOT- Skynet");

    for(int leBot = 0; leBot < unNbrBots; leBot++)
        desJoueurs[leBot].estBot = true;

    for(int leJoueur = 0; leJoueur < unNbrJoueurs && unNbrJoueurs < 5; leJoueur++){
        if(!estUneSauvegarde){
            laCouleur = randomColor(laListeCouleur, &lIndexMax);

            switch (laCouleur) {
            case BLEU: lOrdre = 0; break;
            case JAUNE: lOrdre = 1; break;
            case ROUGE: lOrdre = 2; break;
            case VERT: lOrdre = 3;
            }

            desJoueurs[leJoueur].sonTour = lOrdre;
            init_Piece(desJoueurs[leJoueur].sesPieces, laCouleur, unFichierP);
            /*
            if(!desJoueurs[leJoueur].estBot){
                do{
                    estCorrect = true;
                    std::cout<<"Entrez le nom du joueur numero "<<leJoueur+1<<" : ";
                    std::getline(std::cin, leNom);

                        for(int lIndex = 0; lIndex < leNom.length() && estCorrect; lIndex++){
                            if(!((leNom[lIndex] >= 'A' && leNom[lIndex] <= 'Z')
                                 || (leNom[lIndex] >= 'a' && leNom[lIndex] <= 'z')
                                 || leNom[lIndex] == ' ' || leNom[lIndex] == '-' || leNom[lIndex] == '\'')){
                                std::cout<<"Oups ! Votre pseudo ne doit comporter que des lettres (majuscules ou minuscules), espaces, tirets et apostrophes !"<<std::endl;
                                estCorrect = false;
                            }
                        }

                }while(!estCorrect);
                desJoueurs[leJoueur].sonNom = leNom;
            }
        }else
            desJoueurs[leJoueur].sonNom = "";
    */
    }
}
}
