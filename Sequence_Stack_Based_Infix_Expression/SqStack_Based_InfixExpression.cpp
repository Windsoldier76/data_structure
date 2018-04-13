//����ջ����׺�������ʽ��ֵ
#define MAXSIZE 10000
#define INSIZE 50
#define Status int
#define OK 1
#define ERROR 0

#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//˳��ջ����
typedef struct
{
	char *base;
    char *top;
	int stacksize;
}SqStack;

//˳����ջ����
typedef struct
{
    double *base;
    double *top;
    int stacksize;
}SqNumStack;

//��ʼ��ջ
Status InitStack(SqStack &S)
{//�������������һ����ջS
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

//��ʼ����ջ
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

//��ջ
Status Push(SqStack &S, char c)
{
	if(S.top - S.base == S.stacksize)
		return ERROR;
	*S.top++ = c;
	return OK;
}

//����ջ
Status NumberPush(SqNumStack &S, double d)
{
	if(S.top - S.base == S.stacksize)
		return ERROR;
	*S.top++ = d;
	return OK;
}

//��ջ
Status Pop(SqStack &S, char &c)
{
	if(S.top == S.base)
		return ERROR;
	c = *--S.top;
	return OK;
}

//����ջ
Status NumberPop(SqNumStack &S, double &d)
{
	if(S.top == S.base)
		return ERROR;
	d = *--S.top;
	return OK;
}

//ȡջ��Ԫ��
char GetTop(SqStack S)
{
	if(S.top != S.base)
		return *(S.top - 1);
}

//ȡ��ջ��Ԫ��
double GetNumberTop(SqNumStack S)
{
	if(S.top != S.base)
		return *(S.top - 1);
}

//�ж϶����ַ��Ƿ�Ϊ�����
Status In(char c)
{
	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=')
		return OK;
	else
		return ERROR;
}

//�ж�������������ȼ�
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

//���ж�Ԫ����
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

//��׺�������ʽ
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
	cout << "��ӭʹ��Wind������" << endl;
	cout << "====================" << endl;
	cout << "��������Ҫ����ı��ʽ��" << endl;
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
