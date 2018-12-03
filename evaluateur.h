#ifndef EVALUATEUR_H_INCLUDED
#define EVALUATEUR_H_INCLUDED


typedef struct Node
{
    typejeton jeton;
    struct Node *pjeton_preced;
    struct Node *pjeton_suiv;
} Node;
typedef Node *Arbre;

#endif // EVALUATEUR_H_INCLUDED
