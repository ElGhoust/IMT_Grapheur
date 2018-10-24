#ifndef ANALYSE_SYNTAXIQUE_H_INCLUDED
#define ANALYSE_SYNTAXIQUE_H_INCLUDED

#include "jeton.h"
#include "analyse_lexicale.h"

ListeEntite priorite(ListeEntite liste, int priorite);
Arbre analyse_syntaxique(typejeton * j);
void afficher_arbre(Arbre a);
void afficher_tab_jeton(typejeton * j);

#endif // ANALYSE_SYNTAXIQUE_H_INCLUDED
