#ifndef ANALYSE_LEXICALE_H_INCLUDED
#define ANALYSE_LEXICALE_H_INCLUDED
#include "jeton.h"

typedef struct Entite
{
    typejeton jeton;
    struct Entite *pjeton_suiv;
} Entite;
typedef Entite *LinkedList;

void analyseLexicale(char * input);

#endif // ANALYSE_LEXICALE_H_INCLUDED
