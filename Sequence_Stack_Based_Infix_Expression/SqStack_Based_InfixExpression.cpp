//基于栈的中缀算术表达式求值
#define MAXSIZE 10000
#define INSIZE 50
#define Status int
#define OK 1
#define ERROR 0

#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//顺序栈定义
typedef struct
{
	char *base;
    char *top;
	int stacksize;
}SqStack;

//顺序数栈定义
typedef struct
{
    double *base;
    double *top;
    int stacksize;
}SqNumStack;

//初始化栈
Status InitStack(SqStack &S)
{//操作结果：构造一个空栈S
	S.base = new char[MAXSIZE];
	if(S.base)
	{
		S.top = S.base;
		S.stacksize = MAXSIZE;
		return OK;
	}
	else
		return ERROR;
}

//初始化数栈
Status InitNumberStack(SqNumStack &S)
{
	S.base = new double[MAXSIZE];
	if(S.base)
	{
		S.top = S.base;
		S.stacksize = MAXSIZE;
		return OK;
	}
	else
		return ERROR;

}

//入栈
Status Push(SqStack &S, char c)
{
	if(S.top - S.base == S.stacksize)
		return ERROR;
	*S.top++ = c;
	return OK;
}

//入数栈
Status NumberPush(SqNumStack &S, double d)
{
	if(S.top - S.base == S.stacksize)
		return ERROR;
	*S.top++ = d;
	return OK;
}

//出栈
Status Pop(SqStack &S, char &c)
{
	if(S.top == S.base)
		return ERROR;
	c = *--S.top;
	return OK;
}

//出数栈
Status NumberPop(SqNumStack &S, double &d)
{
	if(S.top == S.base)
		return ERROR;
	d = *--S.top;
	return OK;
}

//取栈顶元素
char GetTop(SqStack S)
{
	if(S.top != S.base)
		return *(S.top - 1);
}

//取数栈顶元素
double GetNumberTop(SqNumStack S)
{
	if(S.top != S.base)
		return *(S.top - 1);
}

//判断读入字符是否为运算符
Status In(char c)
{
	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=')
		return OK;
	else
		return ERROR;
}

//判断两个运算符优先级
char Precede(char a, char b)
{
	switch(a)
	{
	case '+':
		if(b == '*' || b == '/')
			return '<';
		else
			return '>';
		break;
	case '-':
		if(b == '*' || b == '/')
			return '<';
		else
			return '>';
		break;
	case '*':
		if(b == '(')
			return '<';
		else
			return '>';
		break;
	case '/':
		if(b == '(')
			return '<';
		else
			return '>';
		break;
	case '(':
		if(b == ')')
			return '=';
		else if(b == '#')
			return '#';
		else
			return '>';
		break;
	case ')':
		if(b == '(')
			return '#';
		else
			return '>';
	case '#':
		if(b == '#')
			return '=';
		else if(b == ')')
			return '#';
		else
			return '<';
		break;
	}
	return '#';
}

//进行二元运算
double Operate(double a, char b, double c)
{
	switch(b)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	}
}

//中缀算术表达式
double EvaluateExpression(int *p)
{
    SqStack OPTR;
    SqNumStack OPND;
    char ch;
	InitNumberStack(OPND);
	InitStack(OPTR);
	Push(OPTR,'#');
	cin >> ch;
	if(ch == '=')
	{
		*p++;
		return NULL;
	}
	while(ch != '=' || GetTop(OPTR) != '#')
	{
		if(!In(ch))
		{
			char *a;
			a = &ch;
			double b = atof(a);
			NumberPush(OPND, b);
			cin >> ch;
		}
		else
			switch(Precede(GetTop(OPTR), ch))
			{
			case '<':
				Push(OPTR, ch);
				cin >> ch;
				break;
			case '>':
			    char theta;
			    double a,b;
				Pop(OPTR, theta);
				NumberPop(OPND,b);
				NumberPop(OPND,a);
				NumberPush(OPND, Operate(a, theta, b));
				break;
			case '=':
			    char x;
				Pop(OPTR, x);
				cin >> ch;
				break;
			case '#':
				return '#';
			}
	}
	return GetNumberTop(OPND);
}

int main()
{
	double answer[INSIZE];
	int i, j;
	i = j = 0;
	int *p;
	p = &j;
	cout << "====================" << endl;
	cout << "欢迎使用Wind计算器" << endl;
	cout << "====================" << endl;
	cout << "请输入你要计算的表达式：" << endl;
	while(j != 1)
	{
		answer[i] = EvaluateExpression(p);
		++i;
	}
	i = 0;
	while(answer[i] == NULL)
    {
		cout << setiosflags(ios::fixed) << setprecision(2) << answer[i] << endl;
        ++i;
    }
	return 0;
}
