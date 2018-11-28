#ifndef ANALYSE_LEXICALE_H_INCLUDED
#define ANALYSE_LEXICALE_H_INCLUDED
#include "jeton.h"

typedef struct Entite
{
    typejeton jeton;
    struct Entite *suiv;
} Entite;
typedef Entite *ListeEntite;

/* Fonction principal de l'analyse lexicale */
ListeEntite analyseLexicale(char * input);

ListeEntite initListe();

ListeEntite ajoutFin(ListeEntite origine,typejeton jeton);

void afficherListe(ListeEntite liste);

#endif // ANALYSE_LEXICALE_H_INCLUDED
