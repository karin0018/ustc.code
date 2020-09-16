/*
 * @Author: karin018
 * @Date: 2019-10-29 00:40:56
 * @Last Modified by: karin018
 * @Last Modified time: 2019-10-29 20:59:18
 * @Project Name: Binary Tree
 */
/*
1.利用二叉链表实现二叉树
2.实现先序/中序/后序/层序/的二叉树遍历算法
3.给定中序和后序序列，分别存放在两个数组中，构造出唯一的一颗二叉树
4.编写递归算法，求二叉树节点中最大的 value 和最小的 value 之差
分别用函数实现
*/
#include <stdio.h>
#include <stdlib.h>

//定义节点数据类型为 ElemType
typedef struct {
  int id;
  int value;
} ElemType;
//定义二叉树节点 包含数据域和两个孩子节点指针
typedef struct BinaryTreeNode {
  ElemType data;
  struct BinaryTreeNode *lchild;
  struct BinaryTreeNode *rchild;
} bNode;
/*二叉链表实现二叉排序树 每一个节点的左孩子都比自己大，右孩子比自己小
输入：长度为 len 的一维数组 value
返回值：生成好的二叉树
*/
bNode *buildTreeByvalue(int *value, int len) {
  bNode *root = (bNode *)malloc(sizeof(bNode));
  if (!root) exit(0);
  int idx = 0;  //根节点的编码是 0
  root->data.id = idx;
  root->data.value = value[idx];
  root->lchild = NULL;
  root->rchild = NULL;
  for (idx = 1; idx < len; idx++) {  //逐个创建二叉树的新节点
    bNode *t = (bNode *)malloc(sizeof(bNode));
    t->data.id = idx;
    t->data.value = value[idx];
    t->lchild = NULL;
    t->rchild = NULL;
    //确定每个节点的具体位置
    bNode *parent;  // p的双亲节点
    for (bNode *p = root; p;
         (value[idx] > p->data.value) ? p = p->rchild : p = p->lchild)
      parent = p;
    (value[idx] > parent->data.value)
        ? parent->rchild = t
        : parent->lchild = t;  //找到新节点的位置并挂在树上
  }
  return root;  //返回生成好的二叉树
}

//打印某个节点的数据域
void visittreeNode(bNode *t) { printf("node data = %d , ", t->data.value); }

//先序遍历 输出二叉树的先序序列
void preTraverseTree(bNode *root) {
  if (root) {
    visittreeNode(root);
    preTraverseTree(root->lchild);
    preTraverseTree(root->rchild);
  }
}
//中序遍历 输出二叉树的中序序列
void inTraverseTree(bNode *root) {
  if (root) {
    inTraverseTree(root->lchild);
    visittreeNode(root);
    inTraverseTree(root->rchild);
  }
}
//后序遍历 输出二叉树的后序序列
void postTraverseTree(bNode *root) {
  if (root) {
    postTraverseTree(root->lchild);
    postTraverseTree(root->rchild);
    visittreeNode(root);
  }
}

//层序遍历二叉树：借助队列形式输出层序序列
/*
层序遍历就是一行一行遍历，先输出根节点，再输出其所有子节点，再输出下一层的所有节点，所以需要依靠队列实现
1. 根节点入队
2. 如果队列中有元素，则队列头出队，并在队尾添加出队元素的左右孩子
3. 如果队头没有左右孩子，则继续出下一个元素，并在队尾补充其左右孩子
4.重复上述操作 2.3. 直到队列为空

*/
struct qnode {
  bNode *ptr;          //队列节点的数据域是二叉树的节点
  struct qnode *next;  //队列的下一个节点->该队列是单链表
};
typedef struct queue {  //定义队列
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
      *head;  //创建一个新的队头指针，注意不能修改原来的 front 防止队列丢失
  //初始化队列
  struct qnode *t = (struct qnode *)malloc(sizeof(struct qnode));
  if (!t) exit(0);
  hQueue->front = hQueue->rear = head = t;
  //根节点入队
  t = (struct qnode *)malloc(sizeof(struct qnode));
  if (!t) exit(0);
  t->ptr = root;
  hQueue->rear->next = t;
  hQueue->rear = t;

  while (head !=
         hQueue->rear) {  //队列不空，头节点出队，并让头节点的左右孩子入队
    head = head->next;  //头节点出队
    visittreeNode(head->ptr);
    if (head->ptr->lchild) {  //左孩子入列
      t = (struct qnode *)malloc(sizeof(struct qnode));
      if (!t) exit(0);
      t->ptr = head->ptr->lchild;
      hQueue->rear->next = t;
      hQueue->rear = t;
    }
    if (head->ptr->rchild) {  //右孩子入列
      t = (struct qnode *)malloc(sizeof(struct qnode));
      if (!t) exit(0);
      t->ptr = head->ptr->rchild;
      hQueue->rear->next = t;
      hQueue->rear = t;
    }
  }
}

//先序遍历求最大 value 和最小 value 之差 -
//先递归寻找最大/最小值，再另写函数调用最大最小函数，求出差值
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
//返回最大值和最小值之差
int Found(bNode *root) {
  MaxValueandMinValue(root);
  return MAXVALUE - MINVAlUE;
}

//给定中序和后序序列，构建一棵二叉树
//递归思想，长序列切分成短序列
bNode *buildtreeByZH(int *intree, int iu, int il, int *posttree, int pu,
                     int pl) {
  // intree 是存中序序列的数组， posttree 是后序序列的数组
  // iu,il分别是序列上界和序列下界
  // printf("%d %d %d %d ",iu,il,pu,pl);
  int iu1, iu2, il1, il2, pu1, pu2, pl1, pl2;  //切分上下界定义
  if (il - iu != pl - pu) exit(0);
  if (pl - pu < 0) return NULL;  //序列为空，返回空

  bNode *t = (bNode *)malloc(sizeof(bNode));
  if (!t) exit(0);
  t->data.value = posttree[pl];
  t->data.id = pl;
  visittreeNode(t);                 //打印输出
  for (int i = iu; i <= il; i++) {  //从中序序列的上界遍历到下界
    if (intree[i] == posttree[pl]) {
      il1 = i - 1;  //第一个子序列的下界,左孩子
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

//测试树的功能
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

