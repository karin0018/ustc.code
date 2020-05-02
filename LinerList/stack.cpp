/*
 * @Author: karin
 * @Date: 2020-01-03 15:05:17
 * @LastEditors  : karin
 * @LastEditTime : 2020-01-05 11:04:19
 * @Description: file content
 * @TimeComplexity: O()
 * @FilePath: \datastructure\LinerList\stack.cpp
 */

/*#include<iostream>
#include<stack>
#include<queue>
using namespace std;//C++标准程序库中的所有标识符都被定义于一个名为std的namespace中

stack<int>stk;
queue<int>que; */

#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
unsigned int_stacksize;  //预分配大小
int *int_stacktop_ptr;   //栈顶指针
int *int_stackbase_ptr;  //基底指针
/**下面用宏定义来实现 8 个栈的基本操作
 * ## 表示吧前后两个参数连接起来
 * gcc -E hstack.cpp
 * 只做预编译，输出宏定义展开后的结果，用于粗略检查宏定义是否存在问题
 */
//初始化栈
#define initStack(stack)                                                    \
  stack##_stackbase_ptr = (stack *)malloc(sizeof(stack) * STACK_INIT_SIZE); \
  if (stack##_stackbase_ptr) {                                              \
    stack##_stacktop_ptr = stack##_stackbase_ptr;                           \
    stack##_stacksize = STACK_INIT_SIZE;                                    \
  } else                                                                    \
    exit(0)  //分配空间失败 退出程序

//判断是否为空栈
#define stackEmpty(stack) \
  stack##_stackbase_ptr == stack##_stacktop_ptr ? 1 : 0  // yes 1;no 0
//获得栈顶数据
#define getTop(stack, e)                        \
  stack##_stackbase_ptr == stack##_stacktop_ptr \
      ? 1                                       \
      : (e = *(stack##_stacktop_ptr - 1), 1)
// 清空栈
#define ClearStack(stack) stack##_stacktop_ptr = stack##_stackbase_ptr
//销毁栈
#define destroyStack(stack) free(stak##_stackbase_ptr)
//测量栈的长度
#define stackLength(stack) stack##_stacktop_ptr - stack##_stackbase_ptr
//弹栈
#define pop(stack, e)                           \
  stack##_stackbase_ptr == stack##_stacktop_ptr \
      ? 0                                       \
      : (e = *(--stack##_stacktop_ptr), 1)
//压栈
#define push(stack, e)                                                     \
  if (stack##_stacktop_ptr - stack##_stackbase_ptr >= stack##_stacksize) { \
    stack##_stackbase_ptr = (stack *)realloc(                              \
        stack##_stackbase_ptr,                                             \
        (stack##_stacksize + STACKINCREMENT) * sizeof(stack));             \
    if (!stack##_stackbase_ptr) exit(0);                                   \
    stack##_stacktop_ptr = stack##_stackbase_ptr + stack##_stacksize;      \
    stack##_stacksize += STACKINCREMENT;                                   \
  }                                                                        \
  *(stack##_stacktop_ptr++) = e

//定义其他类型的栈，只需要定义静态结构，基本操作重复上面的宏定义
unsigned char_stacksize;
char *char_stacktop_ptr;
char *char_stackbase_ptr;

typedef struct node {
  int data[10];
  float x, y;
} tnode;

unsigned tnode_stacksize;
tnode *tnode_stacktop_ptr;
tnode *tnode_stackbase_ptr;

int main() {
  initStack(int);
  initStack(char);
  initStack(tnode);
  int x;
  if (pop(int, x))
    printf("出栈成功 %d\n", x);
  else
    printf("栈空,出栈失败\n");
  if (stackEmpty(int))
    printf("目前栈空\n");
  else if (getTop(int, x)) {
    printf("栈顶元素是 %d\n", x);
  }
  push(int, 3);
  printf("压栈后 栈中有 %d 个元素\n", stackLength(int));
  push(int, 4);
  push(int, 5);
  printf("第二次压栈后，栈中有 %d 个元素\n", stackLength(int));
  if (pop(int, x))
    printf("出栈成功 栈顶元素是--%d\n", x);
  else
    printf("栈空");
  printf("栈中有 %d 个元素\n", stackLength(int));
  if (stackEmpty(int))
    printf("栈空");
  else if (getTop(int, x)) {
    printf("栈顶元素是 %d\n", x);
  }

  getchar();
  getchar();
  ClearStack(int);
}
