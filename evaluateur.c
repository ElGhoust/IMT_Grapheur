#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>

#include "variables.h"
#include "evaluateur.h"
#include "jeton.h"

/**
 * Permet de savoir si l'arbre passe en parametre est vide ou non, utile pour la fonction operation
 */
int est_vide(Arbre a) {
    int vide = 0;
    if(a == NULL)
        vide = 1;
    return vide;
}

/**
 * Permet d'afficher dans la console la fonction contenue dans l'arbre passe en parametre
 */
void analyse_arbre(Arbre a) {
    if(est_vide(a))
        printf("Vide");
    else {
        if(a->fg != NULL) {
            analyse_arbre(a->fg);
        } else if(a->fd != NULL) {
            analyse_arbre(a->fd);
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
           /* case ERR1:
                break;
            case ERR2:
                break;
            case ERR3:
                break;*/
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

/**
 * Fonction principale de la partie evaluateur, effectue l'operation a partir de l'arbre passe en parametre
 * Cette fonction repose en grande partie sur la recursivite pour lire au mieux l'arbre fournit
 * Le fils gauche est prioritaire au fils droit, notamment pour les fonctions n'utilisant qu'un seul parametre telles
 * que COS, SIN, LOG,... le fils gauche est le seul a contenir une valeur. De meme, pour les operations arithmetiques
 * simple c'est le fils gauche qui est lu en premier puis le fils droit.
 */
float operation(Arbre a, float x) {
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
                    return operation(a->fg, x) + operation(a->fd, x);
                    break;
                case MOINS:
                    return operation(a->fg, x) - operation(a->fd, x);
                    break;
                case FOIS:
                    return operation(a->fg, x) * operation(a->fd, x);
                    break;
                case DIV:
                    return operation(a->fg, x) / operation(a->fd, x);
                    break;
                case PUIS:
                    return pow(operation(a->fg, x), operation(a->fd, x));
                    break;
                default:
                    break;
            }
            break;
        case FONCTION:
            switch(a->jeton.valeur.fonction) {
                case ABS:
                    return abs(operation(a->fg, x));
                    break;
                case SIN:
                    return sin(operation(a->fg, x));
                    break;
                case SQRT:
                    return sqrt(operation(a->fg, x));
                    break;
                case LOG:
                    return log(operation(a->fg, x));
                    break;
                case COS:
                    return cos(operation(a->fg, x));
                    break;
                case TAN:
                    return tan(operation(a->fg, x));
                    break;
                case EXP:
                    return exp(operation(a->fg, x));
                    break;
                case ENTIER:
                    break;
                case VAL_NEG:
                    return 0 - operation(a->fg, x);
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

/**
 * Permet d'effectuer le calcul d'une intervalle de la valeur X jusqu'a la valeur Y sur l'arbre d'operation passe en parametre.
 * Le tout renvoie une liste chainee comportant la valeur testee et le resultat obtenu pour chaque index.
 */
ptrMaillon calculIntervalle(Arbre a, float x, float y) {
    ptrMaillon valeurs;
    float i;
    float index = 0;

    creer_liste_chainee(&valeurs);

    for(i = x; i <= y; i+=pas) {
        inserer(&valeurs, i, operation(a,i));
        index++;
    }
    return valeurs;
}

/**
 * Cree une liste chainee vide
 */
void creer_liste_chainee(ptrMaillon *pL) {
    *pL = NULL;
}

/**
 * Cree un maillon avec en parametre un index et sa valeur asssociee
 */
ptrMaillon creationNoeud(float x, float y) {
    ptrMaillon nouveau = malloc(sizeof(struct maillon));
    nouveau->x = x;
    nouveau->y = y;
    nouveau->suivant=NULL;
    return nouveau;
}

/**
 * Permet d'inserer dans une liste chainee un index et sa valeur associee
 */
void inserer(ptrMaillon *pL, float x, float y) {
    ptrMaillon nouveau = creationNoeud(x, y);
    if(*pL == NULL)
    {
        *pL = nouveau;
    }
    else
    {
        ptrMaillon parcours = *pL;
        while(parcours->suivant != NULL)
        {
          parcours=parcours->suivant;
        }
        parcours->suivant = nouveau;
    }
}

/**
 * Permet d'afficher une liste chainee.
 */
void afficher(ptrMaillon pL) {
    ptrMaillon parcours = pL;
    if(pL == NULL) { printf("La liste est vide !\n\n"); }
    else
    {
        while(parcours != NULL)
        {
            printf("f(%f) = %f\n", parcours->x, parcours->y);
            parcours = parcours->suivant;
        }
    }
}
