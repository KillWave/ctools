#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
//单词编码
enum e_TokenCode
{
    //运算符及分隔符
    TK_PLUS,      //+
    TK_MINUS,     //-
    TK_STAR,      //*
    TK_DIVIDE,    // /
    TK_MOD,       // %
    TK_EQ,        // ==
    TK_NEQ,       //!=
    TK_LT,        //<
    TK_LEQ,       //<=
    TK_GT,        //>
    TK_GEQ,       // >=
    TK_ASSIGN,    //=
    TK_POINTSTO,  //->
    TK_DOT,       //.
    TK_AND,       //&
    TK_OPENPA,    //(
    TK_CLOSEPA,   //)
    TK_OPENBR,    //[
    TK_CLOSEBR,   //]
    TK_BEGIN,     //{
    TK_END,       // }
    TK_SEMICOLON, // ;
    TK_COMMA,     //,
    TK_ELLIPSIS,  //...
    TK_EOF,       //EOF
    //常量
    TK_CINT,  //int
    TK_CCHAR, //char
    TK_CSTR,  //string
    //关键字
    KW_CHAR,     //char
    KW_SHORT,    //short
    KW_INT,      //int
    KW_VOID,     //void
    KW_STRUCT,   //struct
    KW_IF,       //if
    KW_ELSE,     //else
    KW_FOR,      //for
    KW_CONTINUE, //continue
    KW_BREAK,    //break
    KW_RETURN,   //return
    KW_SIZEOF,   //sizeof
    KW_ALIGN,    //__align
    KW_CDECL,    //__cdecl
    KW_STDCALL,  //__stdcall
    //标识符
    TK_IDENT

};

char *pstr = "1239083";
char *pstr1 = "1239084";
int main()
{
    int key = elf_hash(pstr);
    int key1 = elf_hash(pstr1);
    printf("%d,%d\n", key, key1);
    return 0;
}