#include <stdio.h>
#include <stdlib.h>
#include "parseur.tab.h"
#include "AST.h"

extern int yyparse();
extern FILE* yyin;

int main(int argc, char *args[]) {

    yyin = fopen(args[1],"r");
    // AST *pT = malloc(sizeof(struct _tree*)); 
    AST pT;

if (yyparse(&pT) == 0) { // call to the parsing (and lexing) function
    printf("\nParsing:: syntax OK\n"); // reached if parsing follows the grammar
    
    // printAST(pT);
    printf("l evaulation de l expression est de: %d", displayValueAst(pT));    
 
}
    exit(EXIT_SUCCESS);
}
