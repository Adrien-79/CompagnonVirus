/*!
  * \file init.h
  * \brief Regroupe les fonctions d'initialisation du jeu.
  * \author Adrien Nunes
  */

#ifndef INIT_H
#define INIT_H


/*!
 * \brief Fonction qui demande a l'utilisateur de rentrer un nombre de bot, il ne peut y avoir aucun bot, comme il peut y avoir que des bots
 * \param unNbrJoueurs [out] le nombre de joueurs
 * \return le nombre de bots
 */
int demandeNbrBots(int unNbrJoueurs);

/*!
  * \brief Fonction initialisation de la Scene.
  * \param uneScene [out] La scene du jeu
  */
  void init_Scene(Case (*uneScene)[COLONNE_S]);

/*!
  * \brief Fonction initialisation de la liste des pieces.
  * \param desPieces [out] tableau qui va stocker les pieces du jeux
  * \param uneCouleur [in] la Couleur des pieces
  * \param unNomFichier [in] nom du fichier où se trouvent les pieces du jeux.
  */
void init_Piece(Piece desPieces[NBR_PIECES], Couleur uneCouleur, String unNomFichier);

/*!
  * \brief Fonction tire un couleur aléatoire d'un tableau.
  * \param uneListeCouleur [in out] comporte la listes des couleurs
  * \param unIndexMax [in out] represente l'index maximum du tableau de couleur.
  * \return La couleur tirée aleatoirement.
  *
  * un IndexMax est passé en reference car une fois la couleur tirée, cette couleur est remplacée par la derniere couleur du tableau
  * puis l'index maximum diminu afin de ne pas retirer la même couleur.
  *
  */
Couleur randomColor(Couleur uneListeCouleur[], int * unIndexMax);

/*!
 * \brief Demande la saisie du nombre de joueur et verifie si la saisie est correcte
 * \param unNbrJoueurs [out] le nombre de joueurs dans la partie
 * \return true si le joueur lance une sauvegarde, sinon false
 */
bool nbrJoueurs(int * unNbrJoueurs, int * unNbrBots);

/*!
 * \brief Initialise les joueurs
 * \param desJoueurs [out] listes des joueurs a initialiser
 * \param unNbrJoueurs [in] nombre de joueurs a creer
 * \param unFichierP [in] le nom du fichier ou se trouve les pieces
 */
void init_Joueur(Joueur desJoueurs[], int unNbrJoueurs, int unNbrBots, bool estUneSauvegarde, String unFichierP);

#endif // INIT_H
