%{
#include <stdio.h>
#include <stdlib.h>
#define YYDEBUG 1
int yylex (void);
int yyerror (char const *);
%}
%union {
    double double_value;
}
%token <double_value> DOUBLE_LITERAL
%token CR LP RP
%type <double_value>  expr exprcalc line 
%left ADD SUB 
%left MUL DIV
%%
line :exprcalc CR { printf(">>%0.5lf\n",$1); };
exprcalc : expr ADD expr {
         $$ = $1 + $3;
        }
        | expr SUB expr {
            $$ = $1 - $3;
        }
        | expr MUL expr {
            $$ = $1 * $3;
        }
        | expr DIV expr {
            $$ = $1 / $3;
        };
expr : DOUBLE_LITERAL
     | LP exprcalc RP {
         $$ = $2;
     };

%%

int yyerror(char const *str)
{
    extern char *yytext;
    fprintf(stderr, "parser error near %s\n", yytext);
    return 0;
}

int main(int argc,char* argv[])
{
    extern int yyparse(void);
    extern FILE *yyin;
    yyin = stdin;
    if (yyparse()) {
        fprintf(stderr, "Error!\n");
        exit(1);
    }
}

