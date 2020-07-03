#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct
{
    void **pAddr;
    int capacity;
    int length;
} vector;

//初始化
vector *init_vector(int capacity)
{
    if (capacity <= 0)
    {
        return NULL;
    }
    vector *array = (vector *)malloc(sizeof(vector));

    array->capacity = capacity;
    array->length = 0;
    array->pAddr = (void **)malloc(sizeof(void *) * array->capacity);
    return array;
}

//插入
void insert_vector(vector *array, int index, void *data)
{
    if (array == NULL)
        return;
    if (data == NULL)
        return;

    if (index < 0 || index > array->length)
    {
        index = array->length;
    }
    if (array->length >= array->capacity)
    {
        int newCapacity = array->capacity * 2;
        array->pAddr = (void **)realloc(array->pAddr,sizeof(void *) * newCapacity);
        array->capacity = newCapacity;
    }
    for (int i = array->length - 1; i >= index; i--)
    {
        array->pAddr[i + 1] = array->pAddr[i];
    }
    array->pAddr[index] = data;
    array->length++;
}

//遍历
void forEach_vector(vector *array, void (*myForEach)(void *))
{
    if (array == NULL)
        return;

    if (myForEach == NULL)
        return;

    for (int i = 0; i < array->length; i++)
    {
        myForEach(array->pAddr[i]);
    }
}
//删除
void removeByIndex_vector(vector *array, int index)
{
    if (array == NULL)
        return;
    if (index < 0 || index > array->length)
        return;

    for (size_t i = index; i < array->length - 1; i++)
    {
        array->pAddr[i] = array->pAddr[i + 1];
    }
    array->length--;
}
//删除 按照值删除
void removeByVal_vector(vector *array, void *data, int (*compare)(void *, void *))
{
    if (array == NULL)
        return;
    if (data == NULL)
        return;
    for (size_t i = 0; i < array->length; i++)
    {
        if (compare(array->pAddr[i], data))
        {
            removeByIndex_vector(array, i);
            break;
        }
    }
}
//销毁
void destroy_vector(vector *array)
{
    if (array == NULL)
        return;
    if (array->pAddr != NULL)
    {
        free(array->pAddr);
        array->pAddr = NULL;
    }
    free(array);
    array = NULL;
}