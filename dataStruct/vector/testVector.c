#include "vector.h"
#define lambda(return_type,function_body)({return_type return_type##this function_body return_type##this;})

struct Person
{
    char name[65];
    int age;
};

int main()
{
    vector *arr = init_vector(5);
    struct Person p = {"1", 15};
    struct Person p1 = {"2", 15};
    struct Person p2 = {"3", 15};
    struct Person p3 = {"4", 15};
    struct Person p4 = {"5", 15};
    struct Person p5 = {"6", 15};

    insert_vector(arr, 0, &p);
    insert_vector(arr, 1, &p1);
    insert_vector(arr, 2, &p2);
    insert_vector(arr, 3, &p3);
    insert_vector(arr, 4, &p4);
    insert_vector(arr, 5, &p5);
    //3 5  2 
    forEach_vector(arr,lambda(void,(void*data){
        struct Person *p = data;
        printf("%s,%d\n",p->name,p->age);
    }));
    removeByIndex_vector(arr,1);
    forEach_vector(arr,lambda(void,(void*data){
        struct Person *p = data;
        printf("%s,%d\n",p->name,p->age);
    }));
    removeByVal_vector(arr,&p3,lambda(int,(void*data1,void*data2){
        struct Person *p1 = data1;
        struct Person *p2 = data2;
        return strcmp(p1->name,p2->name) == 0 && p1->age == p2->age;
    }));
     forEach_vector(arr,lambda(void,(void*data){
        struct Person *p = data;
        printf("%s,%d\n",p->name,p->age);
    }));
    destroy_vector(arr);
    return 0;
}