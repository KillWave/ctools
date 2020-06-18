#include "Array.h"
Array *Array_Init(int size)
{
    Array *tmp = (Array *)malloc(sizeof(Array));
    if (tmp == NULL)
        return NULL;
    tmp->size = size;
    tmp->length = 0;
    tmp->array = NULL;
    return tmp;
}

int Array_Push(Array *array_ptr, void *data)
{

    //重新分配内存当前数组长度加1*数据大小
    void *arr = malloc(((array_ptr->length) + 1) * array_ptr->size);
    if (arr == NULL)
        return -1;
    //内存之前的内存数据copy到新分配内存中
    memcpy(arr, array_ptr->array, array_ptr->length * array_ptr->size);
    memcpy(arr + array_ptr->length * array_ptr->size, data, array_ptr->size);
    free(array_ptr->array);
    //长度加1
    array_ptr->length += 1;
    //内存地址赋值
    array_ptr->array = arr;
    return 0;
}
//将数据追加到数组的头部，成功返回0，失败返回-1
int Array_Unshift(Array *array_ptr, void *data)
{
    void *arr = malloc((array_ptr->length + 1) * array_ptr->size);
    if (arr == NULL)
        return -1;
    memcpy(arr, data, array_ptr->size);
    memcpy(arr + array_ptr->size, array_ptr->array, array_ptr->length * array_ptr->size);
    free(array_ptr->array);
    array_ptr->length += 1;
    array_ptr->array = arr;
    return 0;
}
//根据下标修改对应数据到数组，成功返回0,失败返回负数
int Array_UpdateByIndex(Array *array_ptr, void *data, int index)
{
    if (index >= array_ptr->length)
    {
        printf("\033[31m Invade append\033[0m\n");
        return -1;
    }

    memcpy(array_ptr->array + (array_ptr->size * index), data, array_ptr->size);

    return 0;
}
//根据下标获得对应数据
void *Array_QueryByIndex(Array *array_ptr, int index)
{
    if (index >= array_ptr->length)
    {
        return NULL;
    }
    return array_ptr->array + (index * array_ptr->size);
}
//根据下标删除数据
int Array_DeleteByIndex(Array *array_ptr, int index)
{
    void *arr = malloc((array_ptr->length - 1) * array_ptr->size);
    if (arr == NULL)
    {
        return -1;
    }
    memcpy(arr, array_ptr->array, index * array_ptr->size);
    memcpy(arr + index * array_ptr->size, array_ptr->array + (index + 1) * array_ptr->size, (array_ptr->length - index) * array_ptr->size);
    free(array_ptr->array);
    array_ptr->array = arr;
    array_ptr->length -= 1;
    return 0;
}

//遍历动态数组数据
void Array_Travel(Array *array_ptr, void (*callback)(void *item, void *args), void *param)
{
    int i;
    for (i = 0; i < array_ptr->length; i++)
    {
        callback(array_ptr->array + (i * array_ptr->size), param);
    }
}
//销毁动态数组
void Array_DestroyArray(Array *array_ptr)
{
    free(array_ptr->array);
    free(array_ptr);
}