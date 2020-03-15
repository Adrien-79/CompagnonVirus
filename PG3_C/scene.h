/*!
  * \file scene.h
  * \brief Regroupe les fonctions de manipulations de la scene
  * \author Adrien Nunes
  */

#ifndef SCENE_H
#define SCENE_H

/*!
 * \brief Insertion des pieces des joueurs à droite de la scene
 * \param uneScene [out] la scene du jeu
 * \param desJoueurs [in] les joueurs du jeu
 * \param unNbrJoueurs [in] le nombre de joueur
 */
void piecesDansScene(Case uneScene[LIGNE_S][COLONNE_S], Joueur desJoueurs[], int unNbrJoueurs);

/*!
  * \brief Fonction qui retire les pieces à droite de la scene.
  * \param uneScene[out] La scene du jeu
  */
void clearPieces(Case uneScene[LIGNE_S][COLONNE_S]);

/*!
  * \brief Fonction qui place une piece dans le plateau.
  * \param unePiece[in] La piece a placer
  * \param uneScene [out] la scene ou va etre placé la piece,
  * \param uneLigne [in] la Ligne dans la scene ou placer la piece
  * \param uneColonne [in] la colonne dans la scene ou placer la piece
  */
void placer(Piece unePiece, Case uneScene[LIGNE_S][COLONNE_S], int uneLigne, int uneColonne);

/*!
  * \brief Fonction qui test si une piece est placable dans le plateau
  * \param unePiece [in] La piece a tester
  * \param uneScene [in] la scene ou l'on veut tester la piece
  * \param uneLigne [in] la ligne de la scene ou l'on veut tester la piece
  * \param uneColonne [in] la colonne de la scene ou l'on veut tester la piece
  * \return true si la piece peut être placer sinon false.
  */
//bool estPlacable(Piece &unePiece, Case uneScene[LIGNE_S][COLONNE_S], int uneLigne, int uneColonne);

/*!
 * \brief Ecrit une chaine de caractere dans la scene
 * \param unMot [in] la chaine de caractere a inserer
 * \param uneScene [out] la scene ou l'on veut inserer la chaine de caractere
 * \param uneLigne [in] la ligne dans la scene
 * \param uneColonne [in] la colonne dans la scene
 */
void ecrireMot(String unMot,Case uneScene[LIGNE_S][COLONNE_S] ,int uneLigne, int uneColonne);

/*!
 * \brief Insere le score des joueurs dans la scene à droite
 * \param desJoueurs [in] les joueurs a afficher
 * \param unNbrJoueurs [in] le nombre de joueur a afficher
 * \param uneScene [out] la scene
 */
//void putScore(Joueur desJoueurs[], int unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S]);
#endif // SCENE_H
