#ifndef JETON_H_INCLUDED
#define JETON_H_INCLUDED

typedef enum
{
    REEL,OPERATEUR,FONCTION,ERREUR,FIN,PAR_OUV,PAR_FERM,VARIABLE,BAR_OUV,BAR_FERM,ABSOLU
} typelexem;

typedef enum
{
    PLUS,MOINS,FOIS,DIV,PUIS
} typeoperateur;

typedef enum
{
    ABS,SIN,SQRT,LOG,COS,TAN,EXP,ENTIER,VAL_NEG,SINC
} typefonction;

typedef enum
{
    TOO_MANY_OPERATOR, ERR2, ERR3,etc // /!\ D�finir les diff�rents type d'erreurs
} typeerreur;

typedef union
{
    float reel;
    typefonction fonction;
    typeoperateur operateur;
    typeerreur erreur;
} typevaleur;

typedef struct
{
    typelexem lexem;
    typevaleur valeur;
} typejeton;

typedef struct Node
{
    typejeton jeton;
    struct Node *fg;
    struct Node *fd;
} Node;
typedef Node *Arbre;

#endif // JETON_H_INCLUDED
