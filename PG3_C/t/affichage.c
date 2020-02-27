#include <iostream>
//#include <windows.h>

#include "enum.h"
#include "constantes.h"
#include "structures.h"


void afficher(Case uneScene[LIGNE_S][COLONNE_S]){
    //ANDLE leHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int laLigne = 0; laLigne < LIGNE_S; laLigne++){
        for(int laColonne = 0; laColonne < COLONNE_S; laColonne++){
            //SetConsoleTextAttribute(leHandle, uneScene[laLigne][laColonne].saCouleur);
            std::cout<<"\033[37;"<<uneScene[laLigne][laColonne].saCouleur<<"m"<<uneScene[laLigne][laColonne].sonChar<<"\033[0m";
        }
        std::cout<<std::endl;
    }
}





