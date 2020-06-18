#include "Array.h"

Array *Array_Init(size_t size)
{
    void *array = (void *)malloc(size * ARRAR_CAPACITY);
    int length = 0;

    Array this = {size, ARRAR_CAPACITY, length,
                  array, Array_Push, Array_Unshift,
                  Array_UpdateByIndex, Array_QueryByIndex,
                  Array_DeleteByIndex, Array_Travel, Array_DestroyArray};

    return &this;
}

int Array_remalloc(Array *this)
{
    if (this->length == this->capacity)
    {
        this->capacity = this->capacity * 2;
        //重新分配内存当前数组长度加1*数据大小
        this->array = remalloc(this->array, this->capacity * this->size);

        return this->array == NULL ? -1 : 0;
    }
    return 0;
}
void *Array_malloc(Array *this)
{
    void *arr;
    if (this->length == this->capacity)
    {
        this->capacity = this->capacity * 2;
        arr = malloc(this->capacity * this->size);
        return arr;
    }
    else
    {
        arr = malloc(this->capacity * this->size);
        return arr;
    }
}

int Array_Push(Array *this, void *data)
{

    //重新分配内存当前数组长度加1*数据大小
    if (Array_remalloc(this) == -1)
    {
        return -1;
    }
    memcpy(this->array + this->length * this->size, data, this->size);
    //长度加1
    this->length += 1;

    return 0;
}
//将数据追加到数组的头部，成功返回0，失败返回-1
int Array_Unshift(Array *this, void *data)
{
    //重新分配内存当前数组长度加1*数据大小
    Array *array = (void *)Array_malloc(this);
    if (array == NULL)
    {
        return -1;
    }

    memcpy(array, data, this->size);
    memcpy(this->array + this->size, array, this->length * this->size);
    this->length += 1;
    free(array);
    array = NULL;
    return 0;
}
//根据下标修改对应数据到数组，成功返回0,失败返回负数
int Array_UpdateByIndex(Array *this, void *data, int index)
{
    if (index >= this->length)
    {
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
    Array *array = (void *)Array_malloc(this);
    if (array == NULL)
    {
        return -1;
    }
    memcpy(array, this->array, index * this->size);
    memcpy(array + index * this->size, this->array + (index + 1) * this->size, (this->length - index) * this->size);
    this->array = array;
    this->length -= 1;
    free(array);
    array = NULL;
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