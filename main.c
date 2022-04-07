#include <stdio.h>
#include <stdlib.h>
#include "parseur.tab.h"

extern int yyparse();
extern FILE* yyin;

int main(int argc, char *args[]) {

    yyin = fopen(args[1],"r");

    if (yyparse() == 0) { // call to the parsing (and lexing) function
        printf("\nParsing:: syntax OK\n"); // reached if parsing follows the grammar
    }
    exit(EXIT_SUCCESS);
}
