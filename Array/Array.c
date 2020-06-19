#include "Array.h"
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

Array *Array_Init(void *arr, int capacity, int num, size_t size)
{
    int c = capacity == 0 ? ARRAR_CAPACITY : capacity;
    Array *array = (Array *)malloc(sizeof(Array));
    if (arr == NULL){
        arr = malloc(size * c);
    }
    array->size = size;
    array->capacity = c;
    array->length = num;
    array->array = arr;
    array->push = Array_Push;
    array->unshift = Array_Unshift;
    array->updateByIndex = Array_UpdateByIndex;
    array->queryByIndex = Array_QueryByIndex;
    array->deleteByIndex = Array_DeleteByIndex;
    array->travel = Array_Travel;
    array->destroyArray = Array_DestroyArray;
    return array;
}

int Array_realloc(Array *this)
{

    if (this->length == this->capacity)
    {
        this->capacity = this->capacity * 2;
        //重新分配内存当前数组长度加1*数据大小
        this->array = realloc(this->array, this->capacity * this->size);

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
    if (Array_realloc(this) == -1)
    {
        return -1;
    }
    memcpy(this->array + this->length * this->size, data, this->size);
    //长度加1
    this->length += 1;

    return 0;
}
// //将数据追加到数组的头部，成功返回0，失败返回-1
int Array_Unshift(Array *this, void *data)
{
    //重新分配内存当前数组长度加1*数据大小
    void *array = (void *)Array_malloc(this);
    if (array == NULL)
    {
        return -1;
    }

    memcpy(array, data, this->size);
    memcpy(array + this->size, this->array, this->length * this->size);
    free(this->array);
    this->length += 1;
    this->array = array;

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
    void *array = (void *)Array_malloc(this);
    if (array == NULL)
    {
        return -1;
    }
    memcpy(array, this->array, index * this->size);
    memcpy(array + index * this->size, this->array + (index + 1) * this->size, (this->length - index) * this->size);
    free(this->array);
    this->array = array;
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