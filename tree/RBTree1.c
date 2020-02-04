/*
 * @Author: karin
 * @Date: 2020-02-04 15:52:11
 * @LastEditors  : karin
 * @LastEditTime : 2020-02-04 18:26:51
 * @Description:红黑树的实现
 * @TimeComplexity: O(logn)
 * @FilePath: \datastructure\ustc.code\tree\RBTree1.c
 */

#include<stdio.h>
#include<stdlib.h>

#define RED 1
#define BLACK 0
typedef int kType;//键
typedef int vType;//值
//树结点结构体
typedef struct Node{
    kType key;
    vType val;
    struct Node *left,*right;
    int color;// color of parent link; red -- true; black -- false
}RBNode;

int isRed(RBNode *x) {//检验结点颜色

    if (x == NULL) return 0;
    return (x->color == RED)?1:0;
}

//基本操作 1.  -- 左旋，把右倾的红色链接修改为左倾；
//维持了红黑树的特征；
//返回修改后的结点指针；
struct Node * rotateLeft(RBNode *h) {
	// isRed(h->right) == true;
	printf("rotateLeft");
	getchar();
    RBNode *x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

//基本操作 2. -- 右旋，把左倾的连接改为右倾
struct Node * rotateRight(RBNode *h) {
    // isRed(h->left) == true;
    printf("rotateRight");
    getchar();
	RBNode *x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;

    return x;
}

//基本操作 3. -- 颜色翻转;
//适用情况 -- 分裂临时四结点--插入一个已有 2 个值的节点中->中间值上升，其余两个节点各自分裂，此时，按照规定，这两个结点都会是红色的；
void flipColors(RBNode *h) {
    // isRed(h->left) == true;
    // isRed(h->right) == true;
    // isRed(h) == true;
    printf("flipcolors");
    getchar();
	h->color = RED;
    h->left->color = BLACK;
    h->right->color = BLACK;
}


struct Node* newNode(kType k,vType v){
    RBNode *x = (RBNode *)malloc(sizeof(RBNode));
    printf("newnode %d",k);
    getchar();
    x->key = k;
    x->val = v;
    x->color = RED;
    x->left = NULL;
    x->right = NULL;
    return x;
}


kType compare (kType a, kType b) {
    if(a == b) return 0;
    return (a > b)?1:-1;
}

//按照红黑树的规则插入结点
struct Node* put (RBNode* h, kType key,vType val) {
    if (!h) return newNode(key,val);
    int cmp = compare(h->key,key);
    if (cmp < 0) h->right = put(h->right,key,val);
    else if (cmp > 0) h->left = put(h->left,key,val);
    else h->val = val;

    if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
    if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
    if (isRed(h->right) && isRed(h->left))  flipColors(h);
    return h;
}

 //中序遍历
void visitBst (struct Node* root){
	if(root == NULL) return;
	visitBst(root->left);
	printf("k- %d val - %d color - %d",root->key,root->val,root->color);
	getchar();
	visitBst(root->right);
}

 int main(){
 	int a[10] = {6,5,4,66,7,8,9,0,55,43};
 	int b[10] = {3,5,4,3,8,99,33,11,22,34};
 	RBNode *root = NULL;
 	int i = 0;
 	for(i = 0;i<10;i++){
 		root = put(root,a[i],b[i]);
 		visitBst(root);
	 }
	 printf("visit");
	 visitBst(root);
	 getchar();
	 return 0;
 }

