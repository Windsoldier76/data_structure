---
layout: post
title: "Linklist Book Management System"
date: 2018-06-08 22:00:00
categories:
---

[View Code on Github](https://github.com/Windsoldier76/data_structure/tree/master/Data_Structure_Code/Link_Lisk_Book_Manage_System)

# Source Code
```
//link.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <process.h>
#include <iostream>
#include <iomanip>
#include "link.h"

#define Status int
#define MAXSIZE 10000

using namespace std;

//定义图书
typedef struct
{
	char no[20];        //图书编码
	char name[50];      //图书名字
	float price;        //图书价格
}Book;

//定义链表
typedef struct LNode
{
	Book data;             //节点的数据域
	struct LNode *next;    //节点的指针域
}LNode, *LinkList;

//检验链表是否为空
Status IsEmpty(LinkList L)
{
	if (L)
		return OK;
	else
		return ERROR;
}

//创建空表
Status CreateLinkList(LinkList &L)
{//操作结果：构造一个新的链表
	L = new LNode;   //生成新结点作为头结点，用头指针L指向头结点
	L->next = NULL;  //将头结点的指针域置空
	return OK;
}

//插入新的图书数据
Status InsertLinkList(LinkList L, int i, Book b)
{//初始条件：链表L存在，1<=i<=ListLength+1
 //操作结果：在L中第i个位置插入新的数据b
	LinkList p, q;
	int j = 0;
	p = L;
	while (p && j < i - 1)  //p扫描链表并指向第i个位置
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)    //i值非法或超出最大长度
		return ERROR;
	q = new LNode;         //为b建立新的结点
	q->data = b;           //将b存入新结点数据域
	q->next = p->next;     //新结点指针域指向第i+1位置的结点
	p->next = q;           //第i-1位置的结点指向新结点
	return OK;
}

//删除旧的图书数据
Status DeleteLinkList(LinkList L, LinkList p)
{

	if (p->next)
	{
		LinkList q = L;
		while (q->next != p)
			q = q->next;
		q->next = p->next;
		delete p;

	}
	else
		delete p;
	return OK;
}

//ISBN查找
LNode *BookNoLocate(LinkList L, char c[])
{
	LinkList p = L->next;     //扫描用指针
	while (p && strcmp(p->data.no, c))  //扫描
		p = p->next;
	return p;   			  //返回结果
}

//名称查找
LNode *BookNameLocate(LinkList L, char c[])
{
	LinkList p = L->next;     //扫描用指针
	while (p && strcmp(p->data.name, c))  //扫描
		p = p->next;
	return p;   			  //返回结果
}

//价格查找
Status BookPriceLocate(LinkList L, float min, float max)
{
	LinkList p = L;
	int ct = 0;
	p = L->next;     //扫描用指针
	while (p)
	{
		if (p->data.price>=min&&p->data.price<=max)
		{
			cout << "找到了符合条件的书" << " 书号是：" << p->data.no << " 书名是：" << p->data.name << " 价格是：" << setiosflags(ios::fixed) << setprecision(2) << p->data.price << endl;
			++ct;
		}
		p = p->next;
	}
	if (!p && !ct)
		return ERROR;
	else
		return OK;

}

//存入数据
Status InputBook(LinkList L, Book b)
{//初始条件：链表存在
 //操作结果：在链表最后一个结点处新增一个结点，将数据b存入
	LinkList p = L;
	while (p->next)   //扫描链表定位至最后一个结点
		p = p->next;
	LinkList s = new LNode;  //创建新结点
	s->data = b;			 //将图书数据存入新结点数据域
	s->next = NULL;			 //新结点指针域置空
	p->next = s;			 //链表尾结点与新结点连接
	return OK;
}

//输出数据
Status OutputBook(LinkList L)
{//初始条件：链表存在
 //操作结果：输出图书信息
	LinkList p;
	p = L;
	if (p && p->next == NULL)
		return ERROR;
	p = p->next;
	while (p)
	{
		cout << p->data.no << " " << p->data.name << " " << setiosflags(ios::fixed) << setprecision(2) << p->data.price << endl;
		p = p->next;
	}

	return OK;

}

//根据价格降序排序
Status DescendingOrder(LinkList &L)
{//初始条件：链表存在
 //操作结果：按照价格降序输出
	LinkList p, p1, p2;
	int count = 0;       //记录链表长度
	p = L;
	p1 = p->next;
	p2 = p->next->next;

	if (!p || !p1)       //链表不存在
		return ERROR;
	if(!p2)              //链表仅两个结点
		cout << p1->data.no << " " << p1->data.name << " " << setiosflags(ios::fixed) << setprecision(2) << p1->data.price << endl;

	while (p2)
	{
		if (p1->data.price < p2->data.price)
		{
			p1->next = p2->next;       //p1结点连接p2的下一个结点
			p2->next = p->next;        //p2结点连接p1
			p->next = p2;              //p结点连接p2
			p = p2;
			p2 = p1->next;
		}
		else
		{
			p = p->next;                   //向后扫描
			p1 = p1->next;
			p2 = p2->next;
		}
		++count;                       //记录长度
	}

	//--count;                           //循环次数矫正
	for (count; count > 0; count--)    //冒泡排序
	{
		p = L;
		p1 = p->next;
		p2 = p1->next;
		for (int j = 0; j < count; j++)
		{
			if (p1->data.price < p2->data.price)
			{
				p1->next = p2->next;       //p1结点连接p2的下一个结点
				p2->next = p->next;        //p2结点连接p1
				p->next = p2;              //p结点连接p2
				p = p2;
				p2 = p1->next;
			}
			else
			{
				p = p->next;                   //向后扫描
				p1 = p1->next;
				p2 = p2->next;
			}
		}
	}

	if (OutputBook(L))
		return OK;
	else
		return ERROR;
}

//按价格升序排序
Status AscendingOrder(LinkList L)
{
	LinkList p, p1, p2;
	int count = 0;       //记录链表长度
	p = L;
	p1 = p->next;
	p2 = p1->next;

	if (!p || !p1)       //链表不存在
		return ERROR;
	if (!p2)              //链表仅两个结点
		cout << p1->data.no << " " << p1->data.name << " " << setiosflags(ios::fixed) << setprecision(2) << p1->data.price << endl;

	while (p2)
	{
		if (p1->data.price > p2->data.price)
		{
			p1->next = p2->next;       //p1结点连接p2的下一个结点
			p2->next = p->next;        //p2结点连接p1
			p->next = p2;              //p结点连接p2
			p = p2;
			p2 = p1->next;
		}
		else
		{
			p = p->next;                   //向后扫描
			p1 = p1->next;
			p2 = p2->next;
		}
		++count;                       //记录长度
	}

	--count;                           //循环次数矫正
	for (count; count > 0; count--)    //冒泡排序
	{
		p = L;
		p1 = p->next;
		p2 = p1->next;
		for (int j = 0; j < count; j++)
		{
			if (p1->data.price > p2->data.price)
			{
				p1->next = p2->next;       //p1结点连接p2的下一个结点
				p2->next = p->next;        //p2结点连接p1
				p->next = p2;              //p结点连接p2
				p = p2;
				p2 = p1->next;
			}
			else
			{
				p = p->next;                   //向后扫描
				p1 = p1->next;
				p2 = p2->next;
			}
		}
	}

	if (OutputBook(L))
		return OK;
	else
		return ERROR;
}

//逆序存储输出
Status ReverseOrder(LinkList L)
{//初始条件：链表存在
 //操作结果：逆序输出链表数据
	LinkList p, p1, p2;
	int count = 0;       //记录链表长度
	p = L;
	p1 = p->next;
	p2 = p1->next;

	if (!p || !p1)       //链表不存在
		return ERROR;
	if (!p2)              //链表仅两个结点
		cout << p1->data.no << " " << p1->data.name << " " << setiosflags(ios::fixed) << setprecision(2) << p1->data.price << endl;

	while (p2)
	{

		p1->next = p2->next;       //p1结点连接p2的下一个结点
		p2->next = p->next;        //p2结点连接p1
		p->next = p2;              //p结点连接p2
		p = p2;                    //向后扫描
		p2 = p1->next;

		++count;                       //记录长度
	}

	--count;                           //循环次数矫正
	for (count; count > 0; count--)    //冒泡排序
	{
		p = L;
		p1 = p->next;
		p2 = p1->next;
		for (int j = 0; j < count; j++)
		{
			p1->next = p2->next;       //p1结点连接p2的下一个结点
			p2->next = p->next;        //p2结点连接p1
			p->next = p2;              //p结点连接p2
			p = p2;                    //向后扫描
			p2 = p1->next;
		}
	}

	if (OutputBook(L))
		return OK;
	else
		return ERROR;
}

//去重
Status DeleteSame(LinkList L)
{
	LinkList p, q;
	p = L->next->next;

	while (p)
	{
		q = L->next;
		while (q != p)
		{
			if (strcmp(q->data.no,p->data.no) == 0)
			{
				LinkList s = q;
				q = q->next;
				DeleteLinkList(L, s);
			}
			else
				q = q->next;
		}
		p = p->next;
	}
	return OK;
}

//主函数
int main()
{
	int choose = 0;       //标记用户一级选择

	//一级界面
	cout << "==============================" << endl;
	cout << "欢迎使用Wind图书管理系统！" << endl;
	cout << "==============================" << endl;
	cout << "请选择你想要使用的模式：" << endl;
	cout << "1.顺序表模式（尚未开放）" << endl;
	cout << "2.链表模式" << endl;
	cout << "==============================" << endl;

	cin >> choose;

	system("cls");
	if (choose == 1)       //皮了一把
	{
		cout << "==============================" << endl;
		cout << "说了尚未开放还选" << endl;
		cout << "好吧我知道你没得选" << endl;
		cout << "正在自动转入链表模式..." << endl;
	}

	//二级界面
	cout << "==============================" << endl;
	cout << "您已进入链表模式" << endl;

	//建立全局通用变量
	LinkList bookstack = NULL;  //图书信息链表
	int listlength = 0;         //链表长度
	int status = 0;             //标记状态量
	int isempty = 1;            //标记链表存在状态
	int tag = 1;                //标记用户二级选择
	int thirdtag = 1;           //标记用户三级选择

	while (choose)
	{
		cout << "==============================" << endl;
		cout << "请问您想做什么？" << endl;
		cout << "提示：没有消息就是好消息" << endl;
		cout << "1.创建书库" << endl;
		cout << "2.看看这个书库里面有什么" << endl;
		cout << "3.给书库排个序" << endl;
		cout << "4.给书库修改点信息" << endl;
		cout << "5.找到您想找的书" << endl;
		cout << "6.放进来点新书" << endl;
		cout << "7.去掉重复的书籍" << endl;
		cout << "0.退出链表模式" << endl;
		cout << "==============================" << endl;

		cin >> choose;

		cout << "==============================" << endl;

		switch (choose)
		{
		case 1:
			status = CreateLinkList(bookstack);     //初始化新链表
			if (!status)
				cout << "初始化链表失败" << endl;
			Book book;                  //新建临时图书信息变量
			cout << "请输入图书信息" << endl;
			while (TRUE)
			{
				cin >> book.no >> book.name >> book.price;    //输入图书信息
				if (book.price == 0)
					break;
				else
				{
					status = InputBook(bookstack, book);
					++listlength;
				}
			}
			if (!status)
				cout << "输入图书信息失败" << endl;
			break;
		case 2:
			isempty = IsEmpty(bookstack);
			if (isempty)
			{
				cout << listlength << endl;
				status = OutputBook(bookstack);
				if (!status)
					cout << "输出图书信息失败" << endl;
				break;
			}
			else
			{
				cout << "书库为空！" << endl;
				break;
			}
		case 3:
			isempty = IsEmpty(bookstack);
			if (isempty)
			{
				LinkList p1, p2;      //制作复制链表copy
				while (tag)
				{
					LinkList copy;
					p1 = bookstack->next;       //p1扫描书库链表
					CreateLinkList(copy);       //初始化复制链表
					p2 = copy;                  //p2扫描复制链表
					LinkList s;

					while (p1)
					{
						s = new LNode;          //建立新结点
						s->data = p1->data;     //复制数据域
						s->next = NULL;         //新结点指针域置空
						p2->next = s;           //连接新结点
						p2 = s;                 //扫描下一个复制链表结点
						p1 = p1->next;          //扫描下一个书库链表结点
					}

					if (!copy)
						cout << "排序初始化失败" << endl;

					cout << "请选择排序方式：" << endl;
					cout << "1.按价格降序" << endl;
					cout << "2.按价格升序" << endl;
					cout << "3.逆序排序" << endl;
					cout << "0.退出排序模式" << endl;
					cout << "==============================" << endl;

					cin >> tag;

					switch (tag)
					{
					case 1:
						status = DescendingOrder(copy);
						if (!status)
							cout << "排序失败！" << endl;
						delete copy;
						break;
					case 2:
						status = AscendingOrder(copy);
						if (!status)
							cout << "排序失败！" << endl;
						delete copy;
						break;
					case 3:
						status = ReverseOrder(copy);
						if (!status)
							cout << "排序失败！" << endl;
						delete copy;
						break;
					case 0:
						delete copy;
						break;
					}
				}
				break;
			}
			else
			{
				cout << "书库为空！" << endl;
				break;
			}
		case 4:
			isempty = IsEmpty(bookstack);
			if (isempty)
			{
				tag = 1;
				while (tag)
				{
					cout << "==============================" << endl;
					cout << "请问书库哪本书出错了？" << endl;
					cout << "1.书号错了" << endl;
					cout << "2.名字错了" << endl;
					cout << "3.价格错了" << endl;
					cout << "4.我要删除书" << endl;
					cout << "0.退出修改" << endl;
					cout << "==============================" << endl;

					cin >> tag;
					char no[20] = { 0 };
					char name[50] = { 0 };
					switch (tag)
					{

					case 1:
						thirdtag = 1;
						while (thirdtag)
						{
							cout << "==============================" << endl;
							cout << "请问您要改哪本书？" << endl;
							cout << "1.根据书号查找" << endl;
							cout << "2.根据名字查找" << endl;
							cout << "0.退出查找" << endl;
							cout << "==============================" << endl;
							cin >> thirdtag;

							LinkList p;
							switch (thirdtag)
							{
							case 1:
								cout << "请输入你要查询的书号：" << endl;
								cin >> no;
								p = BookNoLocate(bookstack, no);
								if (!p)
									cout << "抱歉，本书库没有您要找的那本书" << endl;
								else
								{
									cout << "请输入你要修改的书号：" << endl;
									cin >> p->data.no;
								}
								break;
							case 2:
								cout << "请输入你要查询的书名：" << endl;
								cin >> name;
								p = BookNameLocate(bookstack, name);
								if (!p)
									cout << "抱歉，本书库没有您要找的那本书" << endl;
								else
								{
									cout << "请输入你要修改的书号：" << endl;
									cin >> p->data.no;
								}
								break;
							}
						}
						break;
					case 2:
						thirdtag = 1;
						while (thirdtag)
						{
							cout << "==============================" << endl;
							cout << "请问您要改哪本书？" << endl;
							cout << "1.根据书号查找" << endl;
							cout << "2.根据名字查找" << endl;
							cout << "0.退出查找" << endl;
							cout << "==============================" << endl;
							cin >> thirdtag;

							LinkList p;
							switch (thirdtag)
							{
							case 1:
								cout << "请输入你要查询的书号：" << endl;
								cin >> no;
								p = BookNoLocate(bookstack, no);
								if (!p)
									cout << "抱歉，本书库没有您要找的那本书" << endl;
								else
								{
									cout << "请输入你要修改的书名：" << endl;
									cin >> p->data.name;
								}
								break;
							case 2:
								cout << "请输入你要查询的书名：" << endl;
								cin >> name;
								p = BookNameLocate(bookstack, name);
								if (!p)
									cout << "抱歉，本书库没有您要找的那本书" << endl;
								else
								{
									cout << "请输入你要修改的书名：" << endl;
									cin >> p->data.name;
								}
								break;
							}
						}
						break;
					case 3:
						thirdtag = 1;
						while (thirdtag)
						{
							cout << "==============================" << endl;
							cout << "请问您要改哪本书？" << endl;
							cout << "1.根据书号查找" << endl;
							cout << "2.根据名字查找" << endl;
							cout << "0.退出查找" << endl;
							cout << "==============================" << endl;
							cin >> thirdtag;

							LinkList p;
							switch (thirdtag)
							{
							case 1:
								cout << "请输入你要查询的书号：" << endl;
								cin >> no;
								p = BookNoLocate(bookstack, no);
								if (!p)
									cout << "抱歉，本书库没有您要找的那本书" << endl;
								else
								{
									cout << "请输入你要修改的价格：" << endl;
									cin >> p->data.price;
								}
								break;
							case 2:
								cout << "请输入你要查询的书名：" << endl;
								cin >> name;
								p = BookNameLocate(bookstack, name);
								if (!p)
									cout << "抱歉，本书库没有您要找的那本书" << endl;
								else
								{
									cout << "请输入你要修改的价格：" << endl;
									cin >> p->data.price;
								}
								break;
							}
						}
						break;
					case 4:
						thirdtag = 1;
						while (thirdtag)
						{
							cout << "==============================" << endl;
							cout << "请问您要删除哪本书？" << endl;
							cout << "1.根据书号查找" << endl;
							cout << "2.根据名字查找" << endl;
							cout << "0.退出查找" << endl;
							cout << "==============================" << endl;
							cin >> thirdtag;

							LinkList p;
							switch (thirdtag)
							{
							case 1:
								cout << "请输入你要查询的书号：" << endl;
								cin >> no;
								p = BookNoLocate(bookstack, no);
								if (!p)
									cout << "抱歉，本书库没有您要找的那本书" << endl;
								else
								{
									status = DeleteLinkList(bookstack, p);
									if (!status)
										cout << "删除失败" << endl;
								}
								break;
							case 2:
								cout << "请输入你要查询的书名：" << endl;
								cin >> name;
								p = BookNameLocate(bookstack, name);
								if (!p)
									cout << "抱歉，本书库没有您要找的那本书" << endl;
								else
								{
									status = DeleteLinkList(bookstack, p);
									if (!status)
										cout << "删除失败" << endl;
								}
								break;
							}
						}
						break;
					}
				}
				break;
			}
			else
			{
				cout << "书库为空！" << endl;
				break;
			}
		case 5:
			isempty = IsEmpty(bookstack);
			if (isempty)
			{
				tag = 1;
				while (tag)
				{
					char no[20] = { 0 };
					char name[50] = { 0 };
					float minprice = 0;
					float maxprice = 0;

					cout << "==============================" << endl;
					cout << "请问您要找哪本书？" << endl;
					cout << "1.根据书号查找" << endl;
					cout << "2.根据名字查找" << endl;
					cout << "3.根据价格查找" << endl;
					cout << "0.退出查找" << endl;
					cout << "==============================" << endl;
					cin >> tag;

					LinkList p;
					switch (tag)
					{
					case 1:
						cout << "请输入你要查询的书号：" << endl;
						cin >> no;
						p = BookNoLocate(bookstack, no);
						if (!p)
							cout << "抱歉，本书库没有您要找的那本书" << endl;
						else
							cout << "找到了！" << " 本书名字是：" << p->data.name << " 价格是：" << setiosflags(ios::fixed) << setprecision(2) << p->data.price << endl;
						break;
					case 2:
						cout << "请输入你要查询的书名：" << endl;
						cin >> name;
						p = BookNameLocate(bookstack, name);
						if (!p)
							cout << "抱歉，本书库没有您要找的那本书" << endl;
						else
							cout << "找到了！" << " 本书书号是：" << p->data.no << " 价格是：" << setiosflags(ios::fixed) << setprecision(2) << p->data.price << endl;
						break;
					case 3:
						cout << "请输入价格下限：" << endl;
						cin >> minprice;
						cout << "请输入价格上限：" << endl;
						cin >> maxprice;
						status = BookPriceLocate(bookstack, minprice, maxprice);
						if (!status)
							cout << "抱歉，本书库没有您要找的那本书" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "书库为空！" << endl;
				break;
			}
		case 6:
			isempty = IsEmpty(bookstack);
			if (isempty)
			{
				tag = 1;
				while (tag)
				{
					cout << "==============================" << endl;
					cout << "请选择插入方式：" << endl;
					cout << "1.指定位置插入" << endl;
					cout << "2.直接放在最后" << endl;
					cout << "0.退出插入模式" << endl;
					cin >> tag;
					int i = 0;
					switch (tag)
					{
					case 1:

						cout << "==============================" << endl;
						cout << "请输入插入位置：" << endl;
						cin >> i;
						cout << "请输入书籍信息（书号 书名 价格）：" << endl;
						cin >> book.no >> book.name >> book.price;
						status = InsertLinkList(bookstack, i, book);
						if (!status)
							cout << "插入失败" << endl;
						break;
					case 2:
						cout << "==============================" << endl;
						cout << "请输入书籍信息（书号 书名 价格）：" << endl;
						cin >> book.no >> book.name >> book.price;
						status = InputBook(bookstack, book);
						if (!status)
							cout << "插入失败" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "书库为空！" << endl;
				break;
			}
		case 7:
			isempty = IsEmpty(bookstack);
			if (isempty)
			{
				status = DeleteSame(bookstack);
				if (!status)
					cout << "去重失败" << endl;
			}
			else
			{
				cout << "书库为空！" << endl;
				break;
			}
		}
	}

	cout << "退出系统请输入0:" << endl;
	cin >> choose;
	if (choose == 0)
		return 0;
}
```

# here is some books you can put in
```
9787302257646 程序设计基础 25.00
9787302164340 程序设计基础（第2版） 20.00
9787302219972 单片机技术及应用 32.00
9787302203513 单片机原理与应用技术 26.00
9787810827430 工业计算机控制技术——原理与应用 29.00
9787811234923 汇编语言程序设计教程 21.00
0 0 0
```

welcome to comment!
