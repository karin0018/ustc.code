#include <stdio.h>
#include <stdlib.h>

//需要定义的链表数据类型 ElmType
#define ElemType int

typedef struct Lnode {  //定义链表节点结构体
  ElemType data;
  struct Lnode *next;  //数据关系由 next 实现
} LinkNode, *LinkList;

LinkNode *first;  // first is type of pointer (a struct pointer)

/*achieve some operations
 */

/* initial list
 */
LinkList initList() {
  LinkNode *q =(LinkNode *)malloc(sizeof(Lnode));
  if(!q){
  	printf("fail to malloc !!");
  	exit (0);
  }
  q->next=NULL;
  return q;
}

/*ListLength
 */
int ListLength(LinkList p) {
  int count = 0;  //计数器
  for (; p->next != NULL; count++, p = p->next)
    ;
  return count;
}

/*判断链表是否为空
 */
int ListEmpty(LinkList p) {
  if (p->next == NULL) {  // yes return 1
    return 1;
  }
  return 0;  // no return 0
}

/*清空链表 只保留头结点
循环删除链表节点 时间复杂度 O(n)
*/
void ClearList(LinkList p) {
  LinkNode *q;
  while (p->next != NULL) {
    q = p->next;
    p->next = q->next;
    free(q);
  }
}

/*销毁列表
包括头结点
*/
void DistoryList(LinkList p) {
  ClearList(p);
  free(p);
}

/*得到链表第 i 个结点的数据
遍历链表 时间复杂度 O(n)
返回 0 表示提取失败
*/
int GetElem(LinkList p, int i) {
  int k = 0;                 //计数器
  while (p->next != NULL) {  //(p=p->next)
    k++;
    if (k == i) {
      return p->data;
    }
  }
  return 0;
}

/*查找链表数据元素为 e 的结点
遍历链表 时间复杂度 O(n)
返回指向数据元素的第一个结点(地址)
*/
LinkNode *LocateElem(LinkList p, ElemType e) {
  while (p->next != NULL) {
    if (p->data == e) {
      return p;
    }
    p = p->next;
  }
  return NULL;
}

/*查找某个结点的前驱结点
遍历链表 注意边界条件的检查，时间复杂度 O(n)
*/
LinkNode *PriorElem(LinkList p, LinkList cur_e) {
  for (; p->next != NULL; p = p->next) {
    if (p->next == cur_e) return p;
  }
  return NULL;
}

/*查找某个结点的后继结点
直接返回 cur_e 的 next 指针
*/
LinkNode *NextElem(LinkList p, LinkList cur_e) { return cur_e->next; }

/*插入结点
遍历链表查找插入位置，时间复杂度 O(n)
返回成功插入的节点地址，返回 NULL 时，表示插入失败
*/
LinkNode *ListInsert(LinkList p, int i, ElemType e) {
  if (i < 1) return NULL;
  for (; p; p = p->next) {
    if (--i < 1) {  //找到要插入的位置
      LinkList q = (LinkNode *)malloc(sizeof(LinkNode));
      if (!q) {
        printf("插入结点时，分配空间失败！");
        exit(0);  //分配空间失败 彻底退出该程序
      }
      q->next = p->next;
      p->next = q;
      q->data = e;
      return q;
    }
  }
  return NULL;  // i 位置溢出
}

/*链表中删除一个节点
遍历链表查找要删除的位置
删除成功返回 1 ，失败返回 0
*/
int ListDelete(LinkList p, int i,int *e) {
  if (i < 1) return NULL;
  LinkList q = p;  // 辅助指针 q 表示 p 的前驱节点
  for (p = p->next; p; p = p->next) {
    if (--i < 1) {  //找到要删除的位置
      q->next = p->next;
      *e=p->data;
      free(p);
      return 1;
    }
    q = p;
  }
  return 0;  // i 位置溢出
}

/*定义节点访问函数 visit()
采用函数指针实现，供 ListTranverse () 调用
*/
void PrintLinkNode(LinkList p) {
  printf("%d,  ", p->data);  // data is type of int
}

void Add2(LinkNode *p) {
  p->data += 2;
  printf("+2,  ");
}

//用于调试代码
void DebugLinkNode(LinkList p) {
  printf("节点-(*addr)=value:  ");
  printf("(*%lx)=%d\n", p,
         p->data);  //十六进制输出地址，并输出对应的数据值--仅适用于整数
}

/*遍历链表
 */
void ListTraverse(LinkList p, void (*ptrFunc)(LinkNode *ptr)) {
  //函数指针--指向函数的指针
  printf("链表(表长=%d)：", ListLength(p));
  while (p = p->next) (*ptrFunc)(p);  // p 不是 NULL 调用函数指针所指向的函数
  printf("\n");
}


int main(){ //用于测试基本操作

    void (*ptrFunc)(LinkNode *p) = DebugLinkNode;   //声明函数指针

	//初始化
	first = initList();
	//initList1(first);   //这种初始化怎么样？
	//initList2();        //如何？


	//在不同位置插入数据
	ListTraverse(first,ptrFunc);
	ListInsert(first,1,2);
	ListInsert(first,1,3);
	ListInsert(first,1,4);
	ListInsert(first,1,5);
	ListTraverse(first,ptrFunc);
	ListInsert(first,1,6);
	ListInsert(first,1,7);
	ListInsert(first,1,8);
	ListInsert(first,1,9);
	ListTraverse(first,ptrFunc);
	ListInsert(first,3,666);
	ListInsert(first,5,777);
	ListInsert(first,7,888);
	ListInsert(first,9,999);
	ListTraverse(first,ptrFunc);


  //查找第 i 个数据 或者值为 X 的数据
  ElemType ei = 0;
  printf("取数据之前 %d --\n ", &ei);
  ei = GetElem(first, 10);
  printf("取数据之后 %d -- \n", &ei);
  ei = 8;
  printf("查找值为 %d 的数据", &ei);
  LinkNode *q = LocateElem(first, ei);
  if (!q)
    printf("查找失败");
  else {
    q = PriorElem(first, q);
    printf("前驱节点是 %d -- ", q->data);
    if (q->next->next)
      printf("后继节点是 %d -- ", NextElem(first, NextElem(first, q))->data);
      printf("\n");
  }
  	//删除数据
      ei=0;
	printf("删除前的值 %d -- ", ei);
	if (ListDelete(first,15,&ei)>0)
		printf("删除的值为 %d\n", ei);
	else
		printf("删除失败 %d \n", ei);

	ListTraverse(first,ptrFunc);
	printf("删除前的值 %d -- ", ei);
	if (ListDelete(first,10,&ei)>0)
		printf("删除的值为 %d\n", ei);
	else
		printf("删除失败 %d \n", ei);

	printf("删除前的值 %d -- ", ei);
	if (ListDelete(first,6,&ei)>0)
		printf("删除的值为 %d\n", ei);
	else
		printf("删除失败 %d \n", ei);
	ListTraverse(first,ptrFunc);

    ptrFunc=Add2;//函数指针所指向的函数定义
    printf("每个数据元素 +2 ");
    ListTraverse(first,ptrFunc);
    printf("+2 完成后，新的链表");
    ListTraverse(first,PrintLinkNode);

    //销毁链表
    DistoryList(first);
	
	getchar();
	getchar();

    return 0;
}

