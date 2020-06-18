#ifndef __MAP_H__
#define __MAP_H__
#include <stdlib.h>
typedef struct
{
    char *key; //键
    void *val; //值
} DataType;    //对基本数据类型进行封装，类似泛型
typedef struct
{
    DataType data;
    struct Node *next; //key冲突时，通过next指针进行连接
} Node;
typedef struct
{
    int size;
    Node *table;
} Map;

#endif