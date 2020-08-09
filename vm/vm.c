// this file is used for tutorial to build the compiler step by step


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#define int long long // work with 64bit target  
int line;             // line number
int *text,            // text segment
    *old_text,        // for dump text segment
    *stack;           // stack
char *data;           // data segment

// PC 程序计数器，它存放的是一个内存地址，该地址中存放着 下一条 要执行的计算机指令。
// SP 指针寄存器，永远指向当前的栈顶。注意的是由于栈是位于高地址并向低地址增长的，所以入栈时 SP 的值减小。
// BP 基址指针。也是用于指向栈的某些位置，在调用函数时会使用到它。
// AX 通用寄存器，我们的虚拟机中，它用于存放一条指令执行后的结果。
int *pc, *bp, *sp, ax, cycle; // virtual machine registers

// instructions
enum { LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };

int eval() {
    int op, *tmp;
    while (true) {
         op = *pc++; // get next operation code
        //指令集
        if (op == IMM)       { ax = *pc++;  }                                     // load immediate value to ax
        else if (op == LC)   {ax = *(char *)ax;}                               // load character to ax, address in ax
        else if (op == LI)   {ax = *(int *)ax;}                                // load integer to ax, address in ax
        else if (op == SC)   {ax = *(char *)*sp++ = ax;}                       // save character to address, value in ax, address on stack
        else if (op == SI)   {*(int *)*sp++ = ax;}                             // save integer to address, value in ax, address on stack
        else if (op == PUSH) { printf("push.%d\n",ax,*--sp);  *--sp = ax;}                                     // push the value of ax onto the stack
        else if (op == JMP)  {pc = (int *)*pc;}                                // jump to the address
        else if (op == JZ)   {pc = ax ? pc + 1 : (int *)*pc;}                   // jump if ax is zero
        else if (op == JNZ)  {pc = ax ? (int *)*pc : pc + 1;}                   // jump if ax is zero
        else if (op == CALL) {*--sp = (int)(pc+1); pc = (int *)*pc;}           // call subroutine
        //else if (op == RET)  {pc = (int *)*sp++;}                              // return from subroutine;
        else if (op == ENT)  {*--sp = (int)bp; bp = sp; sp = sp - *pc++;}      // make new stack frame
        else if (op == ADJ)  {sp = sp + *pc++;}                                // add esp, <size>
        else if (op == LEV)  {sp = bp; bp = (int *)*sp++; pc = (int *)*sp++;}  // restore call frame and PC
        else if (op == LEA)  {ax = (int)(bp + *pc++);}                         // load address for arguments.
        //操作符
        else if (op == OR)  ax = *sp++ | ax;
        else if (op == XOR) ax = *sp++ ^ ax;
        else if (op == AND) ax = *sp++ & ax;
        else if (op == EQ)  ax = *sp++ == ax;
        else if (op == NE)  ax = *sp++ != ax;
        else if (op == LT)  ax = *sp++ < ax;
        else if (op == LE)  ax = *sp++ <= ax;
        else if (op == GT)  ax = *sp++ >  ax;
        else if (op == GE)  ax = *sp++ >= ax;
        else if (op == SHL) ax = *sp++ << ax;
        else if (op == SHR) ax = *sp++ >> ax;
        else if (op == ADD) ax = *sp++ + ax;
        else if (op == SUB) ax = *sp++ - ax;
        else if (op == MUL) ax = *sp++ * ax;
        else if (op == DIV) ax = *sp++ / ax;
        else if (op == MOD) ax = *sp++ % ax;
        //内置函数
        else if (op == EXIT) { printf("exit(%d)", *sp); return *sp;}
        else if (op == OPEN) { ax = open((char *)sp[1], sp[0]); }
        else if (op == CLOS) { ax = close(*sp);}
        else if (op == READ) { ax = read(sp[2], (char *)sp[1], *sp); }
        else if (op == PRTF) { tmp = sp + pc[1]; ax = printf((char *)tmp[-1], tmp[-2], tmp[-3], tmp[-4], tmp[-5], tmp[-6]); }
        else if (op == MALC) { ax = (int)malloc(*sp);}
        else if (op == MSET) { ax = (int)memset((char *)sp[2], sp[1], *sp);}
        else if (op == MCMP) { ax = memcmp((char *)sp[2], (char *)sp[1], *sp);}
        else {
            printf("unknown instruction:%d\n", op);
            return -1;
        }
    }
    return 0;
}

int initVM(int poolsize){
     // allocate memory for virtual machine
    if (!(text = old_text = malloc(poolsize))) {
        printf("could not malloc(%d) for text area\n", poolsize);
        return -1;
    }
    if (!(data = malloc(poolsize))) {
        printf("could not malloc(%d) for data area\n", poolsize);
        return -1;
    }
    if (!(stack = malloc(poolsize))) {
        printf("could not malloc(%d) for stack area\n", poolsize);
        return -1;
    }  
    //初始化内存

    memset(text, 0, poolsize);
    memset(data, 0, poolsize);
    memset(stack, 0, poolsize);
    //初始化栈顶位置
    bp = sp = (int *)((int)stack + poolsize);
    ax = 0;
    return 0;
}

int execute(int instruction[],int length ){
    for (int i = 0; i < length; i++)
    {
         text[i] = instruction[i];
    }
    pc = text;
    return eval();
}

#undef int // Mac/clang needs this

int main(int argc, char *argv[])
{
    #define int long long // work with 64bit target
  
    int poolsize = 256 * 1024; // arbitrary size

    if(initVM(poolsize) == -1){
        printf("init falied");
    }

    int instruction[] = {IMM,10,PUSH,IMM,20,ADD,PUSH,EXIT};
    execute(instruction,sizeof(instruction)/sizeof(int));

    return 0;
}
