#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include "jeton.h"

int est_vide(Arbre a) {
    int vide = 0;
    if(a == NULL)
        vide = 1;
    return vide;
}

/**
Fonction test de la lecture de l'arbre

Affiche le contenu de l'arbre
**/
void analyse_arbre(Arbre a) {
    if(est_vide(a))
        printf("Vide");
    else {
        if(a->pjeton_preced != NULL) {
            analyse_arbre(a->pjeton_preced);
        } else if(a->pjeton_suiv != NULL) {
            analyse_arbre(a->pjeton_suiv);
        switch(a->jeton.lexem) {
        case REEL:
            printf("%lf", a->jeton.valeur.reel);
            break;
        case OPERATEUR:
            switch(a->jeton.valeur.operateur) {
            case PLUS:
                printf("+");
                break;
            case MOINS:
                printf("-");
                break;
            case FOIS:
                printf("x");
                break;
            case DIV:
                printf("/");
                break;
            case PUIS:
                printf("^");
                break;
            default:
                break;
            }
            break;
        case FONCTION:
            switch(a->jeton.valeur.fonction) {
            case ABS:
                printf("ABS(");
                break;
            case SIN:
                printf("SIN(");
                break;
            case SQRT:
                printf("SQRT(");
                break;
            case LOG:
                printf("LOG(");
                break;
            case COS:
                printf("COS(");
                break;
            case TAN:
                printf("TAN(");
                break;
            case EXP:
                printf("EXP(");
                break;
            case ENTIER:
                printf("ENTIER(");
                break;
            case VAL_NEG:
                printf("-");
                break;
            case SINC:
                printf("SINC(");
                break;
            default:
                break;
            }
            break;
        case ERREUR:
            switch(a->jeton.valeur.erreur) {
            case ERR1:
                break;
            case ERR2:
                break;
            case ERR3:
                break;
            default:
                break;
            }
            break;
        case FIN:
            break;
        case PAR_OUV:
            break;
        case PAR_FERM:
            break;
        case VARIABLE:
            break;
        case BAR_OUV:
            break;
        case BAR_FERM:
            break;
        case ABSOLU:
            break;
        default:
            break;
        }
        }
    }
}

int operation(Arbre a, int x) {
    if(a == NULL) {
        return 0;
    }
    switch(a->jeton.lexem) {
        case REEL:
            return a->jeton.valeur.reel;
            break;
        case OPERATEUR:
            switch(a->jeton.valeur.operateur) {
                case PLUS:
                    return operation(a->pjeton_preced, x) + operation(a->pjeton_suiv, x);
                    break;
                case MOINS:
                    return operation(a->pjeton_preced, x) - operation(a->pjeton_suiv, x);
                    break;
                case FOIS:
                    return operation(a->pjeton_preced, x) * operation(a->pjeton_suiv, x);
                    break;
                case DIV:
                    return operation(a->pjeton_preced, x) / operation(a->pjeton_suiv, x);
                    break;
                default:
                    break;
            }
            break;
        case FONCTION:
            switch(a->jeton.valeur.fonction) {
                case ABS:
                    return abs(operation(a->pjeton_preced, x));
                    break;
                case SIN:
                    return sin(operation(a->pjeton_preced, x));
                    break;
                case SQRT:
                    return sqrt(operation(a->pjeton_preced, x));
                    break;
                case LOG:
                    return log(operation(a->pjeton_preced, x));
                    break;
                case COS:
                    return cos(operation(a->pjeton_preced, x));
                    break;
                case TAN:
                    return tan(operation(a->pjeton_preced, x));
                    break;
                case EXP:
                    return exp(operation(a->pjeton_preced, x));
                    break;
                case ENTIER:
                    break;
                case VAL_NEG:
                    return 0 - operation(a->pjeton_preced, x);
                    break;
                case SINC:
                    break;
                default:
                    break;
            }
            break;
        case ERREUR:
            printf("Erreur rencontree. Fin du programme.");
            exit(0);
            break;
        case FIN:
            break;
        case PAR_OUV:
            break;
        case PAR_FERM:
            break;
        case VARIABLE:
            return x;
            break;
        case BAR_OUV:
            break;
        case BAR_FERM:
            break;
        case ABSOLU:
            break;
        default:
            break;
    }
    return 0;
}


int * calculIntervalle(Arbre a, int x, int y) {
    int * valeurs = (int *)malloc(sizeof(int *));
    int i;

    for(i = x; i < y; i++) {
        valeurs[i] = operation(a, i);
    }
    return valeurs;
}
