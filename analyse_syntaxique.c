#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
#include "jeton.h"

int priorite(typejeton * j, int priorite){
    int res = -1, i = 0;

    while(j[i].lexem != FIN){
        switch(priorite){
            case 1:
                if(j[i].lexem == OPERATEUR && (j[i].valeur.operateur == MOINS || j[i].valeur.operateur == PLUS))
                    res = i;
                break;
            case 2:
                if(j[i].lexem == OPERATEUR && (j[i].valeur.operateur == FOIS || j[i].valeur.operateur == DIV))
                    res = i;
                break;
            case 3:
                if(j[i].lexem == FONCTION)
                    res = i;
                break;
            case 4:
                if(j[i].lexem == BAR_OUV)
                    res = i;
                break;
            case 5:
                if(j[i].lexem == REEL)
                    res = i;
                break;
            default:
                res = -1;
                break;
        }

        i++;
    }

    return res;
}

Arbre analyse_syntaxique(typejeton * j){
    Arbre a = NULL;

    if(j != NULL) {
        int i1 = priorite(j,1), i2 = priorite(j,1), i3 = priorite(j,1), i4 = priorite(j,1), i5 = priorite(j,5);
        if(i1 != -1) {
            typejeton mem = j[i1];
            j[i1].lexem = FIN;
            a = (Arbre)malloc(sizeof(struct Node));
            a->jeton.lexem = OPERATEUR;
            a->jeton.valeur = mem.valeur;
            a->fg = analyse_syntaxique(j);
            a->fd = analyse_syntaxique(&j[i1 + 1]);
        } else if(i5 != -1) {
            a = (Arbre)malloc(sizeof(struct Node));
            a->fg = NULL;
            a->fd = NULL;
            a->jeton.lexem = REEL;
            a->jeton.valeur = j[i5].valeur;
        }

    }
    return a;
}

void afficher_arbre(Arbre a){

    if(a != NULL){
        afficher_arbre(a->fg);
        if(a->jeton.lexem == OPERATEUR && a->jeton.valeur.operateur == PLUS){
            printf("+\n");
        } else {
            printf("%f\n", a->jeton.valeur.reel);
        }
        afficher_arbre(a->fd);
    }
}

void afficher_tab_jeton(typejeton * j){
    int i = 0;

    while(j[i].lexem != FIN){
        if(j[i].lexem == REEL)
            printf("-%f\n",j[i].valeur.reel);
        else
            printf("-+\n");

        i++;
    }
}