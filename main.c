#include "func_graphique.h"
#include "analyse_lexicale.h"
#include "graph.h"
#include "variables.h"

/***************************************
*          VARIABLES GLOBALES          *
****************************************/

/* Borne - de l'axe des abscisses */
float borneMoins = -5.0F;

/* Borne + de l'axe des abscisses */
float bornePlus = 5.0F;

/* TODO */
float pas = 1.0F;

/* Variable stockant la fonction mathématique */
char* fonction = NULL;

/****************************************
*          PROGRAMME PRINCIPAL          *
*****************************************/

int main ( int argc, char * argv[] )
{
    ListeEntite listeEntite;

    /// Récupération de la fonction mathématique
    fonction = malloc(1024 * sizeof(char));
    printf("Entrez votre fonction : \n");
    scanf("%s", fonction);

    listeEntite = analyseLexicale(fonction);
    afficherListe(listeEntite);
    //InitGraph(argc, argv, "Grapheur", 980, 640, display, NULL, MouseButton);

    return 0;
}
