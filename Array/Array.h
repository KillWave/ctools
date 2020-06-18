
#ifndef __ARRAY_H__
#define __ARRAY_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ARRAR_CAPACITY 2
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
Array* Array_Init(size_t size);
//将数据追加到数组的尾部，成功返回0，失败返回-1
int Array_Push(Array *array_ptr, void *data);
//将数据追加到数组的头部，成功返回0，失败返回-1
int Array_Unshift(Array *array_ptr, void *data);
//按下标更新数据到数组，成功返回0
int Array_UpdateByIndex(Array *array_ptr, void *data, int index);
//根据下标获得对应数据 成功返回数据指向失败返回NULL
void *Array_QueryByIndex(Array *array_ptr, int index);
//根据下标删除数据 成功返回0失败返回-1
int Array_DeleteByIndex(Array *array_ptr, int index);
//遍历数组数据
void Array_Travel(Array *array_ptr, void (*callback)(void *item, void *args), void *param);
//销毁数组
void Array_DestroyArray(Array *array_ptr);
//数组扩容
int Array_realloc(Array *this);
//空间分配
void *Array_malloc(Array *this);
#endif