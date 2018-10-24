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

Arbre analyse_syntaxique(ListeEntite liste){
    Arbre a = NULL;

    if(liste != NULL) {
        ListeEntite e1 = priorite(liste,1), e2 = priorite(liste,1), e3 = priorite(liste,1), e4 = priorite(liste,1), e5 = priorite(liste,5);
        if(e1 != NULL) {
            typejeton mem = e1->jeton;
            e1->jeton.lexem = FIN;
            a = (Arbre)malloc(sizeof(struct Node));
            a->jeton.lexem = OPERATEUR;
            a->jeton.valeur = mem.valeur;
            a->fg = analyse_syntaxique(liste);
            a->fd = analyse_syntaxique(e1->suiv);
            e1->jeton.lexem = OPERATEUR;
            e1->jeton.valeur = mem.valeur;
        } else if(e5 != NULL) {
            a = (Arbre)malloc(sizeof(struct Node));
            a->fg = NULL;
            a->fd = NULL;
            a->jeton.lexem = REEL;
            a->jeton.valeur = e5->jeton.valeur;
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