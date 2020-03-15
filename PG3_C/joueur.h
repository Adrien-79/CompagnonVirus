/*!
  * \file joueur.h
  * \brief Regroupe les fonctions liées aux joueurs
  * \author Adrien Nunes
  */
#ifndef JOUEUR_H
#define JOUEUR_H
/*!
 * \brief Recherche dans la liste un joueur en fonction de son tour
 * \param desJoueurs [in] liste des joueurs
 * \param unNbrJoueurs [in] le nombre de joueurs
 * \param unTour [in] le Tour recherché
 * \return la Position du joueur dans la liste en fonction de son tour
 */
int joueurTour(Joueur desJoueurs[], int unNbrJoueurs, int unTour);

/*!
 * \brief Change le tour de tous les joueurs
 * \param desJoueurs [in out] les joueurs
 * \param unNbrJoueurs [in] le nombre de joueur
 */
//void changeTour(Joueur desJoueurs[], int unNbrJoueurs);

/*!
 * \brief Recherche le prochain joueur a pouvoir jouer, renvoie un message si un joueur passe son tour puis marque ce joueur comme ayant fini de jouer
 * \param desJoueurs [in out] les joueurs
 * \param unNbrJoueurs [in] le nombre de joueurs
 * \param uneMain [in out] index du joueur (dans la liste) ayant la main sur le jeu
 * \param uneScene [in] la scene du jeu
 * \param unMessage [out] le message a renvoyer si un joueur passe son tour
 */
//void passeLeTour(Joueur desJoueurs[], int unNbrJoueurs, int &uneMain, Case uneScene[LIGNE_S][COLONNE_S], std::string &unMessage);

/*!
 * \brief Demande au joueur ayant la main une sequence, puis annalyse et execute la séquence
 * \param unJoueur [in out] le joueur ayant la main
 * \param uneScene [in out] la scene du jeu
 * \return true, si le joueur a pu placer une piece, sinon false
 */
//bool jouer(Joueur &unJoueur,std::string &uneCommande ,Case uneScene[LIGNE_S][COLONNE_S]);

/*!
 * \brief Test si un joueur a encore la possibilité de jouer
 * \param unJoueur [in out] le joueur a tester
 * \param uneScene [in] la scene du jeu
 * \return true si le joueur peut encore jouer, sinon la fonction renvoie false, et le joueur est marqué comme ayant fini
 */
//bool peutJouer(Joueur &unJoueur, Case uneScene[LIGNE_S][COLONNE_S]);

/*!
 * \brief Test si le jeu est terminé
 * \param desJoueurs [in out] les joueurs
 * \param unNbrJoueurs [in] le nombre de joueur
 * \param uneScene [in] la scene du jeu
 * \return true si le jeu est fini, sinon false
 */
//bool estFini(Joueur desJoueurs[], int unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S]);

/*!
 * \brief Test si un joueur a encore des pieces à placer
 * \param unJoueur [in out] le joueur a tester
 * \return true, si il peut encore placer des pieces, sinon false et le marque comme ayant fini
 */
//bool aEncorePiece(Joueur &unJoueur);

/*!
 * \brief Analyse un commande rentrer par un joueur, et renvoie une table des rotations et un placement a faire avec une syntaxe correcte
 * \param uneCommande [in] la commande a analyser
 * \param desRotations [out]  la table des rotations a faire
 * \param unPlacement [out] la placement de la piece (la piece, la ligne, la colonne)
 */
//void analyser(std::string &uneCommande, std::string &desRotations, int unPlacement[3]);

/*!
 * \brief Calcule le score d'un joueur quand celui ci a posé toutes ses pieces
 * \param unJoueur [in out] le joueur a calculer
 * \param unNombre [in] nombre de cases de la derniere piece posée par le joueur
 */
//void ajoutScore(Joueur &unJoueur, int unNombre);

/*!
 * \brief Calcule le score en fin de partie par piece non posee
 * \param desJoueurs [in out] les joueurs
 * \param unNombre [in] le nombre de joueur
 */
//void calculeScore(Joueur desJoueurs[2], int unNbrJoueurs);

/*!
 * \brief Trouve le joueur avec le score le plus haut dans une liste
 * \param desJoueurs [in] les joueurs du jeu
 * \param desJoueursTri [in out] liste des joueurs a choisir
 * \param unIndexMax [in out] l'index maximum de la liste des joueur a choisir
 * \return l'index du joueur avec le score maximum.
 */
//int max(Joueur desJoueurs[], int desJoueursTri[], int &unIndexMax);



#endif // JOUEUR_H
