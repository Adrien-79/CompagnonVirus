/*!
  * \file bot.h
  * \brief Regroupe les fonctions liées à l'inteligence artificielle
  * \author Adrien Nunes
  */
#ifndef BOT_H
#define BOT_H
/*!
 * \brief Permet de faire jouer le bot.
 * \param unJoueur [in out] le joueur bot
 * \param uneScene [in out] la scene du jeu
 * \param desJoueurs [in] tous les joueurs
 * \param unNbrJoueurs [in] le nombre de joueurs dans la partie
 */
void jouerBot(Joueur *unJoueur, Case uneScene[LIGNE_S][COLONNE_S], Joueur desJoueurs[], int unNbrJoueurs);

/*!
 * \brief Fonction permetant d'évaluer la qualité d'un coup (une piece, des coordonées) en fonction de plusieurs calculs
 * \param unePiece [in] la piece à evaluer
 * \param uneScene [in] la scene du jeu
 * \param uneLigne [in] coordonée de la ligne de la piece
 * \param uneColonne [in] coordonée de la colonne de la piece
 * \param desJoueurs [in] liste des joueurs
 * \param unNbrJoueurs [in] le nombre de joueurs en jeu
 * \return La valeur de la qualité du coup évalué
 */
long evaluerCoup(Piece unePiece, Case uneScene[LIGNE_S][COLONNE_S], int uneLigne, int uneColonne, Joueur desJoueurs[], int unNbrJoueurs);

/*!
 * \brief Fonction permetant de calculer la distance minimum entre une piece et le centre du plateau
 * \param unePiece [in] la piece à evaluer
 * \param uneScene [in] la scene du jeu
 * \param uneLigne [in] coordonée de la ligne de la piece
 * \param uneColonne [in] coordonée de la colonne de la piece
 * \return La distance minimum entre la piece et le centre du plateau
 */
int distanceCentreMin(Piece unePiece, int uneLigne, int uneColonne);

/*!
 * \brief Fonction permetant de calculer la distance minimum entre une piece et la piece adverse la plus proche
 * \param unePiece [in] la piece à evaluer
 * \param uneLigne [in] coordonée de la ligne de la piece
 * \param uneColonne [in] coordonée de la colonne de la piece
 * \return La distance minimum entre une piece et la piece adverse la plus proche
 */
int distancePiecesMin(Piece unePiece, Case uneScene[LIGNE_S][COLONNE_S], int uneLigne, int uneColonne);

/*!
 * \brief Fonction permetant de calculer, pour une piece, le nombre de combinaisons de pieces adverses bloquées avec cette piece
 * \param unePiece [in] la piece à evaluer
 * \param uneLigne [in] coordonée de la ligne de la piece
 * \param uneColonne [in] coordonée de la colonne de la piece
 * \param desJoueurs [in] liste des joueurs
 * \param unNbrJoueurs [in] le nombre de joueurs en jeu
 * \param uneScene [in] la scene du jeu
 * \return Le nombre de combinaisons de pieces adverses bloquées avec la piece
 */
int piecesBloquees(Piece unePiece, int uneLigne, int uneColonne, Joueur desJoueurs[], int unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S]);

#endif // BOT_H
