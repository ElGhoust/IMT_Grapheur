#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "jeton.h"
#include "analyse_lexicale.h"

ListeEntite analyseLexicale(char *input)
{
    ListeEntite liste = NULL;

    if(input != NULL)
    {
        int len = strlen(input);
        liste = initListe();
        for(int i = 0; i<len; i++)
        {
            typejeton temp;
            if (isdigit(input[i]))
            {
                temp.lexem=REEL;
                temp.valeur.reel=atof(&input[i]);
                liste = ajoutFin(liste, temp);
                if(atof(&input[i]) > 9)
                {
                    i++;
                }
            }
            else
            {
                switch(input[i])
                {
                    case '+':
                        temp.lexem=OPERATEUR;
                        temp.valeur.operateur = PLUS;
                        liste = ajoutFin(liste, temp);
                        break;
                    case '-':
                        temp.lexem=OPERATEUR;
                        temp.valeur.operateur = MOINS;
                        liste = ajoutFin(liste, temp);
                        break;
                    case '/':
                        temp.lexem = OPERATEUR;
                        temp.valeur.operateur = DIV;
                        liste = ajoutFin(liste, temp);
                        break;
                    case '*':
                        temp.lexem = OPERATEUR;
                        temp.valeur.operateur = FOIS;
                        liste = ajoutFin(liste, temp);
                        break;
                    case '(':
                        temp.lexem = PAR_OUV;
                        liste = ajoutFin(liste, temp);
                        break;
                    case ')':
                        temp.lexem = PAR_FERM;
                        liste = ajoutFin(liste, temp);
                        break;
                    case '^':
                        temp.lexem = PUIS;
                        liste = ajoutFin(liste, temp);
                        break;
                    case 'x':
                        case 'X':
                        temp.lexem = VARIABLE;
                        liste = ajoutFin(liste, temp);
                        break;
                    default:
                        if(toupper(input[i])=='A'&&toupper(input[i+1])=='B'&&toupper(input[i+2])=='S')
                        {
                            temp.lexem = FONCTION;
                            temp.valeur.fonction = ABS;
                            liste = ajoutFin(liste, temp);
                            i=i+2;
                        }
                        else if(toupper(input[i])=='C'&&toupper(input[i+1])=='O'&&toupper(input[i+2])=='S')
                        {
                            temp.lexem = FONCTION;
                            temp.valeur.fonction = COS;
                            liste = ajoutFin(liste, temp);
                            i=i+2;
                        }
                        else if(toupper(input[i])=='S')
                        {
                            if(toupper(input[i+1])=='I'&&toupper(input[i+2])=='N')
                            {
                                if(toupper(input[i+3])=='C')
                                {
                                    temp.lexem = FONCTION;
                                    temp.valeur.fonction = SINC;
                                    liste = ajoutFin(liste, temp);
                                    i=i+3;
                                }
                                else
                                {
                                    temp.lexem = FONCTION;
                                    temp.valeur.fonction = SIN;
                                    liste = ajoutFin(liste, temp);
                                    i=i+2;
                                }
                            }
                            else if(toupper(input[i+1])=='Q'&&toupper(input[i+2])=='R'&&toupper(input[i+3])=='T')
                            {
                                temp.lexem = FONCTION;
                                temp.valeur.fonction = SQRT;
                                liste = ajoutFin(liste, temp);
                                i=i+3;
                            }
                        }
                        else if (toupper(input[i])=='E'&&toupper(input[i+1])=='X'&&toupper(input[i+2])=='P')
                        {
                            temp.lexem = FONCTION;
                            temp.valeur.fonction = EXP;
                            liste = ajoutFin(liste, temp);
                            i=i+2;
                        }
                        else if(toupper(input[i])=='T'&&toupper(input[i+1])=='A'&&toupper(input[i+2])=='N')
                        {
                            temp.lexem = FONCTION;
                            temp.valeur.fonction = TAN;
                            liste = ajoutFin(liste, temp);
                            i=i+2;
                        }
                        else{
                        printf("iiii\n");
                        }
                        break;
                }
            }
        }
    }
    else{
        printf("Chaine vide !");
    }
    return liste;
}

ListeEntite initListe()
{
    ListeEntite liste = (ListeEntite)malloc(sizeof(Entite));

    liste->jeton.lexem = FIN;

    return liste;
}

ListeEntite ajoutFin(ListeEntite origine, typejeton jeton)
{
    ListeEntite temp = initListe();
    ListeEntite nouveau = initListe();


    nouveau->jeton.lexem = jeton.lexem;
    nouveau->jeton.valeur = jeton.valeur;

    if(origine->jeton.lexem == FIN)
    {
        nouveau->suiv = origine;
        temp = nouveau;
    }
    else
    {
        temp = origine;
        while(origine->suiv->jeton.lexem != FIN)
        {
            origine=origine->suiv;
        }
        nouveau->suiv = origine->suiv;
        origine->suiv=nouveau;
    }
    return temp;
}

void afficherListe(ListeEntite liste)
{
    while(liste != NULL && liste->jeton.lexem != FIN)
    {
        if(liste->jeton.lexem == REEL)
        {
            printf(" %f /", liste->jeton.valeur.reel);
        }
        else if(liste->jeton.lexem == OPERATEUR)
        {
            printf(" OPERATEUR /");
        }
        else if(liste->jeton.lexem == PAR_OUV)
        {
            printf(" ( /");
        }
        else if(liste->jeton.lexem == PAR_FERM)
        {
            printf(" ) /");
        }
        else if(liste->jeton.lexem == PUIS)
        {
            printf(" ^ /");
        }
        else if(liste->jeton.lexem == FONCTION)
        {
            printf(" FONCTION /");
        }
        else if(liste->jeton.lexem == VARIABLE)
        {
            printf(" X /");
        }
        else
        {
            printf(" ALERTE /");
        }
        liste = liste->suiv;
    }
    printf(" FIN");
}

