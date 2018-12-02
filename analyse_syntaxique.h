#ifndef ANALYSE_SYNTAXIQUE_H_INCLUDED
#define ANALYSE_SYNTAXIQUE_H_INCLUDED

#include "jeton.h"
#include "analyse_lexicale.h"

ListeEntite priorite(ListeEntite liste, int priorite);
Arbre getSyntaxeFromLexique(ListeEntite liste);
Arbre analyse_syntaxique(ListeEntite);
void afficher_arbre(Arbre a, int space);
void afficher_liste(ListeEntite liste);
void jeton_to_character(typejeton j);
ListeEntite insererEntite(ListeEntite e, typejeton j);
typeerreur findErrorListe(ListeEntite l);
int countJeton(ListeEntite l, typejeton j);
int jetonCompare(typejeton j1, typejeton j2);
typeerreur hasBadLexemSequence(ListeEntite l);
int hasPriorityMismatch(ListeEntite l);
int hasError(ListeEntite l);
ListeEntite getFirstJeton(ListeEntite l, typejeton j);
ListeEntite getLastJeton(ListeEntite l, typejeton j);
void copyJeton(typejeton in, typejeton * out);
ListeEntite clean(ListeEntite l);
ListeEntite cleanSequencePlusMoins(ListeEntite l);
ListeEntite cleanStartPlusMoins(ListeEntite l);
ListeEntite cleanSequenceReelVariable(ListeEntite l);
typeoperateur mergePlusMoins(ListeEntite l);
typelexem getClosingTag(typelexem l);

ListeEntite getClosingTagListe(ListeEntite l);

#endif // ANALYSE_SYNTAXIQUE_H_INCLUDED
