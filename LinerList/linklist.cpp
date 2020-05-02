#include <stdio.h>
#include <stdlib.h>

//��Ҫ����ʲô���������ͽ���������������Ͷ���ΪElemType 
#define ElemType int

//���ڵ��ԣ����������궨��ע�͵�����ô�궨��#ifdef...#endif ����������ڱ���ʱȫ������ 
#define _DEBUG_ 1


//��̬���ֵĶ��� 
typedef struct Lnode {       //������ 
   ElemType  data;	         //���������
   struct Lnode  * next;     //�������

} LinkNode, *LinkList;

//
LinkNode *first;      //firstΪLinkList�͵ı�����Ϊ�������ͷָ��

//�����ȸ�������������ʵ��
 
/***  ��ʼ������  initList() 
 ***  ���ڴ��н�ͷָ�븳����ȷ��ֵ�������������ֳ�ʼ���ķ��� 
 ***/ 
LinkNode *initList(){     //��ʼ���������ڴ�������ͷ��� 
	LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
	if (!p) {
		printf("��ʼ������ͷ���ʧ�ܣ�\n");
		exit(0);
	}
	p->next = NULL;       //p->nextָ�븳ֵΪ�գ�ͨ�������ж�����Ľ�����data���ã��ʲ��ø�ֵ 
	return p;
}

#ifdef _DEBUG_

LinkNode head;      //��һ��ͷ��㣬�ṹ�������ȫ�ֱ��� 

/*** �������������ֳ�ʼ�� ***/ 
void initList1(LinkNode *p){
	p = (LinkNode *)malloc(sizeof(LinkNode));
	if (!p) {
		printf("��ʼ������ͷ���ʧ�ܣ�\n");
		exit(0);
	}
	p->next = NULL;       //p->nextָ�븳ֵΪ�գ�ͨ�������ж�����Ľ�����data���ã��ʲ��ø�ֵ 
} 

void initList2(){
	first = &head;
	first->next = NULL;
}
#endif 

/***  ������ĳ���  ListLength() 
 ***  ��Ҫ���������һ��,ʱ�临�Ӷ�ΪO(n=������) 
 ***/ 
int ListLength(LinkList p){
	int count = 0; 
	while (p->next!=NULL){  //Ϊʲôֱ����ָ��pѭ�������ø�������Ҳ���ԣ�Ϊʲô���ᶪʧ���� 
		count++;
		p = p->next; 
	}
	//for(int count=0;p->next!=NULL;p=p->next,count++);
	return count;
} 

/***  �ж������Ƿ�Ϊ��  ListEmpty() 
 ***  ���Ϊ�գ�����0�����򷵻ط��㣬ʱ�临�Ӷ�ΪO(1) 
 ***/ 
int ListEmpty(LinkList p){
	if (p->next!=NULL)
		return 1;
	return 0;
}

/***  �������  ClearEmpty() 
 ***  ѭ��ɾ�������һ���ڵ㣬ʱ�临�Ӷ�ΪO(n) 
 ***/ 
void ClearList(LinkList p){
	LinkNode *q;       //���⸨������ 
	while(p->next!=NULL){
		q = p->next;   //��������ָ���һ��������ݵĽڵ�/����Ԫ�� 
		p->	next = q->next;   //ͷָ���nextָ��ڶ���Ԫ�� 
		free(q);	   //�ͷŵ�һ���ڵ�ռ�ݵĴ洢�ռ� 
	}	//ѭ��ֹͣʱ��ͷָ���nextָ��NULL����ʾû������������Ԫ�ش���	 
}

/***  ��������  DestroyEmpty() 
 ***  ���������Ȼ��ȥ�ͷ�ͷ������Ŀռ䣬ʱ�临�Ӷ�ΪO(n) 
 ***/ 
void DestroyList(LinkList p){
	ClearList(p); 
	free(p);  //��initList()��ʼ������initList2()��ʼ��ʱ�������κβ����� initList1()�أ� 
} 

/***  ȡ�����i���ڵ������  GetElem() 
 ***  ��������ע��߽������ļ�飬ʱ�临�Ӷ�ΪO(n) 
 ***  ����0��ʾȡֵʧ�ܣ������ʾ�ɹ� 
 ***/ 
int GetElem(LinkList p, int i, ElemType *e){
	int k = 0;
	while(p=p->next){ //C�����У���ֵ���ʽ��ֵ���ǵȺ���ߵ�ֵ���þ���ɸ�ֵ��ͬʱ��ѭ���ж�p�Ƿ�Ϊ�� 
		k++;
		if (k==i){
			*e = p->data;
			return k;
		} 
	} 
	return 0;
} //Ϊʲô���ж�i�����Ƿ���ȷ�� 

/***  ������������Ԫ��Ϊe�Ľڵ�  LocateElem() 
 ***  ��������ʱ�临�Ӷ�ΪO(n) 
 ***  ����ָ������Ԫ��data=e�ĵ�һ���ڵ� (�����������������������ַ�������'='�����ã� 
 ***/ 
LinkNode *LocateElem(LinkList p, ElemType e){
	while(p=p->next){
		if (p->data == e)
			return p;
	} 
	return NULL;
} 

/***  ��������ĳ���ڵ��ǰ���ڵ�  PriorElem() 
 ***  ��������ע��߽������ļ�飬ʱ�临�Ӷ�ΪO(n) 
 ***  ���� NULLʱ����ʾcur_eû�ҵ� 
 ***/ 
//void PriorElem(LinkList p, LinkNode *cur_e, LinkNode *pre_e){  //����,Ϊʲô�� �޷��õ���Ҫ�ķ���ָ�� 
LinkNode *PriorElem(LinkList p, LinkNode *cur_e){ 
	for(;p->next;p=p->next)
		if (p->next == cur_e)
			return p;
	return NULL;
} 

/***  ��������ĳ���ڵ�ĺ�̽ڵ�  NextElem() 
 ***  ֱ�ӷ���cur_e��nextָ�룬ʱ�临�Ӷ�ΪO(1) 
 ***  ���� NULLʱ����ʾcur_eû���; ����дһ��ѭ�������cur_e�Ƿ��������� 
 ***/ 
LinkNode *NextElem(LinkList p, LinkNode *cur_e){ 
	return cur_e->next; 
} 

/***  �������в���һ���ڵ�  ListInsert() 
 ***  �����������Ҳ���λ�ã�ʱ�临�Ӷ�ΪO(n) 
 ***  ����ɹ����ز���ڵ�ָ�룬���� NULLʱ����ʾ����ʧ�� 
 ***/ 
LinkNode *ListInsert(LinkList p, int i, ElemType e){ 
	if (i<1) return NULL;    //λ��i��̫С 
	for(;p;p=p->next)
		if (--i<1){  //�ҵ�����λ�� 
			LinkNode *q = (LinkNode *)malloc(sizeof(LinkNode));
			if (!q) {
				printf("����ڵ�ʱ������ռ�ʧ�ܣ�\n");
				exit(0);
			}
			q->next = p->next;  //�½ڵ��nextָ��ѭ������ǰλ��p��next 
			p->next = q;        //��ǰλ�õ�nextָ��ָ���½ڵ㣬�����д��벻�ܽ������� 
			q->data = e;
			return q;
		}
	return NULL;    //λ��i��̫�󣬳��������� 
} 

/***  ��������ɾ��һ���ڵ�  ListDelete() 
 ***  ������������ɾ��λ�ã�ʱ�临�Ӷ�ΪO(n) 
 ***  ɾ���ɹ����ط��㣬����0ʱ����ʾɾ��ʧ�� 
 ***/ 
int ListDelete(LinkList p, int i, ElemType *e){ 
	if (i<1) return 0;  //λ��i��̫С 
	LinkNode *q = p;        //��p��Ϊѭ��������qָ��p��ǰ�� 
	for(p=p->next;p;p=p->next){
		if (--i<1){  //�ҵ�ɾ��λ�� 
			q->next = p->next;  //q��nextָ��p��next��ǰ��Խ����ǰ�ڵ� 
			*e = p->data;
			free(p);        //�ͷſռ� 
			return 1;
		}
		q = p;
	}
	return 0;   //λ��i��̫�󣬳���������
} 

/*** ����ڵ���ʺ��� visit()
 *** ���ú���ָ����ʵ�֣���ListTranverse()�������� 
 ***/ 
void PrintLinkNode(LinkNode *p){
	printf("%d,",p->data);  //������data������ 
}

void Add2(LinkNode *p){
	p->data += 2;    //visit()������ʵ�֣�ÿ��Ԫ��+2 
	printf("+2,");
}

//���ڵ��Դ��� 
void DebugLinkNode(LinkNode *p){
	printf("���-(*addr)=value :  ");
	printf("(*%lx)=%d\n",p,p->data);   //��������dataΪ���� 
}

/***  ��������  ListTraverse() 
 ***  ������������ɾ��λ�ã�ʱ�临�Ӷ�ΪO(n) 
 ***  ɾ���ɹ����ط��㣬����0ʱ����ʾɾ��ʧ�� 
 ***/
void ListTraverse(LinkList p,void (*ptrFunc)(LinkNode *ptr)){
	printf("����(��=%d)��", ListLength(p));
	while(p=p->next)
		(*ptrFunc)(p);
	printf("\n");
	//ListLength(p);  //����Ϊʲô�� 
}

int main(){ //���ڲ��Ի������� 

    //void (*ptrFunc)(LinkNode *p) = PrintLinkNode;   //��������ָ��
    void (*ptrFunc)(LinkNode *p) = DebugLinkNode;   //��������ָ��
	
	//��ʼ�� 
	first = initList();	
	//initList1(first);   //���ֳ�ʼ����ô���� 
	//initList2();        //��Σ� 
	
		
	//�ڲ�ͬλ�ò������� 
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
	
	//���ҵ�i�����ݻ���ֵΪx������ 
	ElemType ei;
	printf("ȡ����֮ǰ %d --", ei);
	GetElem(first,10,&ei);
	printf("��ȡ������Ϊ %d \n",ei); 
	
	LinkNode *q = LocateElem(first, 888);
	if (!q)   
		printf("û�ҵ�ֵ����Ӧ�Ľ��\n");
	else{
		q = PriorElem(first,q);
		printf("�ҵ�����ǰ��Ϊ %d -- ", q->data);
		printf("�ҵ����Ϊ %d -- ", q->next->data);
		if (q->next->next)
			printf("�ҵ����ĺ��Ϊ %d ", NextElem(first,NextElem(first,q))->data);
		printf("\n");
	}
	    
	//ɾ������
	printf("ɾ��ǰ��ֵ %d -- ", ei); 
	if (ListDelete(first,15,&ei)>0) 
		printf("ɾ����ֵΪ %d\n", ei);
	else
		printf("ɾ��ʧ�� %d \n", ei);
		
	ListTraverse(first,ptrFunc);
	printf("ɾ��ǰ��ֵ %d -- ", ei); 
	if (ListDelete(first,10,&ei)>0) 
		printf("ɾ����ֵΪ %d\n", ei);
	else
		printf("ɾ��ʧ�� %d \n", ei);
			
	printf("ɾ��ǰ��ֵ %d -- ", ei); 
	if (ListDelete(first,6,&ei)>0) 
		printf("ɾ����ֵΪ %d\n", ei);
	else
		printf("ɾ��ʧ�� %d \n", ei);	
	ListTraverse(first,ptrFunc);
	
	ptrFunc = Add2;                     //visit()��������ΪAdd2() 
	printf("ÿ������Ԫ��׼��+2\n"); 
	ListTraverse(first,ptrFunc);        //������ÿ�����ݶ���2 
	printf("���+2���µ�����");
	ListTraverse(first,PrintLinkNode);  //ֱ���ú����������������е��� 
	
					
	//�����������ٹ����е������������ 
	DestroyList(first);
	
	return 0;
}
