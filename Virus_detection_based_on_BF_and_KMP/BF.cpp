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
{
	S.ch[0] = '#';
	for (int i = 1; i < MAXLEN; i++)
		S.ch[i] = '\0';
	S.length = 0;
}

void InputSString(SString &S)
{
	cin >> S.ch + 1;
	int i = 1;
	while (S.ch[i] != '\0')
		i++;
	S.length = --i;
}

int Index_BF(SString S, SString T, int pos)
{
	int i = pos;
	int j = 1;
	while (i <= S.length && j <= T.length)
	{
		if (S.ch[i] == T.ch[j])
		{
			++i;
			++j;
		}
		else
		{
			i = i - j + 2;
			j = 1;
		}
	}
	if (j > T.length)
		return i - T.length;
	else
		return 0;
}

int Virus_detection(SString &Virus, SString &Person)
{
	int num = 0;
	int flag = 0;
	int m = Virus.length;
	for (int i = m + 1, j = 1; j <= m; j++)
		Virus.ch[i++] = Virus.ch[j];
	Virus.ch[2 * m + 1] = '\0';
	SString temp;
	InitSString(temp);
	temp.length = m;
	for (int i = 0; i < m; i++)
	{
		for (int j = 1; j <= m; j++)
			temp.ch[j] = Virus.ch[i + j];
		temp.ch[m + 1] = '\0';
		flag = Index_BF(Person, temp, 1);
		if (flag)
			break;
	}
	return flag;
}

int main()
{
	SString Virus, Person;
	int flag[MAXLEN], i = 0;
	int choose = 0;
	cout << "Welcome to BF&KMP virus detection tool" << endl;
	cout << "Please input Virus's and Person's DNA" << endl;
	cout << "======================================" << endl;
	InitSString(Virus);
	InitSString(Person);
	InputSString(Virus);
	InputSString(Person);
	while (Virus.ch[1] != '0' && Person.ch[1] != '0')
	{		
		flag[i] = Virus_detection(Virus,Person);
		i++;
		InputSString(Virus);
		InputSString(Person);
	}

	int j = 0;
	while (j < i)
	{
		if (flag[j])
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
		j++;
	}
	

	return 0;
}