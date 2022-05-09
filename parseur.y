/* file parseur.y
* compilation: bison -d parseur.y
* result: parseur.tab.c = C code for syntaxic analyser
* result: parseur.tab.h = def. of lexical units aka lexems
*/
%{ // the code between %{ and %} is copied at the start of the generated .c
    #include <stdio.h>
    #include "AST.h"
    int yylex(void); // -Wall : avoid implicit call
    int yyerror(struct _tree**, const char*); // on fonctions defined by the generator
%}

%parse-param {struct _tree* *pT}
%union {
    struct _tree* exp;
    int ival;
    double dval;
} ; 
%token PT_VIRG
%token <dval> NUMBER
%token <ival> FLOAT
%type <exp> expression 
%start result // main non-terminal
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMOINS
%% // denotes the begining of the grammar with bison-specific syntax
 
result: expression PT_VIRG { *pT = $1; };
expression:
expression '+' expression {  
    $$ = newBinaryAST('+',$1,$3); 
}
| expression '-' expression {  
    $$ = newBinaryAST('-',$1,$3);
}
| expression '*' expression {  
    $$ = newBinaryAST('*',$1,$3);
}

| expression '%' expression	{ 
    $$ = newBinaryAST('%',$1,$3); 
}
| expression '/' expression	{ 
    $$ = newBinaryAST('/',$1,$3); 
}
| '(' expression ')' { 
    $$ = $2; 
    }
| '-' expression %prec UMOINS { 
    $$ = newUnaryAST('M',$2);
     }
| NUMBER { 
    $$ = newLeafAST($1); 
    }
| FLOAT			{
     $$ = newLeafAST($1); 
     } 
;
 
%% // denotes the end of the grammar
// everything after %% is copied at the end of the generated .c
int yyerror(struct _tree **pT, const char *msg){ // called by the parser if the parsing fails
    printf("Parsing:: syntax error\n");
    return 1; // to distinguish with the 0 retured by the success
}
int yywrap(void) { return 1; }
