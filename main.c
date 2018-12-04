#include "func_graphique.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"
#include "evaluateur.h"
#include "graph.h"
#include "variables.h"

/***************************************
*          VARIABLES GLOBALES          *
****************************************/

/* Borne - de l'axe des abscisses */
float borneMoins = -10.0F;

/* Borne + de l'axe des abscisses */
float bornePlus = 10.0F;

/* Affichage du quadrillage tous les pas d'affichage */
float pasAffichage = 1.0F;

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
    afficherListe(listeEntite);

    arbre = getSyntaxeFromLexique(listeEntite);
    afficher_arbre(arbre, 0);

    valeurs = calculIntervalle(arbre, -10.0F, 10.0F);
    afficher(valeurs);

    InitGraph(argc, argv, "Grapheur", 980, 640, display, NULL, MouseButton);

    return 0;
}
