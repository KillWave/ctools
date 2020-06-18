#include "Array/Array.h"
#include "Map/Map.h"
typedef struct
{
    int id;
    char name[32];
    float math;
    float chinese;
    float English;
} Student_t;
// void callback(void *item, void *parpm)
// {
//     printf("item:%1f,param:%1f\n", ((Student_t *)item)->math, ((Student_t *)parpm)->math);
// }
int main()
{
    // Student_t student = {1, "张三", 95.2, 80, 65};
    // Student_t student2 = {2, "李四", 70.2, 80, 95};
    // Student_t student3 = {3, "王五", 100, 80, 95};
    // Array *array = Array_Init(sizeof(Student_t));
    // // printf("%d\n",array->size);
    // Array_Push(array, &student);
    // Array_Unshift(array, &student2);
    // Array_Push(array, &student3);
    // // Array_UpdateByIndex(array, &student3, 0);
    // // Array_DeleteByIndex(array,0);
    // // void *data = Array_QueryByIndex(array, 2);
    // // printf("%1f\n", ((Student_t *)data)->math);
    // Array_Travel(array, callback, (void *)&student);

    // //销毁Array 
    // Array_DestroyArray(array);



    return 0;
}