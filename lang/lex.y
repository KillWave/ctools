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
%token CR
%type <double_value> calc line
%left '+' '-' ADD SUB 
%left '*' '/' MUL DIV
%%
line :calc CR { printf(">>%lf\n",$1); };
calc : DOUBLE_LITERAL { $$ = $1;}
     | expr ADD expr {
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

%%

int yyerror(char const *str)
{
    extern char *yytext;
    fprintf(stderr, "parser error near %s\n", yytext);
    return 0;
}

int main(void)
{
    extern int yyparse(void);
    extern FILE *yyin;

    yyin = stdin;
    if (yyparse()) {
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
}

