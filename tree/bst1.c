#include<stdio.h>
#include<stdlib.h>

typedef int kType;

typedef struct Node {
	kType key;
	struct Node *left,*right;
	int count;
}bNode;

struct Node* insert(struct Node* x, struct Node* newNode){
    
    if (x == NULL) return newNode;
    if(x->key > newNode->key) x->left = insert(x->left,newNode);//k ������������
    else if(x->key < newNode->key) x->right = insert(x->right,newNode);
    x->count = 1 + sizeNode(x->left) + sizeNode(x->right);
    return x;
}

//ɾ��bst�ϵ���Сֵ������ɾ����ĸ��ڵ�
struct Node* deleteMin(struct Node* x){
    if(x->left == NULL) {
    	bNode *temp = x->right;
    	free(x); //�ֶ������ڴ� 
    	return temp;
	}
	
    x->left = deleteMin(x->left);
    x->count = 1 + sizeNode(x->left) + sizeNode(x->right);
    return x;
}

int compare(int a, int b){
    if(a == b) return 0;
    return (a > b)?1:-1;
}

int sizeNode(struct Node *x){
    if(x == NULL) return 0;
    return x->count;
}

struct Node* min(struct Node* x){
    if(!x) return NULL;
    while(x->left){
        x = x->left;
    }
    return x;
}

//ɾ���ض���ֵ Hibbard deletion
struct Node* Hdelete (struct Node* x,int k) {
    if (x == NULL) return NULL;
    int cmp = compare(k,x->key);
    if (cmp < 0) x->left = Hdelete(x->left,k);
    else if (cmp > 0) x->right = Hdelete(x->right,k);
    else {
        if (x->right == NULL) return x->left;//�Һ���Ϊ��
        else if (x->left == NULL) return x->right;//����Ϊ��
        //���Һ��Ӷ���Ϊ�գ����ұߵ���Сֵ�滻��ɾ���ڵ�
        bNode* t = (bNode *)malloc(sizeof(bNode));
        t = x;//��ɾ����� t
        x = min(t->right);
        x->right = deleteMin (t->right);//ɾ���������ϵ���Сֵ
        x->left = t->left;
    }
    x->count = 1 + sizeNode(x->left) + sizeNode(x->right);
    return x;
}


void visitBst (struct Node* root){
	if(root == NULL) return;
	visitBst(root->left);
	printf("k- %d count - %d",root->key,root->count);
	getchar();
	visitBst(root->right);
}

int main(){
	int a[10] = {1,3,5,78,4,67,44,6,9,0};
	bNode *root = NULL;
	int i;
	for(i = 0;i<10;i++){
	    bNode *newNode = (bNode *)malloc(sizeof(bNode));
	    newNode->key = a[i];
	    newNode->left = NULL;
	    newNode->right = NULL;
	    newNode->count = 1;
	    root = insert(root,newNode);
	}
	visitBst(root);
	getchar();
	Hdelete(root,78);
	visitBst(root);
	getchar();
	return 0;
}
