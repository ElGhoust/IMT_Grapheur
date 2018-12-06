#include <GL/glut.h>

#include "func_graphique.h"
#include "graph.h"
#include "variables.h"

extern float borneMoins;
extern float bornePlus;
extern float scale;
extern float pas;
extern ptrMaillon valeurs;

/*
float tmp;
tmp = ((-bornePlus)+(-borneMoins))/(abs(bornePlus)+abs(borneMoins));
*/

/** Fonction principale de la partie graphique tournant en boucle.
 *  Elle regroupe la plupart des autres fonctions decrites dans ce fichier.
 */
void display()
{
    // clear window
    glClear(GL_COLOR_BUFFER_BIT);

    /// Creation de la scene ici
    setcolor(0.85F, 0.85F, 0.85F); // noir
    creationCadrillage();

    // Background en blanc et axes en noirs
    creationAxes();

    // Dessine une fonction
    setcolor(1.0F, 0.0F, 0.0F);
    drawFunc(valeurs);

    // flush drawing routines to the window
    glFlush();
}

void creationCadrillage()
{
    float i;
    float nombreIntervalle = abs(borneMoins)+abs(bornePlus);
    for(i = borneMoins; i < bornePlus; i+=scale)
    {
        line(i, borneMoins, i, bornePlus); // abscisse
        line(borneMoins, i, bornePlus, i); // ordonnée
    }
}

/** Permet de créer les axes des abscisses et des ordonnées
 */
void creationAxes()
{
    setcolor(0.0F, 0.0F, 0.0F); // noir
    line(borneMoins, 0.0F, bornePlus, 0.0F); // abscisse
    line(0, borneMoins, 0, bornePlus); // ordonnee
}

/** Dessine la fonction sur le graphique
 */
void drawFunc(ptrMaillon valeurs)
{
    float emplacementAxeY = ((-bornePlus)+(-borneMoins))/(abs(bornePlus)+abs(borneMoins));

    beginlines(valeurs->x, valeurs->y);
    while (valeurs->suivant != NULL)
    {
        lineto(valeurs->x, valeurs->y);
        valeurs = valeurs->suivant;
    }
    finishlines();
}

void MouseButton(int button,int state,int x, int y)
{
    // TODO
}

