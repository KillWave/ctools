#ifndef __TKTABLE_H__
#define __TKTABLE_H__
#include <string.h>
#include "Hash.h"
#include "DynArray.h"
/*单词存储结构定义*/
typedef struct TkWord
{
    int tkcode;                    //单词编码
    struct TkWord *next;           //指向哈希冲突的同义词
    char *spelling;                //单词字符串
    struct Symbol *sym_struct;     //指向单词所表示的结构定义
    struct Symbol *sym_identifier; //指向档次所表示的标识符

} TkWord;
static TkWord *tk_hashtable[MAXKEY]; //单词哈希表
static DynArray tktable;             //单词表
/**
 * 功能 ：运算符、关键字、常量直接放入单词表
*/
TkWord *tkword_direct_insert(TkWord *tp)
{
    int keyno;
    dynarray_add(&tktable, tp);
    keyno = elf_hash(tp->spelling);
    printf("%d\n",keyno);
    tp->next = tk_hashtable[keyno];
    tk_hashtable[keyno] = tp;
    return tp;
}
/**
 * 在单词表中查找单词
 * p:要查找的单词
 * keyno：要查找单词的哈希值
*/
TkWord *tkword_find(char *p, int keyno)
{
    TkWord *tp = NULL, *tp1;
    for (tp1 = tk_hashtable[keyno]; tp1; tp1 = tp1->next)
    {
        if (!strcmp(p, tp1->spelling))
        {
            //    token = tp1->tkcode;
            tp = tp1;
        }
    }

    return tp;
}
TkWord *tkword_insert(char *p){
    
}
#endif