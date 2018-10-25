#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
#include "jeton.h"

ListeEntite priorite(ListeEntite liste, int priorite) {
	int i = 0;
	int found = 0, parentheses = 0, crochets = 0, pipe = 0;
	ListeEntite res = liste;

	while (res != NULL && res->jeton.lexem != FIN && !found) {
		if (parentheses != 0 || crochets != 0) {
			if (res->jeton.lexem == PAR_FERM && parentheses != 0)
				parentheses--;
			else if (res->jeton.lexem == PAR_OUV)
				parentheses++;
            else if (res->jeton.lexem == BAR_FERM && crochets != 0)
                crochets--;
            else if (res->jeton.lexem == BAR_OUV)
                crochets++;

		}
		else {
			if (res->jeton.lexem == PAR_OUV)
				parentheses = 1;
            else if (res->jeton.lexem == BAR_OUV)
                crochets = 1;

			switch (priorite) {
			case 1:
				if (res->jeton.lexem == OPERATEUR && (res->jeton.valeur.operateur == MOINS || res->jeton.valeur.operateur == PLUS))
					found = 1;
				break;
			case 2:
				if (res->jeton.lexem == OPERATEUR && (res->jeton.valeur.operateur == FOIS || res->jeton.valeur.operateur == DIV))
					found = 1;
				break;
			case 3:
				if (res->jeton.lexem == FONCTION)
					found = 1;
				break;
			case 4:
				if (res->jeton.lexem == PAR_OUV || res->jeton.lexem == BAR_OUV)
					found = 1;
				break;
			case 5:
				if (res->jeton.lexem == REEL || res->jeton.lexem == VARIABLE)
					found = 1;
				break;
			default:
				res = NULL;
				break;
			}
		}

		if (!found)
			res = res->suiv;
	}

	return res;
}

ListeEntite cleanup(ListeEntite l) {
    ListeEntite start = l;
    return l;
}

Arbre findError(ListeEntite l) {
    ListeEntite start = l;
    Arbre a = NULL;

    if(start->jeton.lexem == OPERATEUR && start->jeton.valeur.operateur != MOINS) {

    }

    while(l != NULL && l->jeton.lexem != FIN) {
        //Trop d'opérateur qui se suivent
        if(l->jeton.lexem == OPERATEUR && l->suiv->jeton.lexem == OPERATEUR) {
            a = (Arbre)malloc(sizeof(struct Node));
            a->jeton.lexem = ERR;
            a->jeton.valeur.erreur = TOO_MANY_OPERATOR;
            return a;
        }
        l = l->suiv;
    }
}

Arbre analyse_syntaxique(ListeEntite liste) {
	Arbre a = NULL;

	if (liste != NULL) {
		ListeEntite e1 = priorite(liste, 1), e2 = priorite(liste, 2), e3 = priorite(liste, 3), e4 = priorite(liste, 4), e5 = priorite(liste, 5);
		if (e1 != NULL && e1->jeton.lexem != FIN) {
			typejeton mem = e1->jeton;
			e1->jeton.lexem = FIN;
			a = (Arbre)malloc(sizeof(struct Node));
			a->jeton.lexem = OPERATEUR;
			a->jeton.valeur.operateur = mem.valeur.operateur;
			a->fg = analyse_syntaxique(liste);
			a->fd = analyse_syntaxique(e1->suiv);
			e1->jeton.lexem = OPERATEUR;
			e1->jeton.valeur = mem.valeur;
		}
		else if (e2 != NULL && e2->jeton.lexem != FIN) {
			typejeton mem = e2->jeton;
			e2->jeton.lexem = FIN;
			a = (Arbre)malloc(sizeof(struct Node));
			a->jeton.lexem = OPERATEUR;
			a->jeton.valeur.operateur = mem.valeur.operateur;
			a->fg = analyse_syntaxique(liste);
			a->fd = analyse_syntaxique(e2->suiv);
			e2->jeton.lexem = OPERATEUR;
			e2->jeton.valeur = mem.valeur;
		}
		else if (e3 != NULL && e3->jeton.lexem != FIN) {
			ListeEntite par_ouv = e3->suiv, par_ferm = trouver_fermeture_parenthese(par_ouv);
			typejeton mem = par_ferm->jeton;
			par_ferm->jeton.lexem = FIN;

			a = (Arbre)malloc(sizeof(struct Node));
			a->jeton.lexem = FONCTION;
			a->jeton.valeur.fonction = e3->jeton.valeur.fonction;
			a->fg = analyse_syntaxique(par_ouv->suiv);
			a->fd = NULL;

			par_ferm->jeton = mem;
		}
		else if (e4 != NULL && e4->jeton.lexem != FIN) {
            if(e4->jeton.lexem == PAR_OUV) {
                ListeEntite par_ouv = e4, par_ferm = trouver_fermeture_parenthese(par_ouv);
                typejeton mem = par_ferm->jeton;
                par_ferm->jeton.lexem = FIN;

                a = analyse_syntaxique(par_ouv->suiv);

                par_ferm->jeton = mem;
            }
			else if (e4->jeton.lexem == BAR_OUV) {
                ListeEntite bar_ouv = e4, bar_ferm = trouver_fermeture_crochet(bar_ouv);
                typejeton mem = bar_ferm->jeton;
                bar_ferm->jeton.lexem = FIN;

                a = analyse_syntaxique(bar_ouv->suiv);

                bar_ferm->jeton = mem;
			}
		}
		else if (e5 != NULL && e5->jeton.lexem != FIN) {
			a = (Arbre)malloc(sizeof(struct Node));
			a->fg = NULL;
			a->fd = NULL;
			a->jeton.lexem = e5->jeton.lexem;
			a->jeton.valeur = e5->jeton.valeur;
		}

	}
	return a;
    
}


//Suppose que la chaine commence par l'ouverture de parenthèse;
ListeEntite trouver_fermeture_parenthese(ListeEntite e) {
	ListeEntite res = e->suiv;
	int i = 0;
	while (res != NULL && res->jeton.lexem != FIN) {
		if (res->jeton.lexem == PAR_OUV)
			i++;
		else if (res->jeton.lexem == PAR_FERM) {
			if (i == 0)
				return res;
			else
				i--;
		}
		res = res->suiv;
	}
	return NULL;
}

ListeEntite trouver_fermeture_crochet(ListeEntite e) {
    ListeEntite res = e->suiv;
	int i = 0;
	while (res != NULL && res->jeton.lexem != FIN) {
		if (res->jeton.lexem == BAR_OUV)
			i++;
		else if (res->jeton.lexem == BAR_FERM) {
			if (i == 0)
				return res;
			else
				i--;
		}
		res = res->suiv;
	}
	return NULL;
}

void afficher_arbre(Arbre a, int space) {

	if (a == NULL)
		return;

	space += 5;

	afficher_arbre(a->fd, space);

	printf("\n");

	int i;
	for (i = 5; i < space; i++)
		printf(" ");
	jeton_to_character(a->jeton);
	printf("\n");

	afficher_arbre(a->fg, space);
}

void afficher_liste(ListeEntite liste) {
	ListeEntite parcours = liste;

	while (parcours != NULL && parcours->jeton.lexem != FIN) {
		jeton_to_character(parcours->jeton);
		printf("\n");

		parcours = parcours->suiv;
	}
	printf("FIN\n");
}

void jeton_to_character(typejeton j) {
	switch (j.lexem) {
	case REEL:
		printf("%f", j.valeur.reel);
		break;
	case OPERATEUR:
		switch (j.valeur.operateur) {
		case PLUS:
			printf("+");
			break;
		case MOINS:
			printf("-");
			break;
		case FOIS:
			printf("*");
			break;
		case DIV:
			printf("/");
			break;
		case PUIS:
			printf("^");
			break;
		default:
			printf("?");
			break;
		}
		break;
	case FONCTION:
		switch (j.valeur.fonction) {
		case ABS:
			printf("Abs");
			break;
		case SIN:
			printf("sin");
			break;
		case COS:
			printf("cos");
			break;
		case SQRT:
			printf("rac");
			break;
		case LOG:
			printf("log");
			break;
		case TAN:
			printf("tan");
			break;
		case EXP:
			printf("exp");
			break;
		case ENTIER:
			printf("int");
			break;
		case VAL_NEG:
			printf("neg");
			break;
		case SINC:
			printf("sinc");
			break;
		}
		break;
	case ERREUR:
		printf("err");
		break;
	case FIN:
		printf("fin");
		break;
	case PAR_OUV:
		printf("(");
		break;
	case PAR_FERM:
		printf(")");
		break;
	case VARIABLE:
		printf("x");
		break;
	case BAR_OUV:
		printf("[");
		break;
	case BAR_FERM:
		printf("]");
		break;
	case ABSOLU:
		printf("|");
		break;
	}
}

ListeEntite insererEntite(ListeEntite e, typejeton j) {
	ListeEntite p = NULL, mem = e;
	if (e != NULL) {
		p = e->suiv;

		while (p != NULL && p->jeton.lexem != FIN) {
			e = p;
			p = p->suiv;
		}

		e->suiv = (ListeEntite)malloc(sizeof(Entite));
		e->suiv->jeton = j;
		e->suiv->suiv = p;
		p = mem;
	}
	else {
		p = (ListeEntite)malloc(sizeof(Entite));
		p->jeton = j;
		p->suiv = (ListeEntite)malloc(sizeof(Entite));
		p->suiv->jeton.lexem = FIN;
		p->suiv->suiv = NULL;
	}
	return p;
}
