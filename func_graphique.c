#include <GL/glut.h>

#include "func_graphique.h"
#include "graph.h"
#include "variables.h"

extern float borneMoins;
extern float bornePlus;
extern float pas;

/**
* Fonction custom pour redésinner la fenêtre
**/


void display()
{
    // clear window
    glClear(GL_COLOR_BUFFER_BIT);

    // Background en blanc et axes en noirs
    creationGraphique();

    /// Création de la scène ici
    for(float i = borneMoins; i < bornePlus; i=i+pas)
    {
        if (i != 0.0f)
        {
            setcolor(0.96F, 0.96F, 0.96F); // noir
            line(i/5.0F, -1.0F, i/5.0F, 1.0F);
            line(-1.0F, i/5.0F, 1.0F, i/5.0F);
        }
    }

    // flush drawing routines to the window
    glFlush();
}


void creationGraphique()
{
    setcolor(1.0F, 1.0F, 1.0F);
    bar(-1.0F, -1.0F, 1.0F, 1.0F);

    setcolor(0.0F, 0.0F, 0.0F); // noir
    line(-1.0F, 0.0F, 1.0F, 0.0F); // abscisse
    line(0.0F, -1.0F, 0.0F, 1.0F); // ordonnee
}

void MouseButton(int button,int state,int x, int y)
{

}

