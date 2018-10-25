#ifndef ANALYSE_SYNTAXIQUE_H_INCLUDED
#define ANALYSE_SYNTAXIQUE_H_INCLUDED

#include "jeton.h"
#include "analyse_lexicale.h"

ListeEntite priorite(ListeEntite liste, int priorite);
ListeEntite cleanup(ListeEntite l);
Arbre findError(ListeEntite l);
Arbre analyse_syntaxique(ListeEntite);
ListeEntite trouver_fermeture_parenthese(ListeEntite e);
ListeEntite trouver_fermeture_crochet(ListeEntite e);
void afficher_arbre(Arbre a, int space);
void afficher_liste(ListeEntite liste);
void jeton_to_character(typejeton j);
ListeEntite insererEntite(ListeEntite e, typejeton j);

#endif // ANALYSE_SYNTAXIQUE_H_INCLUDED
