#include <stdio.h>
#include <stdlib.h>
#include "parseur.tab.h"
#include "AST.h"

extern int yyparse();

int main(void) {
    //AST *pT = malloc(sizeof(struct _tree*)); 
    AST pT;

if (yyparse(&pT) == 0) { // call to the parsing (and lexing) function
    printf("\nParsing:: syntax OK\n"); // reached if parsing follows the grammar
}
    exit(EXIT_SUCCESS);
}
