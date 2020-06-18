#include "Map.h"

//f1_createHashMap
//将给定的整形数组构建为HashMap,size为数组长度
Map *CreateMap(int size)
{
    //分配内存空间
    Map *map = (Map *)malloc(sizeof(Map));
    map->size = 2 * size;
    //hash表分配空间
    map->table = (Node *)malloc(sizeof(Node) * map->size);
    //初始化
    // int j = 0;
    // for (j = 0; j <map->size; j++)
    // {
    //     map->table[j].data.val = INT_MIN;
    //     map->table[j].next = NULL;
    // }
    // int i = 0;
    // //建立HashMap
    // while (i < size)
    // {
    //     //根据数组元素的值计算其在hashMap中的位置
    //     int pos = abs(nums[i]) % map->size;
    //     //判断是否冲突
    //     if (map->table[pos].data.val == INT_MIN)
    //     {
    //         //不冲突
    //         //把元素在数组中的索引作为key
    //        map->table[pos].data.key = i;
    //         //把元素值作为value
    //         map->table[pos].data.val = nums[i];
    //     }
    //     //冲突
    //     else
    //     {
    //         //给当前元素分配一个结点，并为结点复制
    //         Node *lnode = (Node *)malloc(sizeof(Node)), *hashnode;
    //         lnode->data.key = i;
    //         lnode->data.val = nums[i];
    //         lnode->next = NULL;
    //         //从冲突位置开始，遍历链表
    //         hashnode = &(map->table[pos]);
    //         while (hashnode->next != NULL)
    //         {
    //             hashnode = hashnode->next;
    //         }
    //         //将当前结点连接到链表尾部
    //         hashnode->next = lnode;
    //     }
    //     //处理下一个元素
    //     i++;
    // }
    //处理完成，返回HashMap
    return map;
}
