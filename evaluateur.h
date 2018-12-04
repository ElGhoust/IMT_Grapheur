#ifndef EVALUATEUR_H_INCLUDED
#define EVALUATEUR_H_INCLUDED

#include "jeton.h"

typedef struct maillon
{
    float x;
    float y;
    struct maillon *suivant;
}maillon, *ptrMaillon;

ptrMaillon calculIntervalle(Arbre a, float x, float y);

float operation(Arbre a, float x);

void creer_liste_chainee(ptrMaillon *pL);

ptrMaillon creationNoeud(float x, float y);

void inserer(ptrMaillon *pL, float x, float y);

void afficher(ptrMaillon pE);

#endif // EVALUATEUR_H_INCLUDED
