#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"
#include "analyse_lexicale.h"

int main()
{
    char * entree = "(5+6-8)/2";
    analyseLexicale(entree);
    return 0;
}
