#include "Array.h"

Array *Array_Init(int size)
{
    Array this = {size, 0,
                  NULL, Array_Push, Array_Unshift,
                  Array_UpdateByIndex, Array_QueryByIndex,
                  Array_DeleteByIndex, Array_Travel, Array_DestroyArray};

    return &this;
}

int Array_Push(Array *this, void *data)
{

    //重新分配内存当前数组长度加1*数据大小
    void *arr = malloc(((this->length) + 1) * this->size);
    if (arr == NULL)
        return -1;
    //内存之前的内存数据copy到新分配内存中
    memcpy(arr, this->array, this->length * this->size);
    memcpy(arr + this->length * this->size, data, this->size);
    free(this->array);
    //长度加1
    this->length += 1;
    //内存地址赋值
    this->array = arr;
    return 0;
}
//将数据追加到数组的头部，成功返回0，失败返回-1
int Array_Unshift(Array *this, void *data)
{
    void *arr = malloc((this->length + 1) * this->size);
    if (arr == NULL)
        return -1;
    memcpy(arr, data, this->size);
    memcpy(arr + this->size, this->array, this->length * this->size);
    free(this->array);
    this->length += 1;
    this->array = arr;
    return 0;
}
//根据下标修改对应数据到数组，成功返回0,失败返回负数
int Array_UpdateByIndex(Array *this, void *data, int index)
{
    if (index >= this->length)
    {
        printf("\033[31m Invade append\033[0m\n");
        return -1;
    }

    memcpy(this->array + (this->size * index), data, this->size);

    return 0;
}
//根据下标获得对应数据
void *Array_QueryByIndex(Array *this, int index)
{
    if (index >= this->length)
    {
        return NULL;
    }
    return this->array + (index * this->size);
}
//根据下标删除数据
int Array_DeleteByIndex(Array *this, int index)
{
    void *arr = malloc((this->length - 1) * this->size);
    if (arr == NULL)
    {
        return -1;
    }
    memcpy(arr, this->array, index * this->size);
    memcpy(arr + index * this->size, this->array + (index + 1) * this->size, (this->length - index) * this->size);
    free(this->array);
    this->array = arr;
    this->length -= 1;
    return 0;
}

//遍历动态数组数据
void Array_Travel(Array *this, void (*callback)(void *item, void *args), void *param)
{
    int i;
    for (i = 0; i < this->length; i++)
    {
        callback(this->array + (i * this->size), param);
    }
}
//销毁动态数组
void Array_DestroyArray(Array *this)
{
    free(this->array);
    free(this);
    this = NULL;
}