#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
#include "jeton.h"

ListeEntite priorite(ListeEntite liste, int priorite){
    int i = 0;
    ListeEntite res = liste;

    while(res != NULL){
        switch(priorite){
            case 1:
                if(res->jeton.lexem == OPERATEUR && (res->jeton.valeur.operateur == MOINS || res->jeton.valeur.operateur == PLUS))
                    break;
            case 2:
                if(res->jeton.lexem == OPERATEUR && (res->jeton.valeur.operateur == FOIS || res->jeton.valeur.operateur == DIV))
                    break;
            case 3:
                if(res->jeton.lexem == FONCTION)
                    break;
            case 4:
                if(res->jeton.lexem == BAR_OUV)
                    break;
            case 5:
                if(res->jeton.lexem == REEL)
                    break;
            default:
                res = NULL;
                break;
        }

        res = res->suiv;
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