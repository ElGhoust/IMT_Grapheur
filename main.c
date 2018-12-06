#include "func_graphique.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"
#include "evaluateur.h"
#include "graph.h"
#include "variables.h"

//|3x+|8-3x||+sin|7-3x|

/***************************************
*          VARIABLES GLOBALES          *
****************************************/

/* Borne - de l'axe des abscisses */
float borneMoins = -15.0F;

/* Borne + de l'axe des abscisses */
float bornePlus = 5.0F;

/* Affichage du quadrilage tous les pas d'affichage */
float scale = 1.0F;

/* TODO */
float pas = 0.1F;

/* Chaine de caracteres stockant la fonction mathématique */
char* fonction = NULL;

/* Liste chainee contenant les valeurs de la fonction */
ptrMaillon valeurs = NULL;

/****************************************
*          PROGRAMME PRINCIPAL          *
*****************************************/

int main ( int argc, char * argv[] )
{
    ListeEntite listeEntite;
    Arbre arbre;

    /// Récupération de la fonction mathématique
    fonction = malloc(1024 * sizeof(char));
    printf("Entrez votre fonction : \n");
    scanf("%s", fonction);

    listeEntite = analyseLexicale(fonction);

    arbre = getSyntaxeFromLexique(listeEntite);
    afficher_arbre(arbre, 0);

    valeurs = calculIntervalle(arbre, borneMoins, bornePlus);
    afficher(valeurs);

    InitGraph(argc, argv, "Grapheur", 980, 640, display, NULL, MouseButton);

    return 0;
}
