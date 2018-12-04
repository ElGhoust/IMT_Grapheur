#include <GL/glut.h>

#include "func_graphique.h"
#include "graph.h"
#include "variables.h"

extern float borneMoins;
extern float bornePlus;
extern float pasAffichage;
extern float pas;
extern ptrMaillon valeurs;

/** Fonction principale de la partie graphique tournant en boucle.
 *  Elle regroupe la plupart des autres fonctions decrites dans ce fichier.
 */
void display()
{
    // clear window
    glClear(GL_COLOR_BUFFER_BIT);

    // Background en blanc et axes en noirs
    creationAxes();

    /// Creation de la scene ici
    for(float i = borneMoins; i < bornePlus; i=i+pasAffichage)
    {
        if (i != 0.0f)
        {
            setcolor(0.96F, 0.96F, 0.96F); // noir
            line(i/5.0F, -1.0F, i/5.0F, 1.0F);
            line(-1.0F, i/5.0F, 1.0F, i/5.0F);
        }
    }

    // Dessine une fonction
    setcolor(1.0F, 0.0F, 0.0F);
    drawFunc(valeurs);

    // flush drawing routines to the window
    glFlush();
}

/** Permet de créer les axes des abscisses et des ordonnées
 */
void creationAxes()
{
    setcolor(1.0F, 1.0F, 1.0F);
    bar(-1.0F, -1.0F, 1.0F, 1.0F);

    setcolor(0.0F, 0.0F, 0.0F); // noir
    line(-1.0F, 0.0F, 1.0F, 0.0F); // abscisse
    line(0.0F, -1.0F, 0.0F, 1.0F); // ordonnee
}

/** Dessine la fonction sur le graphique
 */
void drawFunc(ptrMaillon valeurs)
{
    beginlines(valeurs->x/5, valeurs->y/5);
    while (valeurs->suivant != NULL)
    {
        lineto(valeurs->x/5, valeurs->y/5);
        valeurs = valeurs->suivant;
    }
    finishlines();
}

void MouseButton(int button,int state,int x, int y)
{
    // TODO
}

