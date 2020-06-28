%option noyywrap
%{
    #include<stdio.h>
    #include "y.tab.h"
%}

%%
"+"             return ADD;
"-"             return SUB;
"*"             return MUL;
"/"             return DIV;
"("             return LP;
")"             return RP;
"\n"            return CR;
([1-9][0-9]*)|0|([0-9]+\.[0-9]*) {
    yylval.double_value = atof(yytext) ;
    return DOUBLE_LITERAL;
}
[ \t] ;
. {
    fprintf(stderr, "lexical error.\n");
    exit(1);
}
%%

