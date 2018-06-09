---
layout: post
title: "Infix Expression Based on Sequence Stack"
date: 2018-06-09 02:00:00+0000
categories:
---

[View Code on Github](https://github.com/Windsoldier76/data_structure/tree/master/Data_Structure_Code/Sequence_Stack_Based_Infix_Expression)

# Source Code
```
//EvaluateExpression.cpp
#include <iostream>
#include <stdlib.h>
#include <iomanip>

#define MAXSIZE 10000
#define INSIZE 50
#define Status int
#define OK 1
#define ERROR 0

using namespace std;

//Sequence stack define
typedef struct
{
	char *base;
	char *top;
	int stacksize;
}SqStack;

//Number stack define
typedef struct
{
	double *base;
	double *top;
	int stacksize;
}SqNumStack;

//initialize Sequence stack
Status InitStack(SqStack &S)
{//operating conditions: Sequence stack exist
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

//initialize Number stack
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

//push char in Sequence stack
Status Push(SqStack &S, char c)
{
	if(S.top - S.base == S.stacksize)
		return ERROR;
	*S.top++ = c;
	//S.top;
	return OK;
}

//push double in Number stack
Status NumberPush(SqNumStack &S, double d)
{
	if(S.top - S.base == S.stacksize)
		return ERROR;
	*S.top++ = d;
	return OK;
}

//pop char from Sequence stack
Status Pop(SqStack &S, char &c)
{
	if(S.top == S.base)
		return ERROR;
	c = *--S.top;
	return OK;
}

//pop double from Number stack
Status NumberPop(SqNumStack &S, double &d)
{
	if(S.top == S.base)
		return ERROR;
	d = *--S.top;
	return OK;
}

//get the top of Sequence stack
char GetTop(SqStack S)
{
	if(S.top != S.base)
		return *(S.top - 1);
}

//get the top of Number stack
double GetNumberTop(SqNumStack S)
{
	if(S.top != S.base)
		return *(S.top - 1);
}

//judge parameter is the opertor or not
Status In(char c)
{
	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=')
		return OK;
	else
		return ERROR;
}

//judge the priority of two operator
char Precede(char a, char b)
{
	switch(a)
	{
	case '+':
		if(b == '*' || b == '/' || b == '(')
			return '<';
		else
			return '>';
		break;
	case '-':
		if(b == '*' || b == '/' || b == '(')
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
			return '<';
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

//operation
double Operate(double a, char b, double c)
{
	switch(b)
	{
	case '+':
		return a + c;
	case '-':
		return a - c;
	case '*':
		return a * c;
	case '/':
		return a / c;
	}
}

//infix arithmetic expression
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
		(*p)++;
		return 0;
	}

	char a[MAXSIZE] = { '\0' };
	int i = 0;
	while(ch != '=' || GetTop(OPTR) != '#')
	{
		if(!In(ch))
		{
			while (!In(ch))
			{
				a[i] = ch;			  //save ch into array
				i++;
				cin >> ch;
			}
			char *c = a;
			double d = atof(c);       //transform array to double
			NumberPush(OPND, d);      //push double into stack
			while (i >= 0)            //initialize array for next read
			{
				a[i] = '\0';
				i--;
			}
			i = 0;                    //initialize i for next read
		}
		else
		{

			switch(Precede(GetTop(OPTR), ch))
			{
			case '<':
				Push(OPTR, ch);
				cin >> ch;
				break;
			case '>':
				char theta;
				double a, b;
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
			}
		}
	}
	return GetNumberTop(OPND);
}

int main()
{
	double answer[INSIZE];
	int i, j, n;
	i = j = n = 0;
	int *p;
	p = &j;
	cout << "==============================" << endl;
	cout << "Welcome to use Wind calculator" << endl;
	cout << "==============================" << endl;
	cout << "please input the expression you want to calculate" << endl;
	while(j != 1)
	{
		answer[i] = EvaluateExpression(p);
		++i;
	}
	while(answer[n] != 0)
	{
		cout << setiosflags(ios::fixed) << setprecision(2) << answer[n] << endl;
		++n;
	}
	return 0;
}

```
# Input
```
2+2=
20*(4.5-3)=
4+4+4+4+4=
5.67+4.33=
=
```

# Output
```
4.00
30.00
20.00
10.00
```
