/*!
  * \file piece.h
  * \brief Regroupe les fonctions des manipulations des pieces
  * \author Adrien Nunes
  */
#ifndef PIECE_H
#define PIECE_H

/*!
 * \brief Rotation horaire d'une piece
 * \param unePiece [in out] la piece a tourner
 */
void rotation(Piece & unePiece);

/*!
 * \brief Miroir selon un axe vertical d'une piece
 * \param unePiece [in out] la piece a tourner
 */
void vertical(Piece & unePiece);

/*!
 * \brief Miroir selon un axe horinzontal d'une piece
 * \param unePiece [in out] (la piece a tourner
 */
void horizontal(Piece & unePiece);

/*!
 * \brief Execute une séquence de rotations sur des pieces
 * \param desRotations [in] table des rotations et des pieces a executer
 * \param desPieces [in out] liste des pieces d'un joueur
 * \return true, si l'execution s'est passée correctement sinon false
 */

bool executer(std::string &desRotations,Piece desPieces[NBR_PIECES]);

/*!
 * \brief Fonction permetant d'inserer une rotation sur une piece
 * \param unePiece [out] la piece a modifier
 * \param uneRotation [int] la rotation a effectuer (de 0 à 8)
 */
void setRotation(Piece &unePiece, int uneRotation);


#endif // PIECE_H
