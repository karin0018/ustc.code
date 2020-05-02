#include <stdio.h>
#include <stdlib.h>

//��Ҫ����������������� ElmType
#define ElemType int

typedef struct Lnode {  //��������ڵ�ṹ��
  ElemType data;
  struct Lnode *next;  //���ݹ�ϵ�� next ʵ��
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
  int count = 0;  //������
  for (; p->next != NULL; count++, p = p->next)
    ;
  return count;
}

/*�ж������Ƿ�Ϊ��
 */
int ListEmpty(LinkList p) {
  if (p->next == NULL) {  // yes return 1
    return 1;
  }
  return 0;  // no return 0
}

/*������� ֻ����ͷ���
ѭ��ɾ������ڵ� ʱ�临�Ӷ� O(n)
*/
void ClearList(LinkList p) {
  LinkNode *q;
  while (p->next != NULL) {
    q = p->next;
    p->next = q->next;
    free(q);
  }
}

/*�����б�
����ͷ���
*/
void DistoryList(LinkList p) {
  ClearList(p);
  free(p);
}

/*�õ������ i ����������
�������� ʱ�临�Ӷ� O(n)
���� 0 ��ʾ��ȡʧ��
*/
int GetElem(LinkList p, int i) {
  int k = 0;                 //������
  while (p->next != NULL) {  //(p=p->next)
    k++;
    if (k == i) {
      return p->data;
    }
  }
  return 0;
}

/*������������Ԫ��Ϊ e �Ľ��
�������� ʱ�临�Ӷ� O(n)
����ָ������Ԫ�صĵ�һ�����(��ַ)
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

/*����ĳ������ǰ�����
�������� ע��߽������ļ�飬ʱ�临�Ӷ� O(n)
*/
LinkNode *PriorElem(LinkList p, LinkList cur_e) {
  for (; p->next != NULL; p = p->next) {
    if (p->next == cur_e) return p;
  }
  return NULL;
}

/*����ĳ�����ĺ�̽��
ֱ�ӷ��� cur_e �� next ָ��
*/
LinkNode *NextElem(LinkList p, LinkList cur_e) { return cur_e->next; }

/*������
����������Ҳ���λ�ã�ʱ�临�Ӷ� O(n)
���سɹ�����Ľڵ��ַ������ NULL ʱ����ʾ����ʧ��
*/
LinkNode *ListInsert(LinkList p, int i, ElemType e) {
  if (i < 1) return NULL;
  for (; p; p = p->next) {
    if (--i < 1) {  //�ҵ�Ҫ�����λ��
      LinkList q = (LinkNode *)malloc(sizeof(LinkNode));
      if (!q) {
        printf("������ʱ������ռ�ʧ�ܣ�");
        exit(0);  //����ռ�ʧ�� �����˳��ó���
      }
      q->next = p->next;
      p->next = q;
      q->data = e;
      return q;
    }
  }
  return NULL;  // i λ�����
}

/*������ɾ��һ���ڵ�
�����������Ҫɾ����λ��
ɾ���ɹ����� 1 ��ʧ�ܷ��� 0
*/
int ListDelete(LinkList p, int i,int *e) {
  if (i < 1) return NULL;
  LinkList q = p;  // ����ָ�� q ��ʾ p ��ǰ���ڵ�
  for (p = p->next; p; p = p->next) {
    if (--i < 1) {  //�ҵ�Ҫɾ����λ��
      q->next = p->next;
      *e=p->data;
      free(p);
      return 1;
    }
    q = p;
  }
  return 0;  // i λ�����
}

/*����ڵ���ʺ��� visit()
���ú���ָ��ʵ�֣��� ListTranverse () ����
*/
void PrintLinkNode(LinkList p) {
  printf("%d,  ", p->data);  // data is type of int
}

void Add2(LinkNode *p) {
  p->data += 2;
  printf("+2,  ");
}

//���ڵ��Դ���
void DebugLinkNode(LinkList p) {
  printf("�ڵ�-(*addr)=value:  ");
  printf("(*%lx)=%d\n", p,
         p->data);  //ʮ�����������ַ���������Ӧ������ֵ--������������
}

/*��������
 */
void ListTraverse(LinkList p, void (*ptrFunc)(LinkNode *ptr)) {
  //����ָ��--ָ������ָ��
  printf("����(��=%d)��", ListLength(p));
  while (p = p->next) (*ptrFunc)(p);  // p ���� NULL ���ú���ָ����ָ��ĺ���
  printf("\n");
}


int main(){ //���ڲ��Ի�������

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


  //���ҵ� i ������ ����ֵΪ X ������
  ElemType ei = 0;
  printf("ȡ����֮ǰ %d --\n ", &ei);
  ei = GetElem(first, 10);
  printf("ȡ����֮�� %d -- \n", &ei);
  ei = 8;
  printf("����ֵΪ %d ������", &ei);
  LinkNode *q = LocateElem(first, ei);
  if (!q)
    printf("����ʧ��");
  else {
    q = PriorElem(first, q);
    printf("ǰ���ڵ��� %d -- ", q->data);
    if (q->next->next)
      printf("��̽ڵ��� %d -- ", NextElem(first, NextElem(first, q))->data);
      printf("\n");
  }
  	//ɾ������
      ei=0;
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

    ptrFunc=Add2;//����ָ����ָ��ĺ�������
    printf("ÿ������Ԫ�� +2 ");
    ListTraverse(first,ptrFunc);
    printf("+2 ��ɺ��µ�����");
    ListTraverse(first,PrintLinkNode);

    //��������
    DistoryList(first);
	
	getchar();
	getchar();

    return 0;
}

