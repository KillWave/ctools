#ifndef __STRING_H__
#define __STRING_H__
#include <stdio.h>
#include <stdlib.h>
typedef struct DynString
{
    int length;   //字符串长度
    int capacity; //包含字符串的缓存区长度
    char *data;   //指向字符串的指针
} DynString;
/**
 * 初始化动态字符串
 * pstr：动态字符串存储结构
 * initsize:字符串初始化分配空间
*/
void dynstring_init(DynString *pstr, int initsize)
{
    if (pstr != NULL)
    {
        pstr->data = (char *)malloc(sizeof(char) * initsize);
        pstr->length = 0;
        pstr->capacity = initsize;
    }
}
/**
 * 释放动态字符串使用的内存空间
 * pstr：动态字符串存储结构
*/
void dynstring_free(DynString *pstr)
{
    if (pstr != NULL)
    {
        if (pstr->data)
            free(pstr->data);
        pstr->length = 0;
        pstr->capacity = 0;
    }
}
/**
 * 重置动态字符串，先释放，重新初始化
 * pstr：动态字符串存储结构
*/
void dynstring_reset(DynString *pstr)
{
    dynstring_free(pstr);
    dynstring_init(pstr, 8);
}
/**
 * 重新分配字符串容量
 * pstr:动态字符串存储结构
 * new_size:字符串新长度
*/
void dynstring_realloc(DynString *pstr, int new_size)
{
    int capacity;
    char *data;
    capacity = pstr->capacity;
    while (capacity < new_size)
    {
        capacity = capacity * 2;
    }
    data = (char*)realloc(pstr->data, capacity);
    if (!data) return;
    pstr->capacity = capacity;
    pstr->data = data;
}
/**
 * 追加单个字符到动态字符串对象
 * pstr ：动态字符串存储结构
 * ch：所要追加的字符
*/
void dynstring_chcat(DynString *pstr, int ch)
{
    int length;
    length = pstr->length + 1;
    if (length > pstr->capacity)
    {
        dynstring_realloc(pstr, length);
    }
    ((char *)pstr->data)[length - 1] = ch;
    pstr->length = length;
}

#endif