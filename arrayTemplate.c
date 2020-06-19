#include "Array/Array.h"
typedef struct
{
    int id;
    char name[32];
    float math;
    float chinese;
    float English;
} Student_t;
void callback(void *item, void *parpm)
{
    printf("item:%1f,param:%1f\n", ((Student_t *)item)->math, ((Student_t *)parpm)->math);
}
int main()
{
    Student_t student = {1, "张三", 95.2, 80, 65};
    Student_t student2 = {2, "李四", 70.2, 80, 95};
    Student_t student3 = {3, "王五", 100, 80, 95};
    Student_t studentArray[10] = {student, student2, student3, student, student2, student3};
    Array *array = Array_Init((void *)studentArray, 10,6, sizeof(Student_t));
    void *arr = array->array;
    Student_t *a = (Student_t *)(arr + sizeof(Student_t));

    printf("id:%d\n", a->id);
    array->push(array, &student);
    array->unshift(array, &student2);
    array->push(array, &student3);
    array->push(array, &student2);
    array->push(array, &student2);
    array->push(array, &student3);
    printf("%d,%d\n", array->capacity, array->length);
    printf("%1f\n", ((Student_t *)array->queryByIndex(array, 4))->math);
    array->deleteByIndex(array, 4);
    printf("%d,%d\n", array->capacity, array->length);
    // Array_UpdateByIndex(array, &student3, 0);
    // Array_DeleteByIndex(array,0);
    // void *data = Array_QueryByIndex(array, 2);
    // printf("%1f\n", ((Student_t *)data)->math);
    array->travel(array, callback, (void *)&student);

    //销毁Array
    array->destroyArray(array);

    return 0;
}