
#ifndef __ARRAY_H__
#define __ARRAY_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ARRAR_CAPACITY 10
typedef struct array
{
    size_t size;
    int capacity;
    int length;
    void *array;
    int (*push)(struct array *this, void *data);
    int (*unshift)(struct array *this, void *data);
    int (*updateByIndex)(struct array *this, void *data, int index);
    void *(*queryByIndex)(struct array *this, int index);
    int (*deleteByIndex)(struct array *this, int index);
    void (*travel)(struct array *this, void (*callback)(void *item, void *args), void *param);
    void (*destroyArray)(struct array *this);
} Array;
//初始化动态数组结构体，成功返回一个初始化完成的结构体，失败返回NULL
Array *Array_Init(void *array, int capacity,int num, size_t size);

#endif