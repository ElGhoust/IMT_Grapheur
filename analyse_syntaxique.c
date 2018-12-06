#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
#include "jeton.h"

/*
 * Retourne le première occurence dans la liste chainée de la priorité choisie
 * 1: moins / plus
 * 2: fois / div
 * 3: fonction
 * 4: parenthèses, crochets, absolu
 * 5: Reel / Variable
 *
 * @params ListeEntite liste
 * @params int priorite
 *
 * @return ListeEntite
 */
ListeEntite priorite(ListeEntite liste, int priorite) {
	// TODO: Changer toute la logique pour inclure les barres et les absolus
	int i = 0;
	int found = 0;
	ListeEntite res = liste;

	while (res != NULL && res->jeton.lexem != FIN && !found) {
		if (priorite != 4 && (res->jeton.lexem == PAR_OUV || res->jeton.lexem == BAR_OUV || res->jeton.lexem == ABSOLU))
			res = getClosingTagListe(res);

		switch (priorite) {
		case 0:
			if (res->jeton.lexem == OPERATEUR && (res->jeton.valeur.operateur == MOINS || res->jeton.valeur.operateur == PLUS))
				found = 1;
			break;
			break;
		case 1:
			if (res->jeton.lexem == OPERATEUR && (res->jeton.valeur.operateur == FOIS || res->jeton.valeur.operateur == DIV))
				found = 1;
		case 2:
			if (res->jeton.lexem == OPERATEUR && res->jeton.valeur.operateur == PUIS)
				found = 1;
			break;
		case 3:
			if (res->jeton.lexem == FONCTION)
				found = 1;
			break;
		case 4:
			if (res->jeton.lexem == PAR_OUV || res->jeton.lexem == BAR_OUV || res->jeton.lexem == ABSOLU)
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
		if (!found)
			res = res->suiv;
	}

	return res;
}

/*
 * Point d'entrée de la partie analyse syntaxique
 * Retourne un Arbre à partir d'une liste chainée
 *
 * @params ListeEntite liste
 *
 * @return Arbre
 */
Arbre getSyntaxeFromLexique(ListeEntite liste) {
	Arbre a = NULL;
	liste = clean(liste);
	typeerreur e = findErrorListe(liste);
	if (e != NO_ERR) {
		a = (Arbre)malloc(sizeof(struct Node));
		a->jeton.lexem = ERREUR;
		a->jeton.valeur.erreur = e;
		a->fd = NULL, a->fg = NULL;
		return a;
	}
	return analyse_syntaxique(liste);
}

/*
 * Fonction d'analyse synntaxique de la liste chainée
 * Cette fonction est appelée dans getSyntaxeFromLexique après avoir nettoyé et controlé la liste
 *
 * @params ListeEntite liste
 *
 * @return Arbre
 */
Arbre analyse_syntaxique(ListeEntite liste) {
	Arbre a = NULL;

	if (liste != NULL) {
		ListeEntite e0 = priorite(liste, 0);
		// Plus et moins
		if (e0 != NULL && e0->jeton.lexem != FIN) {
			typejeton mem = e0->jeton;
			e0->jeton.lexem = FIN;
			a = (Arbre)malloc(sizeof(struct Node));
			a->jeton.lexem = OPERATEUR;
			a->jeton.valeur.operateur = mem.valeur.operateur;
			a->fg = analyse_syntaxique(liste);
			a->fd = analyse_syntaxique(e0->suiv);
			e0->jeton.lexem = OPERATEUR;
			e0->jeton.valeur = mem.valeur;
		}
		else {
			// Fois et div
			ListeEntite e1 = priorite(liste, 1);
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
			else {
				// Puissance
				ListeEntite e2 = priorite(liste, 2);
				if (e2 != NULL && e2->jeton.lexem != FIN) {
					typejeton mem = e2->jeton;
					e2->jeton.lexem = FIN;
					a = (Arbre)malloc(sizeof(struct Node));
					a->jeton.lexem = OPERATEUR;
					a->jeton.valeur.operateur = mem.valeur.operateur;
					a->fg = analyse_syntaxique(liste);
					a->fd = analyse_syntaxique(e2->suiv);
					e2->jeton.lexem = OPERATEUR;
					e2->jeton.valeur.operateur = PUIS;
				}
				else {
					// Fonction
					ListeEntite e3 = priorite(liste, 3);
					if (e3 != NULL && e3->jeton.lexem != FIN) {
						ListeEntite start = e3->suiv, end = NULL;
						typejeton j;
						j.lexem = getClosingTag(start->jeton.lexem);
						end = getClosingTagListe(start);

						end->jeton.lexem = FIN;

						if (j.lexem == ABSOLU) {
							a = (Arbre)malloc(sizeof(struct Node));
							a->jeton.lexem = FONCTION;
							a->jeton.valeur.fonction = e3->jeton.valeur.fonction;
							a->fg = (Arbre)malloc(sizeof(struct Node));
							a->fg->jeton.lexem = FONCTION;
							a->fg->jeton.valeur.fonction = ABS;
							a->fd = NULL;
							a->fg->fg = analyse_syntaxique(start->suiv);
							a->fg->fd = NULL;
						}
						else {
							a = (Arbre)malloc(sizeof(struct Node));
							a->jeton.lexem = FONCTION;
							a->jeton.valeur.fonction = e3->jeton.valeur.fonction;
							a->fg = analyse_syntaxique(start->suiv);
							a->fd = NULL;
						}

						end->jeton.lexem = j.lexem;
					}
					else {
						// PAR, BAR et ABSOLUE
						ListeEntite e4 = priorite(liste, 4);
						if (e4 != NULL && e4->jeton.lexem != FIN) {
							ListeEntite start = e4, end = NULL;
							typejeton j;
							j.lexem = getClosingTag(start->jeton.lexem);
							end = getClosingTagListe(start);

							end->jeton.lexem = FIN;

							if (j.lexem == ABSOLU) {
								a = (Arbre)malloc(sizeof(struct Node));
								a->jeton.lexem = FONCTION;
								a->jeton.valeur.fonction = ABS;
								a->fg = analyse_syntaxique(start->suiv);
								a->fd = NULL;
							}
							else {
								a = analyse_syntaxique(start->suiv);
							}

							end->jeton.lexem = j.lexem;
						}
						else {
							// REEL et Variable
							ListeEntite e5 = priorite(liste, 5);
							if (e5 != NULL && e5->jeton.lexem != FIN) {
								a = (Arbre)malloc(sizeof(struct Node));
								a->fg = NULL;
								a->fd = NULL;
								a->jeton.lexem = e5->jeton.lexem;
								a->jeton.valeur = e5->jeton.valeur;
							}
						}
					}
				}
			}
		}
	}
	return a;
}

/*
 * Affiche un arbre de manière lisible dans la console
 * Cette fonctions doit être appelée avec space = 0 (sinon décale l'arbre dans la console)
 *
 * @params Arbre a
 * @params int space
 *
 * @return void
 */
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

/*
 * Cette fonction affiche une liste chainée dans la console
 *
 * @params ListeEntite liste
 *
 * @return void
 */
void afficher_liste(ListeEntite liste) {
	ListeEntite parcours = liste;

	while (parcours != NULL && parcours->jeton.lexem != FIN) {
		jeton_to_character(parcours->jeton);
		printf("\n");

		parcours = parcours->suiv;
	}
	printf("FIN\n");
}

/*
 * Affiche un jeton dans la console
 *
 * @params typejeton j
 *
 * @return void
 */
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
		default:
			printf("?");
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
	default:
		printf("?");
		break;
	}
}

/*
 * Insere un jeton dans la liste
 * Utilisé pour le débugage
 *
 * @params ListeEntite e
 * @params typejeton j
 *
 * @return ListeEntite
 */
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

/*
 * Trouve la première dans liste s'il y en a
 * Si il n'y en a pas retourne NO_ERR
 *
 * @params ListeEntite l
 *
 * @return typeerreur
 */
typeerreur findErrorListe(ListeEntite l) {
	typeerreur result;
	if (hasError(l))
		return LEXICAL_ERR;
	else if (hasPriorityMismatch(l))
		return PRIORITY_MISMATCH;
	else if ((result = hasBadLexemSequence(l)) != NO_ERR)
		return result;
	else {
		// TODO: Clear successive + and -
		return NO_ERR;
	}
}

/*
 * Compte le nombre de jetons (jeton spécifique) dans la liste chainée
 *
 * @params ListeEntite l
 * @params typejeton j
 *
 * @return int
 */
int countJeton(ListeEntite l, typejeton j) {
	int i = 0;

	while (l != NULL && l->jeton.lexem != FIN) {
		if (jetonCompare(l->jeton, j))
			i++;
		l = l->suiv;
	}

	return i;
}

/*
 * Compare deux jetons pour savoir s'il sont égaux
 *
 * @params typejeton j1
 * @params typejeton j2
 *
 * @return int (0 ou 1)
 */
int jetonCompare(typejeton j1, typejeton j2) {
	if (j1.lexem == j2.lexem) {
		switch (j1.lexem) {
		case REEL:
			return j1.valeur.reel == j2.valeur.reel;
			break;
		case OPERATEUR:
			return j1.valeur.operateur == j2.valeur.operateur;
			break;
		case FONCTION:
			return j1.valeur.fonction == j2.valeur.fonction;
			break;
		case ERREUR:
			return j1.valeur.erreur == j2.valeur.erreur;
			break;
		default:
			return 1;
		}
	}
	return 0;
}

/*
 * Renvoie une erreur commencant par UNPARSEABLE_SEQUENCE si la liste à une mauvaise sequence de character
 * Ex : sin4+5 pas bon
 *
 * @params ListeEntite l
 *
 * @return typeerreur
 */
typeerreur hasBadLexemSequence(ListeEntite l) {
	while (l != NULL && l->jeton.lexem != FIN) {
		ListeEntite suiv = l->suiv;
		switch (l->jeton.lexem) {
		case REEL:
			if (suiv->jeton.lexem == REEL || suiv->jeton.lexem == FONCTION || suiv->jeton.lexem == PAR_OUV || suiv->jeton.lexem == BAR_OUV || suiv->jeton.lexem == VARIABLE)
				return UNPARSEABLE_SEQUENCE_REEL;
			break;
		case OPERATEUR:
			if (suiv->jeton.lexem == OPERATEUR || suiv->jeton.lexem == FIN || suiv->jeton.lexem == PAR_FERM || suiv->jeton.lexem == BAR_FERM)
				return UNPARSEABLE_SEQUENCE_OPERATEUR;
			else if ((l->jeton.valeur.operateur == PLUS || l->jeton.valeur.operateur == MOINS) && suiv->jeton.lexem == OPERATEUR && (l->jeton.valeur.operateur == FOIS || l->jeton.valeur.operateur == DIV))
				return UNPARSEABLE_SEQUENCE_OPERATEUR;
			else if ((l->jeton.valeur.operateur == FOIS || l->jeton.valeur.operateur == DIV) && suiv->jeton.lexem == OPERATEUR && (l->jeton.valeur.operateur == PLUS || l->jeton.valeur.operateur == MOINS))
				return UNPARSEABLE_SEQUENCE_OPERATEUR;
			break;
		case FONCTION:
			if (suiv->jeton.lexem != BAR_OUV && suiv->jeton.lexem != PAR_OUV && suiv->jeton.lexem != ABSOLU)
				return UNPARSEABLE_SEQUENCE_FONCTION;
			break;
		case VARIABLE:
			if (suiv->jeton.lexem == REEL || suiv->jeton.lexem == FONCTION || suiv->jeton.lexem == PAR_OUV || suiv->jeton.lexem == BAR_OUV || suiv->jeton.lexem == VARIABLE)
				return UNPARSEABLE_SEQUENCE_OTHER;
			break;
		default:
			break;
		}

		l = l->suiv;
	}
	return NO_ERR;
}

/*
 * Trouve si la liste comporte une erreur de parenthèses \ crochets \ absolues
 *
 * Ex : 3*(4/[3+5)] Pas bon
 *
 * @params ListeEntite l
 *
 * @return int (0 ou 1)
 */
int hasPriorityMismatch(ListeEntite l) {
	ListeEntite start = l;
	while (l != NULL && l->jeton.lexem != FIN) {
		typejeton j1, j2;

		j1.lexem = PAR_OUV;
		j2.lexem = PAR_FERM;
		if (countJeton(l, j1) != countJeton(l, j2)) {
			return 1;
		}

		j1.lexem = BAR_OUV;
		j2.lexem = BAR_FERM;
		if (countJeton(l, j1) != countJeton(l, j2)) {
			return 1;
		}

		j1.lexem = ABSOLU;
		if (countJeton(l, j1) % 2 != 0) {
			return 1;
		}

		typelexem lexem = l->jeton.lexem;
		if (lexem == BAR_FERM || lexem == PAR_FERM) {
			return 1;
		}
		else if (lexem == ABSOLU || lexem == BAR_OUV || lexem == PAR_OUV) {
			ListeEntite begin = NULL, end = NULL;

			end = getClosingTagListe(l);
			begin = l->suiv;

			if (end == NULL)
				return 1;

			typejeton temp;
			temp.lexem = end->jeton.lexem;
			end->jeton.lexem = FIN;

			if (hasPriorityMismatch(begin))
				return 1;
			else
				end->jeton.lexem = temp.lexem, l = end;
		}
		l = l->suiv;
	}
	return 0;
}

/*
 * Retourne vrai si la liste comporte une erreur à l'intérieur
 *
 * @params ListeEntite l
 *
 * @return int (0 ou 1)
 */
int hasError(ListeEntite l) {
	while (l != NULL && l->jeton.lexem != FIN) {
		if (l->jeton.lexem == ERREUR)
			return 1;
		l = l->suiv;
	}
	return 0;
}

/*
 * Retourne la première occurence d'un jeton dans la liste
 *
 * @params ListeEntite l
 * @params typejeton j
 *
 * @return ListeEntite (pointeur sur le jeton)
 */
ListeEntite getFirstJeton(ListeEntite l, typejeton j) {
	while (l != NULL && l->jeton.lexem != FIN) {
		if (jetonCompare(l->jeton, j))
			return l;
		l = l->suiv;
	}
	return NULL;
}

/*
 * Retourne la dernière occurence d'un jeton dans la liste
 *
 * @params ListeEntite l
 * @params typejeton j
 *
 * @return ListeEntite (pointeur sur le jeton)
 */
ListeEntite getLastJeton(ListeEntite l, typejeton j) {
	ListeEntite last = NULL;
	while (l != NULL && l->jeton.lexem != FIN) {
		if (jetonCompare(l->jeton, j))
			last = l;
		l = l->suiv;
	}
	return last;
}

/*
 * Copy un jeton
 *
 * @params typejeton in
 * @params typejeton * out
 *
 * @return void
 */
void copyJeton(typejeton in, typejeton * out) {
	out->lexem = in.lexem;
	switch (in.lexem) {
	case REEL:
		out->valeur.reel = in.valeur.reel;
		break;
	case OPERATEUR:
		out->valeur.operateur = in.valeur.operateur;
		break;
	case FONCTION:
		out->valeur.fonction = in.valeur.fonction;
		break;
	case ERREUR:
		out->valeur.erreur = in.valeur.erreur;
		break;
	default:
		break;
	}
}

/*
 * Nettoie la liste chainée pour la formaté et qu'elle soit compatible avec analyse_syntaxique
 * (Certaines suite de charactères peuvent être compris par la machine mais ne soit pas gérés dans analyse_syntaxique)
 *
 * @params ListeEntite l
 *
 * @return ListeEntite
 */
ListeEntite clean(ListeEntite l) {
	l = cleanSequencePlusMoins(l);
	l = cleanStartPlusMoins(l);
	l = cleanSequenceReelVariable(l);

	return l;
}

/*
 * Compile les séquences de plus et de moins en une seule séquence
 * Ex : ++-3 => -3
 *
 * @params ListeEntite l
 *
 * @return ListeEntite l
 */
ListeEntite cleanSequencePlusMoins(ListeEntite l) {
	ListeEntite start = l;
	while (l != NULL && l->jeton.lexem != FIN) {
		ListeEntite temp = l->suiv;
		int taille = 1;
		switch (l->jeton.lexem) {
		case OPERATEUR:
			// Fusion des suites de + et de -
			while (temp->jeton.lexem == OPERATEUR) {
				taille++;
				temp = temp->suiv;
			}
			if (taille != 1) {
				typejeton copy;
				copyJeton(temp->jeton, &copy);
				temp->jeton.lexem = FIN;
				typeoperateur merge = mergePlusMoins(l);

				ListeEntite suiv = l->suiv, tmp = NULL;
				while (suiv->jeton.lexem != FIN) {
					tmp = suiv;
					suiv = suiv->suiv;
					free(tmp);
				}

				copyJeton(copy, &(temp->jeton));
				l->jeton.valeur.operateur = merge;
				l->suiv = temp;
			}
			break;
		default:
			break;
		}
		l = l->suiv;
	}
	return start;
}

/*
 * Remplace les - en début de chaines (y compris en début de parenthèse) par des substitus compréhensibles par analyse_syntaxique
 * Ex : 3*(-sin(3)+4) => 3 * (val_neg(sin(3))+4)
 *
 * @params ListeEntite l
 *
 * @return ListeEntite l
 */
ListeEntite cleanStartPlusMoins(ListeEntite l) {
	if ((l->jeton.lexem == OPERATEUR && (l->jeton.valeur.operateur == PLUS || l->jeton.valeur.operateur == MOINS))) {
		ListeEntite suiv = l->suiv;
		typeoperateur curOp = l->jeton.valeur.operateur;
		typelexem suivLex = suiv->jeton.lexem;


		if (curOp == PLUS && (suivLex == REEL || suivLex == FONCTION || suivLex == PAR_OUV || suivLex == BAR_OUV || suivLex == ABS)) {
			free(l);
			l = suiv;
		}
		else {
			if (suiv->jeton.lexem == REEL) {
				free(l);
				l = suiv;
				l->jeton.valeur.reel *= -1;
			}
			else if (suiv->jeton.lexem == FONCTION || suiv->jeton.lexem == BAR_OUV || suiv->jeton.lexem == PAR_OUV || suiv->jeton.lexem == ABSOLU) {
				ListeEntite end = NULL;
				typejeton j;
				if (suiv->jeton.lexem == FONCTION) {
					j.lexem = getClosingTag(suiv->suiv->jeton.lexem);
					end = getClosingTagListe(suiv->suiv);
				}
				else {
					j.lexem = getClosingTag(suiv->jeton.lexem);
					end = getClosingTagListe(suiv);
				}

				if (end != NULL) {
					l->jeton.lexem = FONCTION;
					l->jeton.valeur.fonction = VAL_NEG;
					l->suiv = (ListeEntite)malloc(sizeof(struct Entite));
					l->suiv->jeton.lexem = PAR_OUV;
					l->suiv->suiv = suiv;
					ListeEntite closing = (ListeEntite)malloc(sizeof(struct Entite));
					closing->jeton.lexem = j.lexem;
					closing->suiv = end->suiv;
					end->suiv = closing;
				}

			}
		}
	}
	else {
		ListeEntite l2 = l;
		while (l2 != NULL && l2->jeton.lexem != FIN) {
			if (l2->jeton.lexem == BAR_OUV || l2->jeton.lexem == PAR_OUV || l2->jeton.lexem == ABSOLU) {
				ListeEntite last = NULL;
				typejeton j;
				j.lexem = getClosingTag(l2->jeton.lexem);
				last = getClosingTagListe(l2);

				if (last != NULL) {
					last->jeton.lexem = FIN;
					l2->suiv = cleanStartPlusMoins(l2->suiv);
					last->jeton.lexem = j.lexem;
				}
			}
			l2 = l2->suiv;
		}
	}
	return l;
}

/*
 * Transforme les séquences de reels/variables en mulitplication
 * Ex: 3xsin(x) => 3*x*sin(x)
 *
 * @params ListeEntite l
 *
 * @return ListeEntite
 */
ListeEntite cleanSequenceReelVariable(ListeEntite l) {
	ListeEntite start = l;
	while (l != NULL && l->jeton.lexem != FIN) {
		ListeEntite s = l->suiv;
		if (l->jeton.lexem == REEL) {
			if (s->jeton.lexem == VARIABLE || s->jeton.lexem == FONCTION || s->jeton.lexem == PAR_OUV || s->jeton.lexem == BAR_OUV) {
				ListeEntite n = (ListeEntite)malloc(sizeof(Entite));
				n->jeton.lexem = OPERATEUR;
				n->jeton.valeur.operateur = FOIS;
				n->suiv = s;
				l->suiv = n;
			}
		}
		else if (l->jeton.lexem == VARIABLE) {
			if (s->jeton.lexem == REEL || s->jeton.lexem == FONCTION || s->jeton.lexem == PAR_OUV || s->jeton.lexem == BAR_OUV) {
				ListeEntite n = (ListeEntite)malloc(sizeof(Entite));
				n->jeton.lexem = OPERATEUR;
				n->jeton.valeur.operateur = FOIS;
				n->suiv = s;
				l->suiv = n;
			}
		}
		else if (l->jeton.lexem == BAR_FERM || l->jeton.lexem == PAR_FERM) {
			if (s->jeton.lexem == VARIABLE || s->jeton.lexem == REEL || s->jeton.lexem == FONCTION || s->jeton.lexem == PAR_OUV || s->jeton.lexem == BAR_OUV || s->jeton.lexem == ABSOLU) {
				ListeEntite n = (ListeEntite)malloc(sizeof(Entite));
				n->jeton.lexem = OPERATEUR;
				n->jeton.valeur.operateur = FOIS;
				n->suiv = s;
				l->suiv = n;
			}
		}

		l = l->suiv;
	}
	return start;
}

/*
 * Compile une liste entite de plus et de moins en une seule
 *
 * @params ListeEntite l
 *
 * @return typeoperateur
 */
typeoperateur mergePlusMoins(ListeEntite l) {
	typeoperateur output = PLUS;
	while (l != NULL && l->jeton.lexem != FIN) {
		if (l->jeton.valeur.operateur == MOINS && output != MOINS)
			output = MOINS;
		else if (l->jeton.valeur.operateur == MOINS && output == MOINS)
			output = PLUS;
		l = l->suiv;
	}
	return output;
}

/*
 * Retourne le lexem équivalent pour les fermetures
 * Ex : ( => )
 * Retourne ERREUR si le lexem n'est pas ( [ ou |
 *
 * @params typelexem l
 *
 * @return typelexem
 */
typelexem getClosingTag(typelexem l) {
	switch (l)
	{
	case PAR_OUV:
		return PAR_FERM;
	case BAR_OUV:
		return BAR_FERM;
	case ABSOLU:
		return ABSOLU;
	default:
		return ERREUR;
	}
}

/*
 * Retourne un pointeur vers le jeton fermant
 * Ex : (x+3)*x => )*x
 *
 * @pre Suppose que le premier jeton de la liste donnée est l'ouverture ( [ |
 *
 * @params ListeEntite l
 *
 * @return ListeEntite
 */
ListeEntite getClosingTagListe(ListeEntite l) {
	typejeton opening, closing;
	opening.lexem = l->jeton.lexem;
	closing.lexem = getClosingTag(opening.lexem);
	int count = 0;

	if (opening.lexem != ABSOLU) {
		while (l != NULL && l->jeton.lexem != FIN) {
			if (jetonCompare(l->jeton, opening))
				count++;
			else if (jetonCompare(l->jeton, closing))
				count--;

			if (count == 0)
				return l;

			l = l->suiv;
		}
	}
	else {
		count = 1;
		l = l->suiv;
		if (l->jeton.lexem == ABSOLU)
			return l;

		while (l != NULL && l->jeton.lexem != FIN) {
			ListeEntite suiv = l->suiv;
			if (suiv != NULL && suiv->jeton.lexem == ABSOLU) {
				typelexem lex = l->jeton.lexem;
				if (lex == OPERATEUR || lex == FONCTION || lex == PAR_OUV || lex == BAR_OUV)
					count++;
				else
					count--;

				if (count == 0)
					return suiv;
			}

			l = l->suiv;
		}
	}

	return NULL;
}

/*
 * Détruit l'arbre et retourne NULL
 *
 * @params Arbre a
 * @return Arbre NULL
 */
Arbre detruireArbre(Arbre a) {
	if (a != NULL) {
		detruireArbre(a->fg);
		detruireArbre(a->fd);
		free(a);
	}
	return NULL;
}
