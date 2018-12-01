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
	  NO_ERR, PRIORITY_MISMATCH, LEXICAL_ERR, UNPARSEABLE_SEQUENCE_REEL, UNPARSEABLE_SEQUENCE_OPERATEUR, UNPARSEABLE_SEQUENCE_FONCTION, UNPARSEABLE_SEQUENCE_OTHER
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
