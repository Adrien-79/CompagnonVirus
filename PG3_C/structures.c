#include "enum.h"

#include "structures.h"

Case Case_new(){
	return (Case) {' ', DEFAULT};
}


Piece Piece_new(){
	return (Piece) {-1, -1, -1, 0, true, ROUGE, {{false}}, 0, 0};
}


Joueur Joueur_new(){
	return (Joueur) {"NULL", {}, 0, 0, false, false};
}
