#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
#include "jeton.h"

ListeEntite priorite(ListeEntite liste, int priorite){
    int i = 0;
    int found = 0;
    ListeEntite res = liste;

    while(res != NULL && res->jeton.lexem != FIN && !found){
        switch(priorite){
            case 1:
                if(res->jeton.lexem == OPERATEUR && (res->jeton.valeur.operateur == MOINS || res->jeton.valeur.operateur == PLUS))
                    found = 1;
                break;
            case 2:
                if(res->jeton.lexem == OPERATEUR && (res->jeton.valeur.operateur == FOIS || res->jeton.valeur.operateur == DIV))
                    found = 1;
                break;
            case 3:
                if(res->jeton.lexem == FONCTION)
                    found = 1;
                break;
            case 4:
                if(res->jeton.lexem == PAR_OUV)
                    found = 1;
                break;
            case 5:
                if(res->jeton.lexem == REEL)
                    found = 1;
                break;
            default:
                res = NULL;
                break;
        }

        if(!found)
            res = res->suiv;
    }

    return res;
}

Arbre analyse_syntaxique(ListeEntite liste){
    Arbre a = NULL;

    if(liste != NULL) {
        ListeEntite e1 = priorite(liste,1), e5 = priorite(liste,5);
        // afficher_liste(e1);
        // afficher_liste(e5);
        if(e1 != NULL && e1->jeton.lexem != FIN) {
            typejeton mem = e1->jeton;
            e1->jeton.lexem = FIN;
            a = (Arbre)malloc(sizeof(struct Node));
            a->jeton.lexem = OPERATEUR;
            a->jeton.valeur.operateur = mem.valeur.operateur;
            a->fg = analyse_syntaxique(liste);
            a->fd = analyse_syntaxique(e1->suiv);
            e1->jeton.lexem = OPERATEUR;
            e1->jeton.valeur = mem.valeur;
        } else if(e5 != NULL && e5->jeton.lexem != FIN) {
            a = (Arbre)malloc(sizeof(struct Node));
            a->fg = NULL;
            a->fd = NULL;
            a->jeton.lexem = REEL;
            a->jeton.valeur.reel = e5->jeton.valeur.reel;
        }

    }
    return a;
}

void afficher_arbre(Arbre a, int space){

    if(a == NULL)
        return;

    space += 10;

    afficher_arbre(a->fd,space);

    printf("\n");

    int i;
    for(i=10;i<space;i++)
        printf(" ");
    switch(a->jeton.lexem){
        case OPERATEUR:
            printf("OPERATEUR\n");
            break;
        case REEL:
            printf("%f\n",a->jeton.valeur.reel);
            break;
        default:
            printf("FIN\n");
            break;
    }

    afficher_arbre(a->fg,space);
}

void afficher_liste(ListeEntite liste){
    ListeEntite parcours = liste;

    while(parcours != NULL && parcours->jeton.lexem != FIN){
        switch(parcours->jeton.lexem){
            case OPERATEUR:
                printf("OPERATEUR\n");
                break;
            case REEL:
                printf("%f\n",parcours->jeton.valeur.reel);
                break;
            default:
                printf("FIN\n");
                break;
        }

        parcours = parcours->suiv;
    }
    printf("FIN\n");
}