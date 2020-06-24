#include<stdio.h>
#include<time.h>
#include <event2/event.h>

struct event ev;
struct timeval tv;

void timer_cb(int fd,short event,void *arg){
    printf("timer_cb\n");
}

int main(){
    struct event_base *base = event_initialized(&ev);
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    
    return 0;
}