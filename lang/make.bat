bison --yacc -dv lex.y
flex lex.l
gcc -o calc y.tab.c lex.yy.c