#include <iostream>

#define MAXSIZE 100
#define Status int
#define OK 1
#define ERROR 0

using namespace std;

typedef struct BiTNode 
{//define a binary tree
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct StackNode
{//define a link stack
	BiTree data;
	struct StackNode *next;
}StackNode,*LinkStack;

typedef struct QNode
{//define a link queue node
	BiTree data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{//define a link queue
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

//queue part
Status InitQueue(LinkQueue &Q)
{//initialize the link queue
	Q.front = Q.rear = new QNode;
	Q.front->next = NULL;
	return OK;
}

Status EnQueue(LinkQueue &Q, BiTree e)
{//entry new binary tree node into queue
	QueuePtr p = new QNode;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

Status DeQueue(LinkQueue &Q, BiTree &e)
{//delete the front binary tree node in queue
	if (Q.front == Q.rear)
		return ERROR;
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear = Q.front;
	delete p;
	return OK;
}

Status QueueEmpty(LinkQueue Q)
{//judge the queue is empty or not
	if (Q.front == Q.rear)
		return OK;
	else
		return ERROR;
}

//stack part
Status InitStack(LinkStack &S)
{//intialize the link stack
	S = NULL;
	return OK;
}

Status StackEmpty(LinkStack S)
{//judge the stack is empty or not
	if (S == NULL)
		return OK;
	else
		return ERROR;
}

Status Push(LinkStack &S, BiTree e)
{//push a binary tree node pointer into stack 
	LinkStack p;
	p = new StackNode;
	p->data = e;
	p->next = S;
	S = p;
	return OK;
}

Status Pop(LinkStack &S, BiTree &e)
{//pop a binary tree node pointer out of stack
	if (S == NULL)
		return ERROR;
	e = S->data;
	LinkStack p = S;
	S = S->next;
	delete p;
	return OK;
}

//binary tree part
void CreateBiTree(BiTree &T)
{//create a binary tree
	//input:  molp##r##eei##o###d#dsn###s##
	char ch;
	cin >> ch;
	if (ch == '#')
		T = NULL;
	else
	{
		T = new BiTNode;
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}

void InOrderTraverse(BiTree T)
{//in order traverse the binary tree with recursion
	if (T)
	{
		InOrderTraverse(T->lchild);
		cout << T->data;
		InOrderTraverse(T->rchild);
	}
}

void FirstOrderTraverse(BiTree T)
{//first order traverse the binary tree with recursion
	if (T)
	{
		cout << T->data;
		FirstOrderTraverse(T->lchild);
		FirstOrderTraverse(T->rchild);
	}
}

void EndOrderTraverse(BiTree T)
{//end order traverse the binary tree with recursion
	if (T)
	{
		EndOrderTraverse(T->lchild);
		EndOrderTraverse(T->rchild);
		cout << T->data;
	}
}

void InOrderStackTraverse(BiTree T)
{//traverse the binary tree with stack
	LinkStack S;
	InitStack(S);
	BiTree p = T;
	BiTree q = new BiTNode;
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, q);
			cout << q->data;
			p = q->rchild;
		}
	}
}

void LevelOrderTraverse(BiTree T)
{//level order traverse the binary tree with queue
	LinkQueue Q;
	InitQueue(Q);
	BiTree p = T;
	BiTree q = new BiTNode;
	while (p || !QueueEmpty(Q))
	{
		if (p)
		{
			cout << p->data;
			EnQueue(Q, p->lchild);
			EnQueue(Q, p->rchild);
			DeQueue(Q, q);
			p = q;
		}
		else
		{
			DeQueue(Q, q);
			p = q;
		}
	}
}

int Depth(BiTree T)
{//calculate the depth of the binary tree
	if (T == NULL)
		return 0;
	else
	{
		int m = Depth(T->lchild);
		int n = Depth(T->rchild);
		if (m > n)
			return (m + 1);
		else
			return (n + 1);
	}
}

int NodeCount(BiTree T)
{//count the amount of the binary tree's nodes
	if (T == NULL)
		return 0;
	else
		return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

int LeavesNodeCount(BiTree T)
{//count the amount of the binary tree's leaves' nodes
	if (T == NULL)
		return 0;
	else if (T->lchild == NULL && T->rchild == NULL)
		return 1;
	else
		return LeavesNodeCount(T->lchild) + LeavesNodeCount(T->rchild);
}

void SwitchLRchild(BiTree &T)
{//switch the nodes' left and right child
	if (T)
	{
		if (T->lchild || T->rchild)
		{
			SwitchLRchild(T->lchild);
			SwitchLRchild(T->rchild);
			BiTree temp;
			temp = T->lchild;
			T->lchild = T->rchild;
			T->rchild = temp;
		}
	}
}

int main()
{
	BiTree T;
	int depth, node_count, leaves_node_count;

	cout << "Please input your binary tree:" << endl;
	CreateBiTree(T);//moeee##s###rds###ei###dapo##n###t#r##
	
	cout << "==================================================" << endl;
	cout << "PART 1:" << endl;
	cout << "the in order traverse is:" << endl;
	InOrderTraverse(T);//eeseosdriemopnadtr
	cout << endl;
	
	cout << "the first order traverse is:" << endl;
	FirstOrderTraverse(T);//moeeesrdseidapontr
	cout << endl;
	
	cout << "the end order traverse is:" << endl;
	EndOrderTraverse(T);//eseesdieroonpartdm
	cout << endl;
	
	cout << "the in order traverse with stack is:" << endl;
	InOrderStackTraverse(T);//eeseosdriemopnadtr
	cout << endl;
	
	cout << "the level order traverse is:" << endl;
	LevelOrderTraverse(T);//modledpression
	cout << endl;

	cout << "--------------------------------------------------" << endl;
	cout << "PART 2:" << endl;
	
	node_count = NodeCount(T);               //18
	leaves_node_count = LeavesNodeCount(T);  //7
	depth = Depth(T);                        //5

	cout << "the amount of the binary tree's nodes is " << node_count << endl;
	cout << "the amount of the binary tree's leaves's nodes is " << leaves_node_count << endl;
	cout << "the depth of the binary tree is " << depth << endl;

	cout << "--------------------------------------------------" << endl;
	cout << "PART 3:" << endl;

	SwitchLRchild(T);
	cout << "the in order traverse after the switch is:" << endl;
	InOrderTraverse(T);//rtdanpomeirdsoesee
	cout << endl;
}

/*the binary tree

             m
            / \
           /   \
          /     \
         /       \
        /         \
       o           d
      / \         / \
     /   \       /   \
    e     r     a     t
   /     / \   /       \
  e     d   e p         r
 / \   /   / / \
e   s s   i o   n

*/