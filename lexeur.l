/* file lexeur.l [\n] { return 0; 0|[0][.][0-9]|[1-9]*[.]?[0-9]*}
* compilation: flex lexeur.l
* result: lex.yy.c = lexical analyser in C
 int yywrap(void){ return 1; } // function called at the end of the file 
*/
%{
#include <stdio.h> // printf
#include "parseur.tab.h" // token constants defined in parseur.y via #define
%}
%%
([a-z,A-Z,0-9,_]*|"0"?("."0*)?)"/"((".")?"0"|"0"("."0*)) { printf("lex::NAN %s\n",yytext); yylval.boolval=yytext; return NAN; }
(0|[1-9][0-9]*)(("."[0-9]*)?("e"-?[0-9]+)?)|("."[0-9]+)("e"-?[0-9]+)? { printf("lex::NUMBER %s\n",yytext); yylval.ival=yytext; return NUMBER; }
"True"|"False" {
    printf("lex::BOOLEAN %s\n",yytext);
    yylval.boolval=yytext;
    return BOOLEAN; 
}
"==" { 
    printf("lex::EQUALS %s\n",yytext); return EQUALS; 
}
"!=" {
     printf("lex::NOTEQ %s\n",yytext); return NOTEQ; 
}
">=" { 
    printf("lex::GREQ %s\n",yytext); return GREQ;
}
"<=" {
     printf("lex::LOEQ %s\n",yytext); return LOEQ;
}
"If" 		{ printf("lex::IF %s\n",yytext); return IF; }
"Else" 	{ printf("lex::ELSE %s\n",yytext); return ELSE; }
[a-z][0-9,A-Z,a-z,_]* { printf("lex::IDENT %s\n",yytext);  yylval.ide=yytext; return IDENT; }
"++"		{ printf("lex::INCRE %s\n",yytext); return INCRE; }
[ \t\n] { ; } // ignore space and tab
[;]	{ return PT_VIRG; }
. { printf("lex::char %s\n",yytext); return yytext[0]; } // other one-%%
%%
