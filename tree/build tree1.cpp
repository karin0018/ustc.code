/*
 * @Author: karin018
 * @Date: 2019-10-29 00:40:56
 * @Last Modified by: karin018
 * @Last Modified time: 2019-10-29 20:59:18
 * @Project Name: Binary Tree
 */
/*
1.���ö�������ʵ�ֶ�����
2.ʵ������/����/����/����/�Ķ����������㷨
3.��������ͺ������У��ֱ��������������У������Ψһ��һ�Ŷ�����
4.��д�ݹ��㷨����������ڵ������� value ����С�� value ֮��
�ֱ��ú���ʵ��
*/
#include <stdio.h>
#include <stdlib.h>

//����ڵ���������Ϊ ElemType
typedef struct {
  int id;
  int value;
} ElemType;
//����������ڵ� ������������������ӽڵ�ָ��
typedef struct BinaryTreeNode {
  ElemType data;
  struct BinaryTreeNode *lchild;
  struct BinaryTreeNode *rchild;
} bNode;
/*��������ʵ�ֶ��������� ÿһ���ڵ�����Ӷ����Լ����Һ��ӱ��Լ�С
���룺����Ϊ len ��һά���� value
����ֵ�����ɺõĶ�����
*/
bNode *buildTreeByvalue(int *value, int len) {
  bNode *root = (bNode *)malloc(sizeof(bNode));
  if (!root) exit(0);
  int idx = 0;  //���ڵ�ı����� 0
  root->data.id = idx;
  root->data.value = value[idx];
  root->lchild = NULL;
  root->rchild = NULL;
  for (idx = 1; idx < len; idx++) {  //����������������½ڵ�
    bNode *t = (bNode *)malloc(sizeof(bNode));
    t->data.id = idx;
    t->data.value = value[idx];
    t->lchild = NULL;
    t->rchild = NULL;
    //ȷ��ÿ���ڵ�ľ���λ��
    bNode *parent;  // p��˫�׽ڵ�
    for (bNode *p = root; p;
         (value[idx] > p->data.value) ? p = p->rchild : p = p->lchild)
      parent = p;
    (value[idx] > parent->data.value)
        ? parent->rchild = t
        : parent->lchild = t;  //�ҵ��½ڵ��λ�ò���������
  }
  return root;  //�������ɺõĶ�����
}

//��ӡĳ���ڵ��������
void visittreeNode(bNode *t) { printf("node data = %d , ", t->data.value); }

//������� �������������������
void preTraverseTree(bNode *root) {
  if (root) {
    visittreeNode(root);
    preTraverseTree(root->lchild);
    preTraverseTree(root->rchild);
  }
}
//������� �������������������
void inTraverseTree(bNode *root) {
  if (root) {
    inTraverseTree(root->lchild);
    visittreeNode(root);
    inTraverseTree(root->rchild);
  }
}
//������� ����������ĺ�������
void postTraverseTree(bNode *root) {
  if (root) {
    postTraverseTree(root->lchild);
    postTraverseTree(root->rchild);
    visittreeNode(root);
  }
}

//�������������������������ʽ�����������
/*
�����������һ��һ�б�������������ڵ㣬������������ӽڵ㣬�������һ������нڵ㣬������Ҫ��������ʵ��
1. ���ڵ����
2. �����������Ԫ�أ������ͷ���ӣ����ڶ�β��ӳ���Ԫ�ص����Һ���
3. �����ͷû�����Һ��ӣ����������һ��Ԫ�أ����ڶ�β���������Һ���
4.�ظ��������� 2.3. ֱ������Ϊ��

*/
struct qnode {
  bNode *ptr;          //���нڵ���������Ƕ������Ľڵ�
  struct qnode *next;  //���е���һ���ڵ�->�ö����ǵ�����
};
typedef struct queue {  //�������
  qnode *front;
  qnode *rear;
} linkQueue;

void seqTraverseTree(bNode *root) {
  linkQueue *hQueue = (linkQueue *)malloc(sizeof(linkQueue));
  if (!root) {
    hQueue->front = NULL;
    hQueue->rear = NULL;
    printf("empty tree!\n");
    exit(0);
  }
  struct qnode
      *head;  //����һ���µĶ�ͷָ�룬ע�ⲻ���޸�ԭ���� front ��ֹ���ж�ʧ
  //��ʼ������
  struct qnode *t = (struct qnode *)malloc(sizeof(struct qnode));
  if (!t) exit(0);
  hQueue->front = hQueue->rear = head = t;
  //���ڵ����
  t = (struct qnode *)malloc(sizeof(struct qnode));
  if (!t) exit(0);
  t->ptr = root;
  hQueue->rear->next = t;
  hQueue->rear = t;

  while (head !=
         hQueue->rear) {  //���в��գ�ͷ�ڵ���ӣ�����ͷ�ڵ�����Һ������
    head = head->next;  //ͷ�ڵ����
    visittreeNode(head->ptr);
    if (head->ptr->lchild) {  //��������
      t = (struct qnode *)malloc(sizeof(struct qnode));
      if (!t) exit(0);
      t->ptr = head->ptr->lchild;
      hQueue->rear->next = t;
      hQueue->rear = t;
    }
    if (head->ptr->rchild) {  //�Һ�������
      t = (struct qnode *)malloc(sizeof(struct qnode));
      if (!t) exit(0);
      t->ptr = head->ptr->rchild;
      hQueue->rear->next = t;
      hQueue->rear = t;
    }
  }
}

//������������ value ����С value ֮�� -
//�ȵݹ�Ѱ�����/��Сֵ������д�������������С�����������ֵ
int MAXVALUE = 0;
int MINVAlUE = 0;

void MaxValueandMinValue(bNode *root) {
  if (root) {
    if ((root->data.value) > MAXVALUE) {
      MAXVALUE = root->data.value;
    }
    if ((root->data.value) < MAXVALUE) {
      MINVAlUE = root->data.value;
    }
    MaxValueandMinValue(root->lchild);
    MaxValueandMinValue(root->rchild);
  }
}
//�������ֵ����Сֵ֮��
int Found(bNode *root) {
  MaxValueandMinValue(root);
  return MAXVALUE - MINVAlUE;
}

//��������ͺ������У�����һ�ö�����
//�ݹ�˼�룬�������зֳɶ�����
bNode *buildtreeByZH(int *intree, int iu, int il, int *posttree, int pu,
                     int pl) {
  // intree �Ǵ��������е����飬 posttree �Ǻ������е�����
  // iu,il�ֱ��������Ͻ�������½�
  // printf("%d %d %d %d ",iu,il,pu,pl);
  int iu1, iu2, il1, il2, pu1, pu2, pl1, pl2;  //�з����½綨��
  if (il - iu != pl - pu) exit(0);
  if (pl - pu < 0) return NULL;  //����Ϊ�գ����ؿ�

  bNode *t = (bNode *)malloc(sizeof(bNode));
  if (!t) exit(0);
  t->data.value = posttree[pl];
  t->data.id = pl;
  visittreeNode(t);                 //��ӡ���
  for (int i = iu; i <= il; i++) {  //���������е��Ͻ�������½�
    if (intree[i] == posttree[pl]) {
      il1 = i - 1;  //��һ�������е��½�,����
      iu1 = iu;
      iu2 = i + 1;
      il2 = il;
      pl2 = pl - 1;
      pu2 = pl - (il2 - iu2 + 1);
      pu1 = pu;
      pl1 = pu2 - 1;
    }
  }
  t->lchild = buildtreeByZH(intree, iu1, il1, posttree, pu1, pl1);
  t->rchild = buildtreeByZH(intree, iu2, il2, posttree, pu2, pl2);
  return t;
}

//�������Ĺ���
int mian() {
  int value[] = {2, 1, 4, 3, 6, 5, 7};
  int intree[] = {2, 1, 4, 3, 6, 5, 7};
  int posttree[] = {2, 4, 6, 7, 5, 3, 1};
  int len = 7;
  bNode *tree = buildTreeByvalue(value, len);
  preTraverseTree(tree);
  getchar();
 /* inTraverseTree(tree);
  getchar();
  postTraverseTree(tree);
  seqTraverseTree(tree);
  getchar();
  int range = Found(tree);
  getchar();
  bNode *newtree = buildtreeByZH(intree, 0, 6, posttree, 0, 6);
  preTraverseTree(newtree);
  getchar();*/
  printf("done!");
  return 0;
}

