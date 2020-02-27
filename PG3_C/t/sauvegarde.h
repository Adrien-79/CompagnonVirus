/*!
  * \file sauvegarde.h
  * \brief Sauvegarde et chargement d'une partie.
  * \author Adrien Nunes
  */
#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H


/*!
 * \brief Fonction permetant la sauvegarde d'une partie dans un fichier blokus.data
 * \param desJoueurs [in] la liste des joueurs de la partie
 * \param unNbrJoueurs [in] le nombre de joueurs dans la partie
 * \param uneScene [in] la scene de la partie
 * \param unNomFichierS [in] le nom du fichier pour sauvegardé la partie
 */
void sauvegarder(Joueur desJoueurs[], int unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S], std::string &unNomFichierS);

/*!
 * \brief Fonction permetant de charger une partie via un fichier blokus.data
 * \param desJoueurs [out] la liste des joueurs de la partie
 * \param unNbrJoueurs [out] le nombre de joueurs dans la partie
 * \param uneScene [out] la scene de la partie
 * \param unNomFichierP [in] le nom du fichier contenant les pieces
 * \param unNomFichierS [in] le nom du fichier ou se trouve la sauvegarde du jeu
 */
void charger(Joueur desJoueurs[], int& unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S],std::string &unNomFichierP, std::string &unNomFichierS);

/*!
 * \brief Fonction permetant de coder un entier en binaire dans un fichier selon une taille.
 * \param unNombre [in] l'entier a coder dans le fichier
 * \param uneTaille [in] la taille en bit que doit prendre l'information a coder dans le fichier
 * \param unDecalage [in out] le decalage sur l'octer pour rentrer une prochaine valeur (comme un curseur)
 * \param unOctet [in out] l'octet ou l'on ecris, quand celui ci est rempli il est ecrit dans le fichier binaire.
 * \param unFichier [out] le fichier de sauvegarde
 */
void putFichier(int unNombre, int uneTaille, int &unDecalage, unsigned char &unOctet, std::ofstream &unFichier);

/*!
 * \brief Fonction permetant de recuperer un entier depuis un fichier binaire
 * \param uneTaille [in] la taille en bit de l'entier a recuperer
 * \param unDecalage [in out] le decalage sur l'octer pour lire une prochaine valeur (comme un curseur)
 * \param unOctet [in out] l'octet ou l'on lis, quand on arrive a la fin de celui ci, on recupere le prochain octet du fichier.
 * \param unFichier [in] le fichier de sauvegarde
 * \return Renvoie l'entier codé sur le(s) octet(s).
 */
int getFichier(int uneTaille, int &unDecalage, unsigned char &unOctet, std::ifstream &unFichier);

/*!
 * \brief Fonction permetant de coder la couleur sur les 4 coins du plateau de jeu dans un fichier binaire de sauvegarde
 * \param uneScene [out] la scene du jeu, où se trouve les 4 coins
 * \param unDecalage [in out] le decalage sur l'octer pour ecrire une prochaine valeur (comme un curseur)
 * \param unOctet [in out] l'octet ou l'on ecris, quand celui ci est rempli il est ecrit dans le fichier binaire.
 * \param unFichier [in] le fichier de sauvegarde
 */
void putCoin(Case uneScene[LIGNE_S][COLONNE_S], int &unDecalage, unsigned char &unOctet, std::ofstream &unFichier);

/*!
 * \brief Fonction permetant de coder un nom dans un fichier binaire, un caractere etant codé sur 6 bits (a-z, A-Z, ' ', ''', '-')
 * \param unNom [in] le nom du joueur a coder dans le fichier
 * \param unOctet [in out] l'octet ou l'on ecris, quand celui ci est rempli il est ecrit dans le fichier binaire.
 * \param unDecalage [in out] le decalage sur l'octer pour ecrire une prochaine valeur (comme un curseur)
 * \param unFichier [in] le fichier de sauvegarde
 */
void putNom(std::string &unNom, unsigned char &unOctet, int &unDecalage, std::ofstream &unFichier);

/*!
 * \brief Fonction permetant de recuperer le nom et de l'intialiser pour un joueur, à partir d'un fichier de sauvegarde binaire
 * \param unJoueur [out] le joueur ou l'on veut ecrire le nom
 * \param unOctet [in out] l'octet ou l'on lis actuellement
 * \param unDecalage [in out] le decalage sur l'octer pour ecrire une prochaine valeur (comme un curseur)
 * \param uneValeur [in out] la valeur lue (6bits), a la fin de la fonction elle retourne le separateur ( nom / piece ) qui est la couleur des pieces du joueur
 * \param unFichier [in] le fichier lu de sauvegarde
 */
void setNom(Joueur &unJoueur, unsigned char &unOctet, int &unDecalage,int &uneValeur, std::ifstream &unFichier);

/*!
 * \brief Fonction permetant de recuperer la position et la rotation des pieces, à partir d'un fichier de sauvegarde binaire
 * \param desPieces [out] les pieces a modifier
 * \param unOctet [in out] l'octet ou l'on lis actuellement
 * \param unDecalage [in out] le decalage sur l'octer pour ecrire une prochaine valeur (comme un curseur)
 * \param uneCouleur [in] valeur de la couleur en entier (de 55 à 58)
 * \param unFichier [in] le fichier lu de sauvegarde
 * \param unNomFichierP [in] le fichier où se trouve les pieces
 * \param uneScene [out] la scene du jeu où placer les pieces
 */
void setPieces(Piece desPieces[], unsigned char &unOctet, int &unDecalage, int uneCouleur, std::ifstream &unFichier, std::string &unNomFichierP, Case uneScene[LIGNE_S][COLONNE_S]);


/*!
 * \brief Fonction permetant d'inserer la piece à un emplacement dans la scene
 * \param unePiece [in out] la piece à placer
 * \param unePosition [in] l'emplacement dans la scene de la piece (de 0 à 400, 400 étant une piece non placée)
 * \param uneScene [out] la scene du jeu où placer la piece
 */
void setPosition(Piece &unePiece, int unePosition, Case uneScene[LIGNE_S][COLONNE_S]);

/*!
 * \brief Fonction permetant de recuperer et d'insrer dans la scene, les couleurs des quatres coins de la scene via un fichier de sauvegarde bianaire
 * \param uneScene [out] la scene où l'on veut inserer les 4 coins
 * \param unDecalage [in out] le decalage sur l'octer pour ecrire une prochaine valeur (comme un curseur)
 * \param unOctet [in out] l'octet ou l'on lis actuellement
 * \param unFichier [in] le fichier lu de sauvegarde
 */
void setCoin(Case uneScene[LIGNE_S][COLONNE_S], int &unDecalage, unsigned char &unOctet , std::ifstream &unFichier);

/*!
 * \brief Fonction permetant de reinitialiser une liste de piece
 * \param desPieces [out] la liste des pieces a reinitialiser
 */
void resetPieces(Piece desPieces[]);

/*!
 * \brief Fonction permetant la convertion d'un type Couleur en un type int (de 55 à 58)
 * \param uneCouleur [in] la couleur a coder en entier
 * \return Un entier qui correspond à la couleur (Bleu : 55, Jaune : 56, Rouge : 57, Vert : 58)
 */
int couleurToInt(Couleur uneCouleur);

/*!
 * \brief Fonction permetant la convertion d'un type int (de 55 à 58) en un type Couleur
 * \param unEntier [in] Un entier qui correspond à la couleur (Bleu : 55, Jaune : 56, Rouge : 57, Vert : 58)
 * \return La couleur qui correspond à l'entier
 */
Couleur intToCouleur(int unEntier);

/*!
 * \brief Fonction qui demande au joueur une confirmation pour la sauvegarde d'une partie, (O / N) si le confirme alors la fontion sauvegarde la partie, la fonction renvoie un message d'info
 * \param desJoueurs [in] Les joueurs de la partie
 * \param unNbrJoueurs [in] Le nombre de joueurs de la partie
 * \param uneScene [in] La scene de la partie
 * \param unNomFichierS [in] Le nom du fichier pour la sauvegarde du jeu
 * \param unMessage [out] Le message d'information en retour
 */
void demandeSauvegarde(Joueur desJoueurs[], int unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S], std::string &unNomFichierS, std::string &unMessage);

/*!
 * \brief Fonction qui demande au joueur une confirmation pour le chargement d'une partie, (O / N) si le confirme alors la fontion charge la partie via le foichier, la fonction renvoie un message d'info
 * \param desJoueurs [in] Les joueurs de la partie
 * \param unNbrJoueurs [in] Le nombre de joueurs de la partie
 * \param uneScene [in] La scene de la partie
 * \param unNomFichierP [in] Le nom du fichier pour les pieces du jeu
 * \param unNomFichierS [in] Le nom du fichier pour la sauvegarde du jeu
 * \param unMessage [out] Le message d'information en retour
 * \param uneMain [in] Index du joueur ayant la main sur le jeu
 */
void demandeCharger(Joueur desJoueurs[], int& unNbrJoueurs, Case uneScene[LIGNE_S][COLONNE_S],std::string &unNomFichierP, std::string &unNomFichierS, std::string &unMessage, int &uneMain);
#endif // SAUVEGARDE_H
