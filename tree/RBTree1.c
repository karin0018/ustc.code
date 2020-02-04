/*
 * @Author: karin
 * @Date: 2020-02-04 15:52:11
 * @LastEditors  : karin
 * @LastEditTime : 2020-02-04 18:26:51
 * @Description:�������ʵ��
 * @TimeComplexity: O(logn)
 * @FilePath: \datastructure\ustc.code\tree\RBTree1.c
 */

#include<stdio.h>
#include<stdlib.h>

#define RED 1
#define BLACK 0
typedef int kType;//��
typedef int vType;//ֵ
//�����ṹ��
typedef struct Node{
    kType key;
    vType val;
    struct Node *left,*right;
    int color;// color of parent link; red -- true; black -- false
}RBNode;

int isRed(RBNode *x) {//��������ɫ

    if (x == NULL) return 0;
    return (x->color == RED)?1:0;
}

//�������� 1.  -- ������������ĺ�ɫ�����޸�Ϊ���㣻
//ά���˺������������
//�����޸ĺ�Ľ��ָ�룻
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

//�������� 2. -- ����������������Ӹ�Ϊ����
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

//�������� 3. -- ��ɫ��ת;
//������� -- ������ʱ�Ľ��--����һ������ 2 ��ֵ�Ľڵ���->�м�ֵ���������������ڵ���Է��ѣ���ʱ�����չ涨����������㶼���Ǻ�ɫ�ģ�
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

//���պ�����Ĺ��������
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

 //�������
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

