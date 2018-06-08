#include <iostream>

using namespace std;

#define KeyType int
#define InfoType int
#define MAXSIZE 10000
#define Status int
#define OK 1
#define ERROR 0

typedef struct
{
	KeyType key;
	InfoType otherinfo;
}ElemType;

typedef struct BSTNode
{
	ElemType data;
	struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

void InsertBST(BSTree &T, ElemType e)
{//insert the node into binary sort tree
	if (!T)
	{
		BSTree S = new BSTNode;
		S->data = e;
		S->lchild = S->rchild = NULL;
		T = S;
	}
	else if (e.key < T->data.key)
		InsertBST(T->lchild, e);
	else if (e.key > T->data.key)
		InsertBST(T->rchild, e);
}

void CreateBSTree(BSTree &T)
{//create a new binary sort tree
	ElemType e;
	e.otherinfo = 0;
	T = NULL;
	cout << "please input the tree nodes" << endl;
	cin >> e.key;                                      //input
	while (e.key != 0)
	{
		InsertBST(T, e);
		cin >> e.key;
	}
}

BSTree SearchBST(BSTree T, KeyType key)
{
	while (true)
	{
		if (T)
			cout << "compare with " << T->data.key << endl;
		if ((!T) || key == T->data.key)
			return T;
		else if (key < T->data.key)
			T = T->lchild;
		else if (key > T->data.key)
			T = T->rchild;
		else
			return NULL;
	}
}

int main()
{
	BSTree T, A;
	ElemType M;
	char choose = 'n';
	M.otherinfo = 0;          //initialize the M
	CreateBSTree(T);
	while (choose == 'n')
	{
		cout << "please input the key M :" << endl;
		cin >> M.key;
		A = SearchBST(T, M.key);
		cout << A << endl;
		cout << "want exit?(y/n)" << endl;
		cin >> choose;
	}

	return 0;
}