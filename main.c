#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseur.tab.h"
#include "AST.h"

extern int yyparse();
extern FILE* yyin;

int main(int argc, char *args[]) {
 
    yyin = fopen(args[1],"r"); 
    AST pT;

    if( argc == 2){
	   
	  if ((yyparse(&pT)==0)) { 		/* yyparse calls yylex */
	    printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
	    
	  
	     
	    char* newFullFileName = strcat(strtok(args[1],"."),".jsm"); // create a jsm instead
	    fclose(fopen(newFullFileName, "w")); // astuce to clear file if exist
 
	    generateCodeInFile(pT, newFullFileName); 

	    FILE* fichier = fopen(newFullFileName,"a+");
	    fprintf(fichier,"Halt\n"); // astuce to add Halt juste pour etre sur que ça marche avec miniJs
	    fclose(fichier);
    	freeAST(pT);

        printf( "%s has been generated\n ", newFullFileName);

    	    
      } 
   }

   else{
        if (yyparse(&pT) == 0) { // call to the parsing (and lexing) function
            printf("\nParsing:: syntax OK\n"); // reached if parsing follows the grammar
            affichageCode(pT);
        }
   }

    exit(EXIT_SUCCESS);
}
