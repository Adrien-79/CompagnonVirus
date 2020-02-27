#include <iostream>
#include <windows.h>

#include "enum.h"
#include "constantes.h"
#include "structures.h"


void afficher(Case uneScene[LIGNE_S][COLONNE_S]){
    HANDLE leHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int laLigne = 0; laLigne < LIGNE_S; laLigne++){
        for(int laColonne = 0; laColonne < COLONNE_S; laColonne++){
            SetConsoleTextAttribute(leHandle, uneScene[laLigne][laColonne].saCouleur);
            std::cout<<uneScene[laLigne][laColonne].sonChar;
        }
        std::cout<<'\n';
    }
}





