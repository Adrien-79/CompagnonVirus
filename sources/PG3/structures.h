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
    char sonChar;
    Couleur saCouleur;
};

typedef struct Case Case;


Case Case_new();
/*!
  * \struct Piece
  * \brief Une piece du jeu, defini par sa Hauteur, sa Largeur, son Numero, sa couleur, si elle est jouable, sa forme (tableau), et sa rotation
  */
struct Piece{
    int sonNumero;
    int saHauteur;
    int saLargeur;
    int sonNbrCases;
    bool estDispo;
    Couleur saCouleur;
    bool saMatrice[5][5];
    int saRotation;
    int saPosition;

};

typedef struct Piece Piece;

Piece Piece_new();

/*!
  * \struct Joueur
  * \brief Un joueur, avec un nom, des pieces, un score, son Tour (ordre de passage), et un etat estFini si il a posé toutes ses pieces ou est bloqu"
  */
struct Joueur{
    char* sonNom;
    Piece sesPieces[21];
    int sonScore;
    int sonTour;
    bool estFini;
    bool estBot;
};

typedef struct Joueur Joueur;

Joueur Joueur_new();

#endif // STRUCTURES_H
