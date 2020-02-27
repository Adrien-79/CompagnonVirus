/*!
  * \file structures.h
  * \brief Regroupe les diffenrentes structures du jeu
  * \author Adrien Nunes
  */
#ifndef STRUCTURES_H
#define STRUCTURES_H

/*!
  * \struct Case
  * \brief Une case de la scene (un caractere et une couleur)
  *
  * Une case est initialisé par un espace comme caractere et une couleur par defaut
  *
  */
struct Case{
    char sonChar = ' ';
    Couleur saCouleur = DEFAULT;
};

/*!
  * \struct Piece
  * \brief Une piece du jeu, defini par sa Hauteur, sa Largeur, son Numero, sa couleur, si elle est jouable, sa forme (tableau), et sa rotation
  */
struct Piece{
    int sonNumero;
    int saHauteur;
    int saLargeur;
    int sonNbrCases = 0;
    bool estDispo = true;
    Couleur saCouleur = ROUGE;
    bool saMatrice[5][5] = {{false}};
    int saRotation = 0;
    int saPosition = 0;

};

/*!
  * \struct Joueur
  * \brief Un joueur, avec un nom, des pieces, un score, son Tour (ordre de passage), et un etat estFini si il a posé toutes ses pieces ou est bloqu"
  */
struct Joueur{
    std::string sonNom;
    Piece sesPieces[NBR_PIECES];
    int sonScore = 0;
    int sonTour;
    bool estFini = false;
    bool estBot = false;
};

#endif // STRUCTURES_H
