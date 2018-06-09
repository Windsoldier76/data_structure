---
layout: post
title: "Hash Table"
date: 2018-06-08 11:15:00
categories:
---

# Source Code

```
//Hash_Table.cpp
#include <iostream>
#include <iomanip>

using namespace std;

#define m 14
#define p 13
#define KeyType int
#define InfoType int
#define NULLKEY 0

typedef struct
{
	KeyType key;            //key word
	InfoType otherinfo;     //other information
}HashTable[m];

void CreateHashTable(HashTable &HT)
{//create a new hash table
	KeyType key;
	for (int i = 0; i < m; ++i)
		HT[i].otherinfo = HT[i].key = NULLKEY;     //initialize the hash table
	for (int i = 0; i < m; ++i)
	{
		cin >> key;                                //input
		if (key == 0)
			return;                                //exit
		int H0 = key % p;                          //hash address
		if (HT[H0].key == NULLKEY)                 //H0 is empty
			HT[H0].key = key;                      //save
		else
		{
			for (int j = 1; j < m; ++j)
			{
				int Hi = (H0 + j) % m;             //calculate the next hash address by linear probing
				if (HT[Hi].key == NULLKEY)
				{
					HT[Hi].key = key;
					break;
				}
			}//for
		}//else
	}//for
}

void OutputHashTable(HashTable HT)
{
	cout << "| ";
	for (int i = 0; i < m; ++i)
		cout << setw(2) << i << " | ";                 //formatted output as a sheet
	cout << endl;
	cout << "| ";
	for (int i = 0; i < m; ++i)
	{
		if (HT[i].key == 0)
			cout << "   | ";
		else
			cout << setw(2) << HT[i].key << " | ";    //formatted output as a sheet
	}
	cout << endl;
}

int main()
{
	HashTable HT;
	CreateHashTable(HT);
	OutputHashTable(HT);
	return 0;
}
```

# Input

```
26 36 41 38 44 15 68 12 06 51 25 0
```

# Output

```
|  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 | 13 |
| 26 | 51 | 41 | 15 | 68 | 44 |  6 | 25 |    |    | 36 |    | 38 | 12 |
```
