#include <stdio.h>
#include <stdlib.h>
#include "parseur.tab.h"

extern int yyparse();

int main(void) {
if (yyparse() == 0) { // call to the parsing (and lexing) function
printf("\nParsing:: syntax OK\n"); // reached if parsing follows the grammar
}
exit(EXIT_SUCCESS);
}
