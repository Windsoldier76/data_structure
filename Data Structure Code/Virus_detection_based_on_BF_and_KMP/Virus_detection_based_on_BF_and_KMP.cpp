#include <iostream>
#include <fstream>

#define MAXLEN 255
using namespace std;

typedef struct
{
	char ch[MAXLEN + 1];
	int length;
}SString;

void InitSString(SString &S)
{//initalize the sequence string
	S.ch[0] = '#';                        //for monitoring variable
	for (int i = 1; i < MAXLEN; i++)
		S.ch[i] = '\0';
	S.length = 0;
}

void InputSString(SString &S)
{
	cin >> S.ch + 1;             //save in array
	int i = 1;
	while (S.ch[i] != '\0')
		i++;
	S.length = --i;              //write the length
}

int Index_BF(SString S, SString T, int pos)
{//BF algorithm
	int i = pos;                              //initialize
	int j = 1;
	while (i <= S.length && j <= T.length)    //not the end yet
	{
		if (S.ch[i] == T.ch[j])               //compare the character
		{
			++i;
			++j;
		}
		else
		{
			i = i - j + 2;                    //go back to recompare
			j = 1;
		}
	}
	if (j > T.length)                         //success
		return i - T.length;
	else                                      //fail
		return 0;
}

void Get_next(SString T, int next[])
{
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T.length)
	{
		if (j == 0 || T.ch[i] == T.ch[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

void Get_nextval(SString T, int nextval[])
{
	int i = 1, j = 0;
	nextval[1] = 0;
	while (i < T.length)
	{
		if (j == 0 || T.ch[i] == T.ch[j])
		{
			++i;
			++j;
			if (T.ch[i] != T.ch[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
	}
}

int Index_KMP(SString S, SString T, int pos, int choose)
{
	int i = pos, j = 1;
	int next[MAXLEN];
	if (choose == 2)
		Get_next(T, next);
	else
		Get_nextval(T, next);
	while (i <= S.length && j <= T.length)
	{
		if (j == 0 || S.ch[i] == T.ch[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	}
	if (j > T.length)
		return i - T.length;
	else
		return 0;
}

int Virus_detection(SString &Virus, SString &Person, int choose)
{
	int num = 0;
	int flag = 0;
	int m = Virus.length;
	for (int i = m + 1, j = 1; j <= m; j++)
		Virus.ch[i++] = Virus.ch[j];         //double the array
	Virus.ch[2 * m + 1] = '\0';
	SString temp;
	InitSString(temp);
	temp.length = m;
	for (int i = 0; i < m; i++)
	{
		for (int j = 1; j <= m; j++)
			temp.ch[j] = Virus.ch[i + j];    //get a temp array for compare
		temp.ch[m + 1] = '\0';
		if (choose == 1)
			flag = Index_BF(Person, temp, 1);
		else
			flag = Index_KMP(Person, temp, 1, choose);
		if (flag)
			break;
	}
	return flag;
}

int main()
{
	SString Virus, Person;

	int choose = 1;               //save user's choice
	cout << "Welcome to BF&KMP virus detection tool" << endl;
	while (choose)
	{
		int flag[MAXLEN], i = 0;      //save the answer
		cout << "======================================" << endl;
		cout << "Please choose the algorithm" << endl;
		cout << "1.BF" << endl;
		cout << "2.KMP NEXT" << endl;
		cout << "3.KMP NEXTVAL" << endl;
		cout << "0.exit" << endl;
		cout << "--------------------------------------" << endl;
		cin >> choose;
		if (!choose)
			break;
		cout << "======================================" << endl;
		cout << "Please input Virus's and Person's DNA" << endl;
		cout << "--------------------------------------" << endl;
		InitSString(Virus);
		InitSString(Person);
		InputSString(Virus);
		InputSString(Person);
		while (Virus.ch[1] != '0' && Person.ch[1] != '0')
		{
			flag[i] = Virus_detection(Virus, Person,choose);
			i++;
			InputSString(Virus);
			InputSString(Person);
		}

		int j = 0;
		cout << "--------------------------------------" << endl;
		cout << "The answer is:" << endl;
		while (j < i)
		{
			if (flag[j])
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
			j++;
		}

	}
	return 0;
}