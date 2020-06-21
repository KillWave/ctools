#include <mycon.h>
#include <stdio.h>
#include <unistd.h> //||#include<windows.h>
int main()
{
    int x = 3;
    int y = 3;
    // set_size(200, 200);
    set_title("test mycon");
    set_color(0, 0xc);
    while (y <= 24)
    {
        gotoxy(x, y);
        hide_cursor();
        printf("hello mycon");
        delay(1000);
        gotoxy(x, y);
        printf("           ");
        y++;
    }
    

    return 0;
}