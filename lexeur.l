/* file lexeur.l // [\n] { return 0; } exit sucessfully
* compilation: flex lexeur.l
* result: lex.yy.c = lexical analyser in C
 int yywrap(void){ return 1; } // function called at the end of the file 
*/
%{
#include <stdio.h> // printf
#include "parseur.tab.h" // token constants defined in parseur.y via #define
%}
%%
0|[0][.][0-9]|[1-9]*[.]?[0-9]* { 
    printf("lex::NUMBER %s\n",yytext);
    yylval.ival=atoi(yytext);
    return NUMBER;
}
0|[1-9][0-9]*[.][0-9]* {
    printf("lex::FLOTTANT %s\n",yytext);  
    yylval.dval=atoi(yytext);
    return FLOAT; 
}
"True"|"False" {
    printf("lex::BOOLEAN %s\n",yytext);
    yylval.boolval=yytext;
    return BOOLEAN; 
}
"==" { 
    printf("lex::EQUALS %s\n",yytext); return EQUALS; 
}
"!=" {
     printf("lex::NOT %s\n",yytext); return NOT; 
}
">=" { 
    printf("lex::GREQ %s\n",yytext); return GREQ;
}
"<=" {
     printf("lex::LOEQ %s\n",yytext); return LOEQ;
}
[ \t\n] { ; } // ignore space and tab
[;]	{ return PT_VIRG; }
. { printf("lex::char %s\n",yytext); return yytext[0]; } // other one-%%
%%
