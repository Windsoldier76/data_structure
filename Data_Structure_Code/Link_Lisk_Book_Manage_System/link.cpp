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

//����ͼ��
typedef struct
{
	char no[20];        //ͼ�����
	char name[50];      //ͼ������
	float price;        //ͼ��۸�
}Book;

//��������
typedef struct LNode
{
	Book data;             //�ڵ��������
	struct LNode *next;    //�ڵ��ָ����
}LNode, *LinkList;

//���������Ƿ�Ϊ��
Status IsEmpty(LinkList L)
{
	if (L)
		return OK;
	else
		return ERROR;
}

//�����ձ�
Status CreateLinkList(LinkList &L)
{//�������������һ���µ�����
	L = new LNode;   //�����½����Ϊͷ��㣬��ͷָ��Lָ��ͷ���
	L->next = NULL;  //��ͷ����ָ�����ÿ�
	return OK;
}

//�����µ�ͼ������
Status InsertLinkList(LinkList L, int i, Book b)
{//��ʼ����������L���ڣ�1<=i<=ListLength+1
 //�����������L�е�i��λ�ò����µ�����b
	LinkList p, q;
	int j = 0;
	p = L;
	while (p && j < i - 1)  //pɨ������ָ���i��λ��
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)    //iֵ�Ƿ��򳬳���󳤶�
		return ERROR;
	q = new LNode;         //Ϊb�����µĽ��
	q->data = b;           //��b�����½��������
	q->next = p->next;     //�½��ָ����ָ���i+1λ�õĽ��
	p->next = q;           //��i-1λ�õĽ��ָ���½��
	return OK;
}

//ɾ���ɵ�ͼ������
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

//ISBN����
LNode *BookNoLocate(LinkList L, char c[])
{
	LinkList p = L->next;     //ɨ����ָ��
	while (p && strcmp(p->data.no, c))  //ɨ��
		p = p->next;
	return p;   			  //���ؽ��
}

//���Ʋ���
LNode *BookNameLocate(LinkList L, char c[])
{
	LinkList p = L->next;     //ɨ����ָ��
	while (p && strcmp(p->data.name, c))  //ɨ��
		p = p->next;
	return p;   			  //���ؽ��
}

//�۸����
Status BookPriceLocate(LinkList L, float min, float max)
{
	LinkList p = L;
	int ct = 0;
	p = L->next;     //ɨ����ָ��
	while (p)
	{
		if (p->data.price>=min&&p->data.price<=max)
		{
			cout << "�ҵ��˷�����������" << " ����ǣ�" << p->data.no << " �����ǣ�" << p->data.name << " �۸��ǣ�" << setiosflags(ios::fixed) << setprecision(2) << p->data.price << endl;
			++ct;
		}
		p = p->next;
	}
	if (!p && !ct)
		return ERROR;
	else
		return OK;

}

//��������
Status InputBook(LinkList L, Book b)
{//��ʼ�������������
 //������������������һ����㴦����һ����㣬������b����
	LinkList p = L;
	while (p->next)   //ɨ������λ�����һ�����
		p = p->next;
	LinkList s = new LNode;  //�����½��
	s->data = b;			 //��ͼ�����ݴ����½��������
	s->next = NULL;			 //�½��ָ�����ÿ�
	p->next = s;			 //����β������½������
	return OK;
}

//�������
Status OutputBook(LinkList L)
{//��ʼ�������������
 //������������ͼ����Ϣ
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

//���ݼ۸�������
Status DescendingOrder(LinkList &L)
{//��ʼ�������������
 //������������ռ۸������
	LinkList p, p1, p2;
	int count = 0;       //��¼������
	p = L;
	p1 = p->next;
	p2 = p->next->next;

	if (!p || !p1)       //��������
		return ERROR;
	if(!p2)              //������������
		cout << p1->data.no << " " << p1->data.name << " " << setiosflags(ios::fixed) << setprecision(2) << p1->data.price << endl;

	while (p2)
	{
		if (p1->data.price < p2->data.price)
		{
			p1->next = p2->next;       //p1�������p2����һ�����
			p2->next = p->next;        //p2�������p1
			p->next = p2;              //p�������p2
			p = p2;
			p2 = p1->next;
		}
		else
		{
			p = p->next;                   //���ɨ��
			p1 = p1->next;
			p2 = p2->next;
		}
		++count;                       //��¼����
	}

	//--count;                           //ѭ����������
	for (count; count > 0; count--)    //ð������
	{
		p = L;
		p1 = p->next;
		p2 = p1->next;
		for (int j = 0; j < count; j++)
		{
			if (p1->data.price < p2->data.price)
			{
				p1->next = p2->next;       //p1�������p2����һ�����
				p2->next = p->next;        //p2�������p1
				p->next = p2;              //p�������p2
				p = p2;
				p2 = p1->next;
			}
			else
			{
				p = p->next;                   //���ɨ��
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

//���۸���������
Status AscendingOrder(LinkList L)
{
	LinkList p, p1, p2;
	int count = 0;       //��¼������
	p = L;
	p1 = p->next;
	p2 = p1->next;

	if (!p || !p1)       //��������
		return ERROR;
	if (!p2)              //������������
		cout << p1->data.no << " " << p1->data.name << " " << setiosflags(ios::fixed) << setprecision(2) << p1->data.price << endl;

	while (p2)
	{
		if (p1->data.price > p2->data.price)
		{
			p1->next = p2->next;       //p1�������p2����һ�����
			p2->next = p->next;        //p2�������p1
			p->next = p2;              //p�������p2
			p = p2;
			p2 = p1->next;
		}
		else
		{
			p = p->next;                   //���ɨ��
			p1 = p1->next;
			p2 = p2->next;
		}
		++count;                       //��¼����
	}

	--count;                           //ѭ����������
	for (count; count > 0; count--)    //ð������
	{
		p = L;
		p1 = p->next;
		p2 = p1->next;
		for (int j = 0; j < count; j++)
		{
			if (p1->data.price > p2->data.price)
			{
				p1->next = p2->next;       //p1�������p2����һ�����
				p2->next = p->next;        //p2�������p1
				p->next = p2;              //p�������p2
				p = p2;
				p2 = p1->next;
			}
			else
			{
				p = p->next;                   //���ɨ��
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

//����洢���
Status ReverseOrder(LinkList L)
{//��ʼ�������������
 //������������������������
	LinkList p, p1, p2;
	int count = 0;       //��¼������
	p = L;
	p1 = p->next;
	p2 = p1->next;

	if (!p || !p1)       //��������
		return ERROR;
	if (!p2)              //������������
		cout << p1->data.no << " " << p1->data.name << " " << setiosflags(ios::fixed) << setprecision(2) << p1->data.price << endl;

	while (p2)
	{

		p1->next = p2->next;       //p1�������p2����һ�����
		p2->next = p->next;        //p2�������p1
		p->next = p2;              //p�������p2
		p = p2;                    //���ɨ��
		p2 = p1->next;

		++count;                       //��¼����
	}

	--count;                           //ѭ����������
	for (count; count > 0; count--)    //ð������
	{
		p = L;
		p1 = p->next;
		p2 = p1->next;
		for (int j = 0; j < count; j++)
		{
			p1->next = p2->next;       //p1�������p2����һ�����
			p2->next = p->next;        //p2�������p1
			p->next = p2;              //p�������p2
			p = p2;                    //���ɨ��
			p2 = p1->next;
		}
	}

	if (OutputBook(L))
		return OK;
	else
		return ERROR;
}

//ȥ��
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

//������
int main()
{
	int choose = 0;       //����û�һ��ѡ��

	//һ������
	cout << "==============================" << endl;
	cout << "��ӭʹ��Windͼ�����ϵͳ��" << endl;
	cout << "==============================" << endl;
	cout << "��ѡ������Ҫʹ�õ�ģʽ��" << endl;
	cout << "1.˳���ģʽ����δ���ţ�" << endl;
	cout << "2.����ģʽ" << endl;
	cout << "==============================" << endl;

	cin >> choose;

	system("cls");
	if (choose == 1)       //Ƥ��һ��
	{
		cout << "==============================" << endl;
		cout << "˵����δ���Ż�ѡ" << endl;
		cout << "�ð���֪����û��ѡ" << endl;
		cout << "�����Զ�ת������ģʽ..." << endl;
	}

	//��������
	cout << "==============================" << endl;
	cout << "���ѽ�������ģʽ" << endl;

	//����ȫ��ͨ�ñ���
	LinkList bookstack = NULL;  //ͼ����Ϣ����
	int listlength = 0;         //������
	int status = 0;             //���״̬��
	int isempty = 1;            //����������״̬
	int tag = 1;                //����û�����ѡ��
	int thirdtag = 1;           //����û�����ѡ��

	while (choose)
	{
		cout << "==============================" << endl;
		cout << "����������ʲô��" << endl;
		cout << "��ʾ��û����Ϣ���Ǻ���Ϣ" << endl;
		cout << "1.�������" << endl;
		cout << "2.����������������ʲô" << endl;
		cout << "3.������Ÿ���" << endl;
		cout << "4.������޸ĵ���Ϣ" << endl;
		cout << "5.�ҵ������ҵ���" << endl;
		cout << "6.�Ž���������" << endl;
		cout << "7.ȥ���ظ����鼮" << endl;
		cout << "0.�˳�����ģʽ" << endl;
		cout << "==============================" << endl;

		cin >> choose;

		cout << "==============================" << endl;

		switch (choose)
		{
		case 1:
			status = CreateLinkList(bookstack);     //��ʼ��������
			if (!status)
				cout << "��ʼ������ʧ��" << endl;
			Book book;                  //�½���ʱͼ����Ϣ����
			cout << "������ͼ����Ϣ" << endl;
			while (TRUE)
			{
				cin >> book.no >> book.name >> book.price;    //����ͼ����Ϣ
				if (book.price == 0)
					break;
				else
				{
					status = InputBook(bookstack, book);
					++listlength;
				}
			}
			if (!status)
				cout << "����ͼ����Ϣʧ��" << endl;
			break;
		case 2:
			isempty = IsEmpty(bookstack);
			if (isempty)
			{
				cout << listlength << endl;
				status = OutputBook(bookstack);
				if (!status)
					cout << "���ͼ����Ϣʧ��" << endl;
				break;
			}
			else
			{
				cout << "���Ϊ�գ�" << endl;
				break;
			}
		case 3:
			isempty = IsEmpty(bookstack);
			if (isempty)
			{
				LinkList p1, p2;      //������������copy
				while (tag)
				{
					LinkList copy;
					p1 = bookstack->next;       //p1ɨ���������
					CreateLinkList(copy);       //��ʼ����������
					p2 = copy;                  //p2ɨ�踴������
					LinkList s;

					while (p1)
					{
						s = new LNode;          //�����½��
						s->data = p1->data;     //����������
						s->next = NULL;         //�½��ָ�����ÿ�
						p2->next = s;           //�����½��
						p2 = s;                 //ɨ����һ������������
						p1 = p1->next;          //ɨ����һ�����������
					}

					if (!copy)
						cout << "�����ʼ��ʧ��" << endl;

					cout << "��ѡ������ʽ��" << endl;
					cout << "1.���۸���" << endl;
					cout << "2.���۸�����" << endl;
					cout << "3.��������" << endl;
					cout << "0.�˳�����ģʽ" << endl;
					cout << "==============================" << endl;

					cin >> tag;

					switch (tag)
					{
					case 1:
						status = DescendingOrder(copy);
						if (!status)
							cout << "����ʧ�ܣ�" << endl;
						delete copy;
						break;
					case 2:
						status = AscendingOrder(copy);
						if (!status)
							cout << "����ʧ�ܣ�" << endl;
						delete copy;
						break;
					case 3:
						status = ReverseOrder(copy);
						if (!status)
							cout << "����ʧ�ܣ�" << endl;
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
				cout << "���Ϊ�գ�" << endl;
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
					cout << "��������ı�������ˣ�" << endl;
					cout << "1.��Ŵ���" << endl;
					cout << "2.���ִ���" << endl;
					cout << "3.�۸����" << endl;
					cout << "4.��Ҫɾ����" << endl;
					cout << "0.�˳��޸�" << endl;
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
							cout << "������Ҫ���ı��飿" << endl;
							cout << "1.������Ų���" << endl;
							cout << "2.�������ֲ���" << endl;
							cout << "0.�˳�����" << endl;
							cout << "==============================" << endl;
							cin >> thirdtag;

							LinkList p;
							switch (thirdtag)
							{
							case 1:
								cout << "��������Ҫ��ѯ����ţ�" << endl;
								cin >> no;
								p = BookNoLocate(bookstack, no);
								if (!p)
									cout << "��Ǹ�������û����Ҫ�ҵ��Ǳ���" << endl;
								else
								{
									cout << "��������Ҫ�޸ĵ���ţ�" << endl;
									cin >> p->data.no;
								}
								break;
							case 2:
								cout << "��������Ҫ��ѯ��������" << endl;
								cin >> name;
								p = BookNameLocate(bookstack, name);
								if (!p)
									cout << "��Ǹ�������û����Ҫ�ҵ��Ǳ���" << endl;
								else
								{
									cout << "��������Ҫ�޸ĵ���ţ�" << endl;
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
							cout << "������Ҫ���ı��飿" << endl;
							cout << "1.������Ų���" << endl;
							cout << "2.�������ֲ���" << endl;
							cout << "0.�˳�����" << endl;
							cout << "==============================" << endl;
							cin >> thirdtag;

							LinkList p;
							switch (thirdtag)
							{
							case 1:
								cout << "��������Ҫ��ѯ����ţ�" << endl;
								cin >> no;
								p = BookNoLocate(bookstack, no);
								if (!p)
									cout << "��Ǹ�������û����Ҫ�ҵ��Ǳ���" << endl;
								else
								{
									cout << "��������Ҫ�޸ĵ�������" << endl;
									cin >> p->data.name;
								}
								break;
							case 2:
								cout << "��������Ҫ��ѯ��������" << endl;
								cin >> name;
								p = BookNameLocate(bookstack, name);
								if (!p)
									cout << "��Ǹ�������û����Ҫ�ҵ��Ǳ���" << endl;
								else
								{
									cout << "��������Ҫ�޸ĵ�������" << endl;
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
							cout << "������Ҫ���ı��飿" << endl;
							cout << "1.������Ų���" << endl;
							cout << "2.�������ֲ���" << endl;
							cout << "0.�˳�����" << endl;
							cout << "==============================" << endl;
							cin >> thirdtag;

							LinkList p;
							switch (thirdtag)
							{
							case 1:
								cout << "��������Ҫ��ѯ����ţ�" << endl;
								cin >> no;
								p = BookNoLocate(bookstack, no);
								if (!p)
									cout << "��Ǹ�������û����Ҫ�ҵ��Ǳ���" << endl;
								else
								{
									cout << "��������Ҫ�޸ĵļ۸�" << endl;
									cin >> p->data.price;
								}
								break;
							case 2:
								cout << "��������Ҫ��ѯ��������" << endl;
								cin >> name;
								p = BookNameLocate(bookstack, name);
								if (!p)
									cout << "��Ǹ�������û����Ҫ�ҵ��Ǳ���" << endl;
								else
								{
									cout << "��������Ҫ�޸ĵļ۸�" << endl;
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
							cout << "������Ҫɾ���ı��飿" << endl;
							cout << "1.������Ų���" << endl;
							cout << "2.�������ֲ���" << endl;
							cout << "0.�˳�����" << endl;
							cout << "==============================" << endl;
							cin >> thirdtag;

							LinkList p;
							switch (thirdtag)
							{
							case 1:
								cout << "��������Ҫ��ѯ����ţ�" << endl;
								cin >> no;
								p = BookNoLocate(bookstack, no);
								if (!p)
									cout << "��Ǹ�������û����Ҫ�ҵ��Ǳ���" << endl;
								else
								{
									status = DeleteLinkList(bookstack, p);
									if (!status)
										cout << "ɾ��ʧ��" << endl;
								}
								break;
							case 2:
								cout << "��������Ҫ��ѯ��������" << endl;
								cin >> name;
								p = BookNameLocate(bookstack, name);
								if (!p)
									cout << "��Ǹ�������û����Ҫ�ҵ��Ǳ���" << endl;
								else
								{
									status = DeleteLinkList(bookstack, p);
									if (!status)
										cout << "ɾ��ʧ��" << endl;
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
				cout << "���Ϊ�գ�" << endl;
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
					cout << "������Ҫ���ı��飿" << endl;
					cout << "1.������Ų���" << endl;
					cout << "2.�������ֲ���" << endl;
					cout << "3.���ݼ۸����" << endl;
					cout << "0.�˳�����" << endl;
					cout << "==============================" << endl;
					cin >> tag;

					LinkList p;
					switch (tag)
					{
					case 1:
						cout << "��������Ҫ��ѯ����ţ�" << endl;
						cin >> no;
						p = BookNoLocate(bookstack, no);
						if (!p)
							cout << "��Ǹ�������û����Ҫ�ҵ��Ǳ���" << endl;
						else
							cout << "�ҵ��ˣ�" << " ���������ǣ�" << p->data.name << " �۸��ǣ�" << setiosflags(ios::fixed) << setprecision(2) << p->data.price << endl;
						break;
					case 2:
						cout << "��������Ҫ��ѯ��������" << endl;
						cin >> name;
						p = BookNameLocate(bookstack, name);
						if (!p)
							cout << "��Ǹ�������û����Ҫ�ҵ��Ǳ���" << endl;
						else
							cout << "�ҵ��ˣ�" << " ��������ǣ�" << p->data.no << " �۸��ǣ�" << setiosflags(ios::fixed) << setprecision(2) << p->data.price << endl;
						break;
					case 3:
						cout << "������۸����ޣ�" << endl;
						cin >> minprice;
						cout << "������۸����ޣ�" << endl;
						cin >> maxprice;
						status = BookPriceLocate(bookstack, minprice, maxprice);
						if (!status)
							cout << "��Ǹ�������û����Ҫ�ҵ��Ǳ���" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "���Ϊ�գ�" << endl;
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
					cout << "��ѡ����뷽ʽ��" << endl;
					cout << "1.ָ��λ�ò���" << endl;
					cout << "2.ֱ�ӷ������" << endl;
					cout << "0.�˳�����ģʽ" << endl;
					cin >> tag;
					int i = 0;
					switch (tag)
					{
					case 1:

						cout << "==============================" << endl;
						cout << "���������λ�ã�" << endl;
						cin >> i;
						cout << "�������鼮��Ϣ����� ���� �۸񣩣�" << endl;
						cin >> book.no >> book.name >> book.price;
						status = InsertLinkList(bookstack, i, book);
						if (!status)
							cout << "����ʧ��" << endl;
						break;
					case 2:
						cout << "==============================" << endl;
						cout << "�������鼮��Ϣ����� ���� �۸񣩣�" << endl;
						cin >> book.no >> book.name >> book.price;
						status = InputBook(bookstack, book);
						if (!status)
							cout << "����ʧ��" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "���Ϊ�գ�" << endl;
				break;
			}
		case 7:
			isempty = IsEmpty(bookstack);
			if (isempty)
			{
				status = DeleteSame(bookstack);
				if (!status)
					cout << "ȥ��ʧ��" << endl;
			}
			else
			{
				cout << "���Ϊ�գ�" << endl;
				break;
			}
		}
	}

	cout << "�˳�ϵͳ������0:" << endl;
	cin >> choose;
	if (choose == 0)
		return 0;
}
