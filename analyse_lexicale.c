#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeton.h"
#include "analyse_lexicale.h"

void analyseLexicale(char * input){
    //Test si input ok
    if(input != NULL){
        int len = strlen(input);
        printf("longueur chaine : %d\n",len);
        typejeton tab[len+1];


        for(int i = 0; i<len; i++){
            typejeton * temp;
            //printf("Valeur atoi: %d\n",atoi(input[i]));

            if (isdigit(input[i])){
                printf("CHIFFRE\n");

                temp = (typejeton*)malloc(sizeof(typejeton));

                temp->lexem='REEL';
                temp->valeur.reel=atof(&input[i]);

                printf("BIM %f\n",temp->valeur.reel);

                tab[i]=*temp;
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
        printf("\n----AFFICHAGE TABLEAU----\n");
        for(int i=0; i< sizeof(tab)/sizeof(typejeton); i++){
            printf("%d\n",i);
            if(tab[i].valeur.reel!=0){
                printf("%f\n",tab[i].valeur.reel);
            }
        }
    }
    else{
        printf("Chaine vide !");
    }


}



