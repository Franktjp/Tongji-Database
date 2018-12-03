#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define Overflow 2

using namespace std;

typedef int Status;
typedef int ElemType;

class Linear_List
{
private:
	typedef struct LNode
	{
		ElemType data;
		LNode *pre;
		LNode *nxt;
	} LNode, *LinkList;
	LinkList L, tail;
public:
	/*************/
	/*common part*/
	/*************/
	Linear_List();
	~Linear_List();

	Status clear();
	Status empty() const;
	int length() const;

	Status del(const ElemType);
	Status del(const int, ElemType &);
	Status del_all(const ElemType);
	Status del_same();

	Status search(const ElemType, int &) const;
	Status reverse();
	Status output() const;

	/******************/
	/*only for ordered*/
	/******************/
	Status insert(const ElemType);
	Status Union(const Linear_List&, const Linear_List&);

	/********************/
	/*only for unordered*/
	/********************/
	Status insert(const int, const ElemType);
};

Linear_List::Linear_List()
{
	L = new(nothrow) LNode;
	if (L == NULL)
		exit(Overflow);
	L->pre = L->nxt = NULL;
	tail = L;
}
Linear_List::~Linear_List()
{
	LinkList p = L, q;
	while (p != NULL)
		q = p->nxt, delete p, p = q;
	L = tail = NULL;
}

Status Linear_List::clear()
{
	LinkList p = L->nxt, q;
	while (p != NULL)
		q = p->nxt, delete p, p = q;
	L->nxt = L->pre = NULL;
	tail = L;
	return OK;
}
Status Linear_List::empty() const
{
	return tail == NULL;
}
int Linear_List::length() const
{
	LinkList p = L->nxt;
	int res = 0;
	while (p != NULL)
		++res, p = p->nxt;
	return res;
}

Status Linear_List::del(const ElemType x)
{
	LinkList p = L->nxt;
	while (p != NULL)
	{
		if (p->data == x)
		{
			p->pre->nxt = p->nxt;
			if (p != tail)
				p->nxt->pre = p->pre;
			else
				tail = p->pre;
			delete p;
			return OK;
		}
		p = p->nxt;
	}
	return ERROR;
}
Status Linear_List::del(const int i, ElemType &res)
{
	LinkList p = L->nxt;
	int pos = 1;
	while (p != NULL && pos < i)
		p = p->nxt, ++pos;
	if (p == NULL || pos > i)
		return ERROR;
	res = p->data;
	p->pre->nxt = p->nxt;
	if (p != tail)
		p->nxt->pre = p->pre;
	else
		tail = p->pre;
	delete p;
	return OK;
}
Status Linear_List::del_all(const ElemType x)
{
	LinkList p = L->nxt, q;
	Status exist = 0;
	while (p != NULL)
	{
		q = p->nxt;
		if (p->data == x)
		{
			p->pre->nxt = p->nxt;
			if (p != tail)
				p->nxt->pre = p->pre;
			else
				tail = p->pre;
			delete p;
			exist = 1;
		}
		p = q;
	}
	return exist;
}
Status Linear_List::del_same()
{
	LinkList cur = L->nxt, p, q;
	while (cur != NULL)
	{
		p = cur->nxt;
		while (p != NULL)
		{
			q = p->nxt;
			if (p->data == cur->data)
			{
				p->pre->nxt = p->nxt;
				if (p != tail)
					p->nxt->pre = p->pre;
				else
					tail = p->pre;
				delete p;
			}
			p = q;
		}
		cur = cur->nxt;
	}
	return OK;
}

Status Linear_List::search(const ElemType x, int &pos) const
{
	LinkList p = L->nxt;
	pos = 1;
	while (p != NULL)
	{
		if (p->data == x)
			return OK;
		p = p->nxt, ++pos;
	}
	pos = -1;
	return ERROR;
}
Status Linear_List::reverse()
{
	if (tail == NULL)
		return ERROR;
	LinkList p = L->nxt, q = tail;
	ElemType tmp;
	while (p != q && p->pre != q)
	{
		tmp = p->data, p->data = q->data, q->data = tmp;
		p = p->nxt, q = q->pre;
	}
	return OK;
}
Status Linear_List::output() const
{
	cout << "=>";
	if (tail == L)
	{
		return ERROR;
	}
	LinkList p = L->nxt;
	while (p != tail)
		cout << p->data << "=>", p = p->nxt;
	cout << p->data;
	return OK;
}

Status Linear_List::insert(const ElemType x)
{
	LinkList p = L;
	while (p->nxt != NULL)
	{
		if (p->nxt->data >= x)
			break;
		p = p->nxt;
	}
	LinkList q = new(nothrow) LNode;
	if (q == NULL)
		exit(Overflow);
	q->data = x;
	q->pre = p;
	q->nxt = p->nxt;
	if (p == tail)
		tail = q;
	else
		p->nxt->pre = q;
	p->nxt = q;
	return OK;
}
Status Linear_List::Union(const Linear_List &A, const Linear_List &B)
{
	if (!empty())
		clear();
	LinkList p = A.L->nxt, q = B.L->nxt;
	LinkList tmp, cur;
	while (p != NULL)
	{
		if (p->data > q->data)
			tmp = p, p = q, q = tmp;
		cur = new(nothrow) LNode;
		if (cur == NULL)
			exit(Overflow);
		tail->nxt = cur, cur->pre = tail, cur->nxt = NULL;
		tail = cur;
		tail->data = p->data;
		p = p->nxt;
	}
	while (q != NULL)
	{
		cur = new(nothrow) LNode;
		if (cur == NULL)
			exit(Overflow);
		tail->nxt = cur, cur->pre = tail, cur->nxt = NULL;
		tail = cur;
		tail->data = q->data;
		q = q->nxt;
	}
	return OK;
}

Status Linear_List::insert(const int i, const ElemType x)
{
	LinkList p = L;
	int pos = 0;
	while (p != NULL && pos < i - 1)
		p = p->nxt, ++pos;
	if (p == NULL || pos > i - 1)
		return ERROR;
	LinkList q = new(nothrow) LNode;
	if (q == NULL)
		exit(Overflow);
	q->data = x;
	q->pre = p;
	q->nxt = p->nxt;
	if (p == tail)
		tail = q;
	else
		p->nxt->pre = q;
	p->nxt = q;
	return OK;
}


void unordered_test()
{
	Linear_List L;
	puts("/************************************/");
	puts("/*�������Ա�Ĳ��롢ɾ�������ҵȲ���*/");
	puts("/************************************/");
	puts("");
#define For(i,l,r) for(int i=l;i<=r;++i)
#define Pause while(_getch()!='\r')

	cout << "�������ʼ���ݸ��� n = ";
	int n;
	cin >> n;
	cout << "����������" << n << "������:" << endl;
	For(i, 1, n)
	{
		ElemType x;
		cin >> x;
		L.insert(i, x);
	}
	puts("��������Ա�������"); L.output(); puts("");
	cout << "�밴���������..."; Pause; puts(""); puts("");

	if (1)
	{
		ElemType x; int pos; Status res;
		puts("/*���Ա���Ҳ���*/");
		cout << "��������Ҫ���ҵ���ֵ x = "; cin >> x;
		res = L.search(x, pos);
		if (res)
			cout << "���ҵ���ֵ" << x << ",λ��Ϊ��" << pos << "��\n";
		else
			cout << "����ʧ�ܣ���ֵ������" << endl;
		cout << "�밴���������..."; Pause; puts(""); puts("");
	}

	if (1)
	{
		int pos; ElemType x;

		puts("/*ͷ����ԣ������ڱ�ͷ�������� 1 */");
		L.insert(1, 1);
		puts("���Ա��״̬����"); L.output(); puts("");
		cout << "�밴���������..."; Pause; puts(""); puts("");

		puts("/*β����ԣ������ڱ�β�������� -1 */");
		L.insert(L.length() + 1, -1);
		puts("���Ա��״̬����"); L.output(); puts("");
		cout << "�밴���������..."; Pause; puts(""); puts("");

		puts("/*�Զ���������*/");
		cout << "������ϣ�������λ�� pos ������ x : "; cin >> pos >> x;
		L.insert(pos, x);
		puts("���Ա��״̬����"); L.output(); puts("");
		cout << "�밴���������..."; Pause; puts(""); puts("");
	}

	if (1)
	{
		ElemType x; int pos; Status res;
		if (1)
		{
			puts("/*ͷɾ���ԣ�����ɾ����ͷ����*/");
			res = L.del(1, x);
			if (res)
				cout << "ɾ���ɹ���ɾ��������Ϊ��" << x << endl;
			else
				cout << "ɾ��ʧ�ܣ���λ�ò��Ϸ�" << endl;
			puts("���Ա��״̬����"); L.output(); puts("");
			cout << "�밴���������..."; Pause; puts(""); puts("");

			puts("/*βɾ���ԣ�����ɾ����β����*/");
			res = L.del(L.length(), x);
			if (res)
				cout << "ɾ���ɹ���ɾ��������Ϊ��" << x << endl;
			else
				cout << "ɾ��ʧ�ܣ���λ�ò��Ϸ�" << endl;
			puts("���Ա��״̬����"); L.output(); puts("");
			cout << "�밴���������..."; Pause; puts(""); puts("");
		}
		if (1)
		{
			puts("/*�Զ���λ��ɾ������*/");
			cout << "������ϣ��ɾ����λ�� pos = "; cin >> pos;
			res = L.del(pos, x);
			if (res)
				cout << "ɾ���ɹ���ɾ��������Ϊ��" << x << endl;
			else
				cout << "ɾ��ʧ�ܣ���λ�ò��Ϸ�" << endl;
			puts("���Ա��״̬����"); L.output(); puts("");
			cout << "�밴���������..."; Pause; puts(""); puts("");
		}
		if (1)
		{
			puts("/*�Զ�����ֵɾ������*/");
			cout << "������ϣ��ɾ������ֵ x = "; cin >> x;
			res = L.del(x);
			if (res)
				cout << "ɾ���ɹ���ɾ��������Ϊ��" << x << endl;
			else
				cout << "ɾ��ʧ�ܣ�����ֵ������" << endl;
			puts("���Ա��״̬����"); L.output(); puts("");
			cout << "�밴���������..."; Pause; puts(""); puts("");
		}
	}

	if (1)
	{
		ElemType x; Status res;
		puts("/*ɾ������ֵx����*/");
		puts("��ǰ���Ա�״̬Ϊ"); L.output(); puts("");
		cout << "��������Ҫȫ��ɾ������ֵ x = "; cin >> x;
		res = L.del_all(x);
		if (res)
			puts("ɾ���ɹ�����ǰ���Ա�״̬Ϊ"), L.output(), puts("");
		else
			puts("ɾ��ʧ�ܣ�����ֵ������");
		cout << "�밴���������..."; Pause; puts(""); puts("");

		puts("/*ȥ�ز���*/");
		puts("��ǰ���Ա�״̬Ϊ"); L.output(); puts("");
		L.del_same();
		puts("ȥ�غ����Ա�״̬Ϊ"); L.output(); puts("");
		cout << "�밴���������..."; Pause; puts(""); puts("");
	}

	if (1)
	{
		puts("/*���Ա�ķ�ת����*/");
		puts("��ǰ���Ա�״̬Ϊ"); L.output(); puts("");
		L.reverse();
		puts("�����Ա�ת��״̬Ϊ"); L.output(); puts("");
		cout << "�밴���������..."; Pause; puts(""); puts("");
	}
	puts(""); puts("");

	if (1)
	{
		puts("/*���Ա����ղ���*/");
		puts("��ǰ���Ա�״̬Ϊ"); L.output(); puts("");
		L.clear();
		puts("�����Ա���պ�״̬Ϊ"); L.output(); puts("");
		cout << "�밴���������..."; Pause; puts(""); puts("");
	}
	puts(""); puts("");
	puts("**************************************************");
	puts("*���򲿷ֲ�����ϣ����½����������Ա�����������*");
	puts("**************************************************");
	cout << "�밴���������..."; Pause; puts(""); puts(""); puts(""); puts("");
}
void ordered_test()
{
	Linear_List LA, LB, LC;
	puts("/******************/");
	puts("/*�������Ա�Ĳ���*/");
	puts("/******************/");
	puts("");
	int n;

#define For(i,l,r) for(int i=l;i<=r;++i)
#define Pause while(_getch()!='\r')

	cout << "���������Ա�A��ʼ���ݸ��� n = ";
	cin >> n;
	cout << "����������" << n << "���ǵݼ�����:" << endl;
	For(i, 1, n)
	{
		ElemType x;
		cin >> x;
		LA.insert(i, x);
	}
	puts("LA��������"); LA.output(); puts("");
	cout << "�밴���������..."; Pause; puts("");

	cout << "���������Ա�B��ʼ���ݸ��� n = ";
	cin >> n;
	cout << "����������" << n << "���ǵݼ�����:" << endl;
	For(i, 1, n)
	{
		ElemType x;
		cin >> x;
		LB.insert(i, x);
	}
	puts("LB��������"); LB.output(); puts("");
	cout << "�밴���������..."; Pause; puts(""); puts("");

	if (1)
	{
		ElemType x;
		cout << "���LA���в������������һ����Ҫ�������ֵ x = "; cin >> x;
		LA.insert(x);
		puts("�����LA��״̬Ϊ"); LA.output(); puts("");
		cout << "�밴���������..."; Pause; puts(""); puts("");
	}
	if (1)
	{
		puts("/*�������Ա�ϲ�����*/");
		puts("LA״̬����"); LA.output(); puts("");
		puts("LB״̬����"); LB.output(); puts("");
		LC.Union(LA, LB);
		puts("����ϲ�LA��LB��LC��LC״̬����"); LC.output(); puts("");
		cout << "�밴���������..."; Pause; puts(""); puts("");
	}

	puts(""); puts("");
	puts("**********************");
	puts("*�������ⲿ�ֲ������*");
	puts("**********************");
	cout << "�밴���������..."; Pause; puts(""); puts(""); puts(""); puts("");
}

void test_part()
{
	if (1)
		unordered_test();
	if (1)
		ordered_test();
}

int main()
{
	/*test_part*/
	test_part();
	/***********/

	return 0;
}
