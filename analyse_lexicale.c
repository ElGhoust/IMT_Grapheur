#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "jeton.h"
#include "analyse_lexicale.h"

void analyseLexicale(char * input){
    //Test si input ok
    if(input != NULL){
        int len = strlen(input);
        printf("longueur chaine : %d\n",len);
        ListeEntite liste = initListe();


        for(int i = 0; i<len; i++){
            typejeton temp;
            //printf("Valeur atoi: %d\n",atoi(input[i]));

//            printf("%f", atof(&input[i]));
            if (isdigit(input[i])){
                printf("CHIFFRE\n");

//                temp = (typejeton*)malloc(sizeof(typejeton));
                /*if(input[i]>9){
                    i++;
                }*/
                temp.lexem=REEL;
                temp.valeur.reel=atof(&input[i]);

                liste = ajoutFin(liste, temp);

//                printf("BIM %f\n",liste->jeton.valeur.reel);
                if(atof(&input[i])>9){
                    i++;
                }


            }
            else{
                switch(input[i]){
                    case '+':
                        printf("c'est un +\n");
                        temp.lexem=OPERATEUR;
                        temp.valeur.operateur = PLUS;
                        liste = ajoutFin(liste, temp);
                        break;
                    case '-':
                        printf("c'est un -\n");
                        temp.lexem=OPERATEUR;
                        temp.valeur.operateur = MOINS;
                        liste = ajoutFin(liste, temp);
                        break;
                    case '/':
                        printf("c'est un /\n");
                        temp.lexem = OPERATEUR;
                        temp.valeur.operateur = DIV;
                        liste = ajoutFin(liste, temp);
                        break;
                    case '*':
                        printf("c'est un *\n");
                        temp.lexem = OPERATEUR;
                        temp.valeur.operateur = FOIS;
                        liste = ajoutFin(liste, temp);
                        break;
                    case '(':
                        printf("c'est un (\n");
                        temp.lexem = PAR_OUV;
                        liste = ajoutFin(liste, temp);
                        break;
                    case ')':
                        printf("c'est un )\n");
                        temp.lexem = PAR_FERM;
                        liste = ajoutFin(liste, temp);
                        break;
                    case '^':
                        printf("c'est un ^\n");
                        temp.lexem = PUIS;
                        liste = ajoutFin(liste, temp);
                        break;
                    case 'x':
                        case 'X':
                        printf("c'est une variable");
                        temp.lexem = VARIABLE;
                        liste = ajoutFin(liste, temp);
                        break;
                    default:
                        if(toupper(input[i])=='A'&&toupper(input[i+1])=='B'&&toupper(input[i+2])=='S'){
                            printf("c'est un ABS\n");
                            temp.lexem = FONCTION;
                            temp.valeur.fonction = ABS;
                            liste = ajoutFin(liste, temp);
                            i=i+2;
                        }
                        else if(toupper(input[i])=='C'&&toupper(input[i+1])=='O'&&toupper(input[i+2])=='S'){
                            printf("c'est un COS\n");
                            temp.lexem = FONCTION;
                            temp.valeur.fonction = COS;
                            liste = ajoutFin(liste, temp);
                            i=i+2;
                        }
                        else if(toupper(input[i])=='S'){
                            if(toupper(input[i+1])=='I'&&toupper(input[i+2])=='N'){
                                if(toupper(input[i+3])=='C'){
                                    printf("c'est un SINC\n");
                                    temp.lexem = FONCTION;
                                    temp.valeur.fonction = SINC;
                                    liste = ajoutFin(liste, temp);
                                    i=i+3;
                                }
                                else{
                                    printf("c'est un SIN\n");
                                    temp.lexem = FONCTION;
                                    temp.valeur.fonction = SIN;
                                    liste = ajoutFin(liste, temp);
                                    i=i+2;
                                }
                            }
                            else if(toupper(input[i+1])=='Q'&&toupper(input[i+2])=='R'&&toupper(input[i+3])=='T'){
                                printf("c'est un SQRT\n");
                                temp.lexem = FONCTION;
                                temp.valeur.fonction = SQRT;
                                liste = ajoutFin(liste, temp);
                                i=i+3;
                            }
                        }
                        else if (toupper(input[i])=='E'&&toupper(input[i+1])=='X'&&toupper(input[i+2])=='P'){
                            printf("c'est un EXP\n");
                            temp.lexem = FONCTION;
                            temp.valeur.fonction = EXP;
                            liste = ajoutFin(liste, temp);
                            i=i+2;
                        }
                        else if(toupper(input[i])=='T'&&toupper(input[i+1])=='A'&&toupper(input[i+2])=='N'){
                            printf("c'est un TAN\n");
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
        afficherListe(liste);
        printf("\n");

        }
    }
    else{
        printf("Chaine vide !");
    }

}

ListeEntite initListe(){
    ListeEntite liste = (ListeEntite)malloc(sizeof(Entite));

    liste->jeton.lexem = FIN;

    return liste;
}

ListeEntite ajoutFin(ListeEntite origine,typejeton jeton){
    printf("Je rentre dans la fonction.\n");
    ListeEntite temp = initListe();
    ListeEntite nouveau = initListe();
    printf("Je viens d'initialiser les listes.\n");


    nouveau->jeton.lexem = jeton.lexem;
    nouveau->jeton.valeur = jeton.valeur;

    printf("Je commence les test.\n");
    if(origine->jeton.lexem == FIN) {
        printf("La liste etait vide.\n");
        nouveau->suiv = origine;
        temp = nouveau;
        printf("Je viens de creer la liste.\n");
    } else {
        printf("La liste n'etait pas vide.\n");
        temp = origine;
        while(origine->suiv->jeton.lexem != FIN){
            origine=origine->suiv;
        }
        printf("Je viens de parcourir toute la liste.\n");
        nouveau->suiv = origine->suiv;
        origine->suiv=nouveau;
        printf("Je viens d'ajouter l'element a la liste.\n");
    }
    printf("\n");
    return temp;
}

void afficherListe(ListeEntite liste) {
    while(liste != NULL && liste->jeton.lexem != FIN) {
        if(liste->jeton.lexem == REEL) {
            printf(" %f /", liste->jeton.valeur.reel);
        } else if(liste->jeton.lexem == OPERATEUR) {
            printf(" OPERATEUR /");
        } else if(liste->jeton.lexem == PAR_OUV) {
            printf(" ( /");
        } else if(liste->jeton.lexem == PAR_FERM) {
            printf(" ) /");
        } else if(liste->jeton.lexem == PUIS) {
            printf(" ^ /");
        } else if(liste->jeton.lexem == FONCTION) {
            printf(" FONCTION /");
        } else if(liste->jeton.lexem == VARIABLE) {
            printf(" X /");
        }
        else {
            printf(" ALERTE /");
        }
        liste = liste->suiv;
    }
    printf(" FIN");
}


