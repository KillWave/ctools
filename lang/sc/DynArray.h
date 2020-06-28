#ifndef __DYNARRAY_H__
#define __DYNARRAY_H__
#include <stdio.h>
#include <stdlib.h>
//动态数组结构体
typedef struct
{
    int length;
    int capacity;
    void **data;
} DynArray;

/**
 * 重新分配动态数组容量
 * parr:动态数组存储结构
 * new_size:动态数组最新元素个数
*/
void dynarray_realloc(DynArray *parr, int new_size)
{
    int capacity;
    void **data;
    capacity = parr->capacity;
    while (capacity < new_size)
    {
        capacity = capacity * 2;
    }
    data = (void **)realloc(parr->data, capacity);
    if (!data)
    {
        printf("内存分配失败");
    }
    parr->capacity = capacity;
    parr->data = data;
}
/**
 * 追加动态数组元素
 * parr ： 动态数组存储结构
 * data ： 所要追加的新元素
*/
void dynarray_add(DynArray *parr, void *data)
{
    int length;
    length = parr->length + 1;
    if (length * sizeof(void *) > parr->capacity)
    {
        dynarray_realloc(parr, length * sizeof(void *));
    }
}
/**
 * 初始化动态数组存储容量
 * parr：动态数组存储结构
 * initsize：动态数组初始化分配空间
*/
void dynarray_init(DynArray *parr, int initsize)
{
    if (parr != NULL)
    {
        parr->data = (void **)malloc(sizeof(char) * initsize);
        parr->length = 0;
        parr->capacity = initsize;
    }
}
/**
 * 释放动态数组使用的内存空间
 * parr：动态数组存储结构
*/
void dynarray_free(DynArray *parr)
{
    void **p;
    for (p = parr->data; parr->length; ++p, --parr->length)
    {
        if (*p)
            free(*p);
    }
    free(parr->data);
    parr->data = NULL;
}
/**
 * 动态数组元素查找
 * parr：动态数组存储结构
 * key：要查找的元素
*/
int dynarray_search(DynArray *parr, int key)
{
    int i;
    int **p;
    p = (int **)parr->data;
    for (i = 0; i < parr->length; ++i, p++)
    {
    }
    if (key == **p)
    {
        return i;
    }

    return -1;
}
#endif