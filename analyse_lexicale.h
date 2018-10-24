#ifndef ANALYSE_LEXICALE_H_INCLUDED
#define ANALYSE_LEXICALE_H_INCLUDED

#include "jeton.h"

typedef struct Entite
{
    typejeton jeton;
    struct Entite *suiv;
} Entite;
typedef Entite * ListeEntite;

void analyseLexicale(char * input);

#endif // ANALYSE_LEXICALE_H_INCLUDED
