#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"
#include "analyse_syntaxique.h"
#include "jeton.h"

int main()
{
    typejeton j1,j2,j3,j5;
    typevaleur v1,v2,v3;
    typeoperateur t1 = PLUS;
    typelexem l = FIN;

    v1.reel = 3;
    v2.reel = 2;
    v3.operateur = t1;

    j1.lexem = REEL;
    j1.valeur = v1;

    j2.lexem = REEL;
    j2.valeur = v2;

    j3.lexem = OPERATEUR;
    j3.valeur = v3;

    j5.lexem = l;

    typejeton j4[6];

    j4[0] = j1;
    j4[1] = j3;
    j4[2] = j2;
    j4[3] = j3;
    j4[4] = j1;
    j4[5] = j5;

    afficher_arbre(analyse_syntaxique(j4));

    return 0;
}
