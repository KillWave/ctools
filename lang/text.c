#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_WD_LEN 255 //word长度
#define MAX_INT 32767
#define MAX_SRC_LEN 1000 //源文件source长度
#define MAX_WD_CNT 100
#define KWD_CNT 6
/************************************************/

union value_type {
    int d;
    char c;
    char s[MAX_WD_LEN];
};

typedef struct
{
    int syn;
    union value_type value;
} word_type;

/********************关键字 source 栈数组和指针等****************************/
char *keywords[20] = {"begin", "if", "then", "while", "do", "end"};
char source[MAX_SRC_LEN];
word_type word_queue[MAX_WD_CNT];
int line = 1, wip = 0, ip = 0;

/**********************打印队列**************************/
void p_word_queue()
{
    int i;
    word_type w;
    printf("(syn,value)\n");
    printf("________________\n");
    for (i = 0; i < wip; i++)
    {
        w = word_queue[i];
        if ((w.syn >= 1 && w.syn <= 10) || w.syn == 18 || w.syn == 21 || w.syn == 22 || w.syn == 24)
            printf("(%d,%s)\n", w.syn, w.value.s); //开头是字母（关键字或标识符）
        else if (w.syn == 11)
            printf("(%d,%d)\n", w.syn, w.value.d); //数字
        else
            printf("(%d,%c)\n", w.syn, w.value.c); //符号
    }
    return;
}
/*************报告错误******************/
void tell_err()
{
    printf("error in line %d\n", line);
    exit(1);
    return;
}
/**************扫描器**********************/
void scan()
{
    word_type w;
    char c;
    int j = 0;

    /**********对数字进行处理***********/
    if (isdigit(c = source[ip]))
    {
        w.syn = 11;                       /* dd*  */
        w.value.d = c - '0';              //变成int型
        while (isdigit(c = source[++ip])) //下一位也是数字时候的处理方法
            w.value.d = w.value.d * 10 + c - '0';
        if (!isalpha(c))
            word_queue[wip++] = w;
        else
            tell_err();
        return;
    }

    /*********开头是字母(关键字或者标识符)**********/
    if (isalpha(c = source[ip]))
    {
        w.syn = 10;                                     /*  (ll|d) */
        w.value.s[0] = c;                               //存入缓冲区数组之中
        while (isalpha(c = source[++ip]) || isdigit(c)) //下一位是数字或者字母
            w.value.s[++j] = c;
        w.value.s[j + 1] = '\0'; //以此符号作为最终态
        for (j = 0; j < KWD_CNT; j++)
        { //判断是否是关键字
            if (strcmp(keywords[j], w.value.s) == 0)
                w.syn = j + 1;
        }
        word_queue[wip++] = w;
        return;
    }

    /*************对符号进行处理******************/
    switch (c = source[ip])
    {
    case '+':
        w.syn = 14; /* '+' */
        w.value.c = '+';
        word_queue[wip++] = w;
        ip++;
        break;
    case '-':
        w.syn = 15; /* '-' */
        w.value.c = '-';
        word_queue[wip++] = w;
        ip++;
        break;
    case '*':
        w.syn = 16; /* '*' */
        w.value.c = '*';
        word_queue[wip++] = w;
        ip++;
        break;
    case '/':
        w.syn = 17;
        w.value.c = '/';
        word_queue[wip++] = w;
        ip++;
        break;
    case ':':
        w.syn = 19;
        w.value.c = ':';
        if ((c = source[++ip]) != '=')
        {
            word_queue[wip++] = w;
        }
        else if (c == '=')
        {
            strcpy(w.value.s, ":=");
            w.syn = 18;
            word_queue[wip++] = w;
            ip++;
        }
        break;
    case '<':
        w.syn = 20;
        w.value.c = '<';
        if ((c = source[++ip]) != '>' && c != '=')
        {
            word_queue[wip++] = w;
        }
        else if (c == '>')
        {
            w.syn = 21;
            strcpy(w.value.s, "<>");
            word_queue[wip++] = w;
            ip++;
        }
        else if (c == '=')
        {
            w.syn = 22;
            strcpy(w.value.s, "<=");
            word_queue[wip++] = w;
            ip++;
        }
        break;
    case '>':
        w.syn = 23;
        w.value.c = '>';
        if ((c = source[++ip]) != '=')
        {
            word_queue[wip++] = w;
        }
        else if (c == '=')
        {
            w.syn = 24;
            strcpy(w.value.s, ">=");
            word_queue[wip++] = w;
            ip++;
        }
        break;
    case '=':
        w.syn = 25;
        w.value.c = '=';
        word_queue[wip++] = w;
        ip++;
        break;
    case ';':
        w.syn = 26;
        w.value.c = ';';
        word_queue[wip++] = w;
        ip++;
        break;
    case '(':
        w.syn = 27;
        w.value.c = '(';
        word_queue[wip++] = w;
        ip++;
        break;
    case ')':
        w.syn = 28;
        w.value.c = ')';
        word_queue[wip++] = w;
        ip++;
        break;
    case ' ':
        while (source[++ip] == ' ')
            ;
        break;
    case '\n':
        line++;
        while (source[++ip] == '\n')
            line++;
        break;

    case '\t':
        while (source[++ip] == '\t')
            ;
        break;
    case '\r':
        while (source[++ip] == '\r')
            ;
        break;
    default:
        tell_err();
    }
    return;
}
int main()
{
    FILE *fp;
    int i = 0;
    word_type w;
    fp = fopen("input.txt", "r");
    /****读取所有字符到source数组中*****/
    while (!feof(fp))
        source[i++] = getc(fp);
    fclose(fp);
    /****检测是否已经达到源文件末尾*****/
    while (source[ip] != '#')
        scan(ip);          //对单个字符进行扫描、处理
    w.syn = 0;             //此时已经扫描完毕
    w.value.c = '#';       //对#单独赋值
    word_queue[wip++] = w; //加入到打印队列里
    p_word_queue();        //调用打印函数
}
