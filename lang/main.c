#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
typedef enum
{
    IF,
    ELSE,
    FUNCTION
} category;
typedef struct
{
    category type;
    char *lexerme;
} token;
void scanf_token(char c){

}
int main()
{
    bool quit = false;
    while (!quit)
    {
        char c = getc(stdin);
        printf(">>%c\n", c);
    }

    return 0;
}