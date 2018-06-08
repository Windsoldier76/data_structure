#include <iostream>

#define MAXSIZE 10000
#define OK 1
#define ERROR 0
#define Status int

using namespace std;

//顺序栈定义
typedef struct
{
	char *base;
	char *top;
	int stacksize;
}SqStack;

//初始化顺序栈
Status InitSqStack(SqStack &S)
{
	S.base = new char[MAXSIZE];
	if (!S.base)
		exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}

//压入顺序栈
Status PushSqStack(SqStack &S, char c)
{
	if (S.top - S.base == S.stacksize)
		return ERROR;
	*S.top++ = c;
	return OK;
}

//弹出顺序栈
Status PopSqStack(SqStack &S, char &c)
{
	if (S.top == S.base)
		return ERROR;
	c = *--S.top;
	return OK;
}

//取顺序栈顶元素
char GetSqStackTop(SqStack S)
{
	if (S.top != S.base)
		return *(S.top - 1);
}

//判断是否为运算符
Status In(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=')
		return OK;
	else
		return ERROR;
}

//判断运算符优先级
char Precede(char a, char b)
{
	switch (a)
	{
	case '+':
		if (b == '*' || b == '/')	
			return '<';
		else
			return '>';
		break;
	case '-':
		if (b == '*' || b == '/')
			return '<';
		else
			return '>';
		break;
	case '*':
		if (b == '(')
			return '<';
		else
			return '>';
		break;
	case '/':
		if (b == '(')
			return '<';
		else
			return '>';
		break;
	case '(':
		if (b == ')')
			return '=';
		else if (b == '#')
			return '#';
		else
			return '<';
		break;
	case ')':
		if (b == '(')
			return '#';
		else
			return '>';
	case '#':
		if (b == '#')
			return '=';
		else if (b == ')')
			return '#';
		else
			return '<';
		break;
	}
	return '#';
}

//运算
char Operate(char a, char b, char c)
{
	int x, y;
	x = a - 48;
	y = c - 48;
	switch (b)
	{
	case '+':
		return x + y + 48;
	case '-':
		return x - y + 48;
	case '*':
		return x * y + 48;
	case '/':
		return x / y + 48;
	}
}

char *PostfixExpression()
{
	SqStack OPTR;
	InitSqStack(OPTR);
	PushSqStack(OPTR, '#');
	int i = 1;
	char ch;
	char postfix[MAXSIZE];
	postfix[0] = '#';
	cin >> ch;
	if (ch == '=')
		return postfix;
	else
	{
		while (ch != '=' || GetSqStackTop(OPTR) != '#')
		{
			if (!In(ch))
			{
				postfix[i] = ch;
				i++;
				cin >> ch;
			}
			else
			{
				switch (Precede(GetSqStackTop(OPTR), ch))
				{
				case '<':
					PushSqStack(OPTR, ch);
					cin >> ch;
					break;
				case '>':
					char b;
					PopSqStack(OPTR, b);
					postfix[i] = b;
					i++;
					break;
				case'=':
					char d;
					PopSqStack(OPTR, d);
					cin >> ch;
				}
			}
		}
	}
}

char expression(char postfix[])
{
	int i = 0;

			cout << postfix << endl;
			i++;
		i = 0;
		SqStack OPND;
		InitSqStack(OPND);

		while (postfix[i] != '#')
		{
			if (!In(postfix[i]))
			{
				PushSqStack(OPND, postfix[i]);
				i++;
			}
			else
			{
				char x, y;
				PopSqStack(OPND, y);
				PopSqStack(OPND, x);
				char answer = Operate(x, postfix[i], y);
				PushSqStack(OPND, answer);
			}
		}
		return GetSqStackTop(OPND);
}

int main()
{
	char chanswer[MAXSIZE];
	int i, j, n;
	char postfix[MAXSIZE];
	i = j = n = 0;
	cout << "欢迎使用后缀计算器" << endl;
	cout << "====================" << endl;
	cout << "请输入你想计算的表达式" << endl;
	while (chanswer[i] != '#')
	{
		chanswer[i] = PostfixExpression(postfix);
		i++;
	}
	while (chanswer[i] != '#')
	{
		cout << chanswer[i] << endl;
		i++;
	}
	return 0;
}