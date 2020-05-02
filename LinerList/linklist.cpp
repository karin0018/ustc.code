#include <stdio.h>
#include <stdlib.h>

//需要定义什么样的链表，就将数据域的数据类型定义为ElemType 
#define ElemType int

//用于调试，把下面这句宏定义注释掉，那么宏定义#ifdef...#endif 包括的语句在编译时全部忽略 
#define _DEBUG_ 1


//静态部分的定义 
typedef struct Lnode {       //链表结点 
   ElemType  data;	         //结点数据域
   struct Lnode  * next;     //结点链域

} LinkNode, *LinkList;

//
LinkNode *first;      //first为LinkList型的变量，为单链表的头指针

//以下先给出基本操作的实现
 
/***  初始化链表  initList() 
 ***  在内存中将头指针赋予正确的值，考虑下面三种初始化的方法 
 ***/ 
LinkNode *initList(){     //初始化链表，在内存中生成头结点 
	LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
	if (!p) {
		printf("初始化分配头结点失败！\n");
		exit(0);
	}
	p->next = NULL;       //p->next指针赋值为空，通常用于判断链表的结束；data域不用，故不用赋值 
	return p;
}

#ifdef _DEBUG_

LinkNode head;      //定一个头结点，结构体变量，全局变量 

/*** 考虑下面这两种初始化 ***/ 
void initList1(LinkNode *p){
	p = (LinkNode *)malloc(sizeof(LinkNode));
	if (!p) {
		printf("初始化分配头结点失败！\n");
		exit(0);
	}
	p->next = NULL;       //p->next指针赋值为空，通常用于判断链表的结束；data域不用，故不用赋值 
} 

void initList2(){
	first = &head;
	first->next = NULL;
}
#endif 

/***  求链表的长度  ListLength() 
 ***  需要将链表遍历一次,时间复杂度为O(n=链表长度) 
 ***/ 
int ListLength(LinkList p){
	int count = 0; 
	while (p->next!=NULL){  //为什么直接用指针p循环，不用辅助变量也可以？为什么不会丢失链表？ 
		count++;
		p = p->next; 
	}
	//for(int count=0;p->next!=NULL;p=p->next,count++);
	return count;
} 

/***  判断链表是否为空  ListEmpty() 
 ***  如果为空，返回0，否则返回非零，时间复杂度为O(1) 
 ***/ 
int ListEmpty(LinkList p){
	if (p->next!=NULL)
		return 1;
	return 0;
}

/***  清空链表  ClearEmpty() 
 ***  循环删除链表第一个节点，时间复杂度为O(n) 
 ***/ 
void ClearList(LinkList p){
	LinkNode *q;       //额外辅助变量 
	while(p->next!=NULL){
		q = p->next;   //辅助变量指向第一个存放数据的节点/数据元素 
		p->	next = q->next;   //头指针的next指向第二个元素 
		free(q);	   //释放第一个节点占据的存储空间 
	}	//循环停止时，头指针的next指向NULL，表示没有真正的数据元素存在	 
}

/***  销毁链表  DestroyEmpty() 
 ***  先清空链表，然后去释放头结点分配的空间，时间复杂度为O(n) 
 ***/ 
void DestroyList(LinkList p){
	ClearList(p); 
	free(p);  //用initList()初始化，用initList2()初始化时，不用任何操作。 initList1()呢？ 
} 

/***  取链表第i个节点的数据  GetElem() 
 ***  遍历链表，注意边界条件的检查，时间复杂度为O(n) 
 ***  返回0表示取值失败，非零表示成功 
 ***/ 
int GetElem(LinkList p, int i, ElemType *e){
	int k = 0;
	while(p=p->next){ //C语言中，赋值表达式的值就是等号左边的值；该句完成赋值的同时，循环判断p是否为空 
		k++;
		if (k==i){
			*e = p->data;
			return k;
		} 
	} 
	return 0;
} //为什么不判断i输入是否正确？ 

/***  查找链表数据元素为e的节点  LocateElem() 
 ***  遍历链表，时间复杂度为O(n) 
 ***  返回指向数据元素data=e的第一个节点 (适用于数据域是整数或者字符，否则'='不能用） 
 ***/ 
LinkNode *LocateElem(LinkList p, ElemType e){
	while(p=p->next){
		if (p->data == e)
			return p;
	} 
	return NULL;
} 

/***  查找链表某个节点的前驱节点  PriorElem() 
 ***  遍历链表，注意边界条件的检查，时间复杂度为O(n) 
 ***  返回 NULL时，表示cur_e没找到 
 ***/ 
//void PriorElem(LinkList p, LinkNode *cur_e, LinkNode *pre_e){  //错误,为什么？ 无法得到想要的返回指针 
LinkNode *PriorElem(LinkList p, LinkNode *cur_e){ 
	for(;p->next;p=p->next)
		if (p->next == cur_e)
			return p;
	return NULL;
} 

/***  查找链表某个节点的后继节点  NextElem() 
 ***  直接返回cur_e的next指针，时间复杂度为O(1) 
 ***  返回 NULL时，表示cur_e没后继; 可以写一个循环来检查cur_e是否在链表中 
 ***/ 
LinkNode *NextElem(LinkList p, LinkNode *cur_e){ 
	return cur_e->next; 
} 

/***  向链表中插入一个节点  ListInsert() 
 ***  遍历链表，查找插入位置，时间复杂度为O(n) 
 ***  插入成功返回插入节点指针，返回 NULL时，表示插入失败 
 ***/ 
LinkNode *ListInsert(LinkList p, int i, ElemType e){ 
	if (i<1) return NULL;    //位置i，太小 
	for(;p;p=p->next)
		if (--i<1){  //找到插入位置 
			LinkNode *q = (LinkNode *)malloc(sizeof(LinkNode));
			if (!q) {
				printf("插入节点时，分配空间失败！\n");
				exit(0);
			}
			q->next = p->next;  //新节点的next指向循环到当前位置p的next 
			p->next = q;        //当前位置的next指针指向新节点，这两行代码不能交换次序 
			q->data = e;
			return q;
		}
	return NULL;    //位置i，太大，超过链表长度 
} 

/***  从链表中删除一个节点  ListDelete() 
 ***  遍历链表，查找删除位置，时间复杂度为O(n) 
 ***  删除成功返回非零，返回0时，表示删除失败 
 ***/ 
int ListDelete(LinkList p, int i, ElemType *e){ 
	if (i<1) return 0;  //位置i，太小 
	LinkNode *q = p;        //将p视为循环变量，q指向p的前驱 
	for(p=p->next;p;p=p->next){
		if (--i<1){  //找到删除位置 
			q->next = p->next;  //q的next指向当p的next，前驱越过当前节点 
			*e = p->data;
			free(p);        //释放空间 
			return 1;
		}
		q = p;
	}
	return 0;   //位置i，太大，超过链表长度
} 

/*** 定义节点访问函数 visit()
 *** 采用函数指针来实现，供ListTranverse()函数调用 
 ***/ 
void PrintLinkNode(LinkNode *p){
	printf("%d,",p->data);  //适用于data是整数 
}

void Add2(LinkNode *p){
	p->data += 2;    //visit()函数的实现，每个元素+2 
	printf("+2,");
}

//用于调试代码 
void DebugLinkNode(LinkNode *p){
	printf("结点-(*addr)=value :  ");
	printf("(*%lx)=%d\n",p,p->data);   //仅适用于data为整数 
}

/***  遍历链表  ListTraverse() 
 ***  遍历链表，查找删除位置，时间复杂度为O(n) 
 ***  删除成功返回非零，返回0时，表示删除失败 
 ***/
void ListTraverse(LinkList p,void (*ptrFunc)(LinkNode *ptr)){
	printf("链表(表长=%d)：", ListLength(p));
	while(p=p->next)
		(*ptrFunc)(p);
	printf("\n");
	//ListLength(p);  //错误，为什么？ 
}

int main(){ //用于测试基本操作 

    //void (*ptrFunc)(LinkNode *p) = PrintLinkNode;   //声明函数指针
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
	
	//查找第i个数据或者值为x的数据 
	ElemType ei;
	printf("取数据之前 %d --", ei);
	GetElem(first,10,&ei);
	printf("读取的数据为 %d \n",ei); 
	
	LinkNode *q = LocateElem(first, 888);
	if (!q)   
		printf("没找到值所对应的结点\n");
	else{
		q = PriorElem(first,q);
		printf("找到结点的前驱为 %d -- ", q->data);
		printf("找到结点为 %d -- ", q->next->data);
		if (q->next->next)
			printf("找到结点的后继为 %d ", NextElem(first,NextElem(first,q))->data);
		printf("\n");
	}
	    
	//删除数据
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
	
	ptrFunc = Add2;                     //visit()函数定义为Add2() 
	printf("每个数据元素准备+2\n"); 
	ListTraverse(first,ptrFunc);        //将链表每个数据都加2 
	printf("完成+2后，新的链表：");
	ListTraverse(first,PrintLinkNode);  //直接用函数名当参数，进行调用 
	
					
	//销毁链表，销毁过程中调用了清空链表 
	DestroyList(first);
	
	return 0;
}
