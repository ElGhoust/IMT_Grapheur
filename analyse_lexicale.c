#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeton.h"
#include "analyse_lexicale.h"

void analyseLexicale(char * input){
    Arbre tab;
    if(input != NULL){
        int len = strlen(input);
        printf("longueur chaine : %d\n",len);

        tab = (Arbre)malloc(sizeof(Node));
        tab->pjeton_preced=NULL;
        tab->pjeton_suiv=NULL;

        for(int i = 0; i<len; i++){
            typejeton * temp;
            //printf("Valeur atoi: %d\n",atoi(input[i]));

            if (isdigit(input[i])){
                printf("CHIFFRE\n");

                temp = (typejeton*)malloc(sizeof(typejeton));

                temp->lexem='REEL';
                temp->valeur.reel=atof(&input[i]);

                printf("BIM %f\n",temp->valeur.reel);
            }
            else{
                switch(input[i]){
                    case '+':
                        printf("c'est un +\n");

                        break;
                    case '-':
                        printf("c'est un -\n");

                        break;
                    case '/':
                        printf("c'est un /\n");

                        break;
                    case '*':
                        printf("c'est un *\n");

                        break;
                    case '(':
                        printf("(\n");

                        break;
                    case ')':
                        printf(")\n");

                        break;
                    default:
                        printf("iiii\n");
                        break;
                }
            }
            printf("\n");
        }


    }
    else{
        printf("Chaine vide !");
    }
}


