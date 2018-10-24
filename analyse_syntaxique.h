#ifndef ANALYSE_SYNTAXIQUE_H_INCLUDED
#define ANALYSE_SYNTAXIQUE_H_INCLUDED

#include "jeton.h"
#include "analyse_lexicale.h"

ListeEntite priorite(ListeEntite liste, int priorite);
Arbre analyse_syntaxique(ListeEntite);
void afficher_arbre(Arbre a, int space);
void afficher_liste(ListeEntite liste);

#endif // ANALYSE_SYNTAXIQUE_H_INCLUDED
