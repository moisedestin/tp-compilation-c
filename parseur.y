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
    char* ival;
    char* boolval;
    char* ide;
} ;  
%type <exp> expression
%type  <exp> programme_ast
%type  <exp> commande_ast
%token <ival> NUMBER  
%token <ide>IDENT // kinds of non-trivial tokens expected from the lexer
%token EQUALS // kinds of non-trivial tokens expected from the lexer
%token INCRE // kinds of non-trivial tokens expected from the lexer
%token IF // kinds of non-trivial tokens expected from the lexer
%token ELSE // kinds of non-trivial tokens expected from the lexer
%token <boolval>BOOLEAN // kinds of non-trivial tokens expected from the lexer
%token <boolval>NAN // kinds of non-trivial tokens expected from the lexer

%token NOTEQ // kinds of non-trivial tokens expected from the lexer
%token GREQ // kinds of non-trivial tokens expected from the lexer 
%token LOEQ // kinds of non-trivial tokens expected from the lexer
%token PT_VIRG 
%start result // main non-terminal

%left '='
%left '+' '-'
%left '*' '/' '%'
%left '!'
%left INCRE

%left EQUALS NOTEQ LOEQ '<' GREQ '>' 
%nonassoc UMOINS
%% // denotes the begining of the grammar with bison-specific syntax
 
result : programme_ast { *pT = $1; };

programme_ast: commande_ast	      { $$ = $1; }
	| commande_ast programme_ast { $$ = newBinaryAST("prog",$1,$2);}
	;


commande_ast: expression PT_VIRG	{ $$ = $1; }
	| IDENT '=' expression PT_VIRG { $$ = newBinaryASTide("=",$1,$3); } 
	| IF '('expression')' commande_ast ELSE commande_ast {$$ = newBinaryAST("IfElse",newBinaryAST("If",$3,$5),newUnaryAST("Else",$7));}
	;	

expression:
expression '+' expression {  
    $$ = newBinaryAST("+",$1,$3); 
}
| expression '-' expression {  
    $$ = newBinaryAST("-",$1,$3);
}
| expression '*' expression {  
    $$ = newBinaryAST("*",$1,$3);
}

| expression '%' expression	{ 
    $$ = newBinaryAST("%",$1,$3); 
}
| expression '/' expression	{ 
    $$ = newBinaryAST("/",$1,$3); 
}
| '(' expression ')' { 
    $$ = $2; 
}
| '-' expression %prec UMOINS { 
    $$ = newUnaryAST("M",$2);
}
|expression EQUALS expression { $$ = newBinaryAST("==",$1,$3); }
|expression NOTEQ expression { $$ = newBinaryAST("!=",$1,$3); }
|expression GREQ expression	 { $$ = newBinaryAST(">=",$1,$3); }
|expression '>' expression	 { $$ = newBinaryAST(">",$1,$3); }
|expression LOEQ expression   { $$ = newBinaryAST("<=",$1,$3); }
|expression '<' expression    {  $$ = newBinaryAST("<",$1,$3); }
|'!'expression		 { $$ = newUnaryAST("!",$2); } 
| NUMBER { $$ = newLeafAST($1); }
  | BOOLEAN			 { $$ = newLeafASTForBoolAndNan($1); } 

 | IDENT			 { $$ = newLeafASTide($1); }
  | IDENT INCRE		 { $$ = newUnaryASTide($1,"++");}
    | NAN			 { $$ = newLeafASTForBoolAndNan($1); }

;
 
%% // denotes the end of the grammar
// everything after %% is copied at the end of the generated .c
int yyerror(struct _tree **pT, const char *msg){ // called by the parser if the parsing fails
    printf("Parsing:: syntax error\n");
    return 1; // to distinguish with the 0 retured by the success
}
int yywrap(void) { return 1; }
