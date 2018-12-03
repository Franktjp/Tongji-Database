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
#define Initial_L 10 /////////////////////////
#define Block_L 10

using namespace std;

typedef int Status;
typedef int ElemType;

class SQList
{
private:
#define For(i,l,r) for(int i=l;i<=r;++i)
#define sFor(i,l,r) for(int i=l;i<r;++i)
#define opFor(i,r,l) for(int i=r;i>=l;--i)
	const ElemType Lazy = 2147483647;

	struct LinkList
	{
		ElemType *data;
		int length, size;

		void ReNew_L();
	}L;
public:
	/*************/
	/*common part*/
	/*************/
	SQList();
	~SQList();
	void reset(const int);

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
	Status Union(const SQList&, const SQList&);

	/********************/
	/*only for unordered*/
	/********************/
	Status insert(const int, const ElemType);
};

void SQList::LinkList::ReNew_L()
{
	ElemType *New = new(nothrow) ElemType[length + Block_L];
	if (New == NULL)
	{
		puts("No more free memory");
		exit(-1);
	}
	memcpy(New, data, length * sizeof(ElemType));
	delete[]data;
	data = New;
	length += Block_L;
}

SQList::SQList()
{
	L.data = new(nothrow) ElemType[Initial_L]{0};
	if (L.data == NULL)
		exit(Overflow);
	L.size = Initial_L;
	L.length = 0;
}
SQList::~SQList()
{
	delete[]L.data;
	L.size = L.length = 0;
}
void SQList::reset(const int size)
{
	if (L.size)
	{
		delete[]L.data;
		L.size = L.length = 0;
	}

	L.data = new(nothrow) ElemType[size]{ 0 };
	if (L.data == NULL)
		exit(Overflow);
	L.size = size;
	L.length = 0;
}

Status SQList::clear()
{
	L.length = 0;
	return 0;
}
Status SQList::empty() const
{
	return L.length != 0;
}
int SQList::length() const
{
	return L.length;
}

Status SQList::del(const ElemType x)
{
	sFor(i,0,L.length)
		if (L.data[i] == x)
		{
			sFor(j, i, L.length)
				L.data[j] = L.data[j + 1];
			--L.length;
			return OK;
		}
	return ERROR;
}
Status SQList::del(const int i, ElemType &res)
{
	if (i > L.length || i < 1)
		return ERROR;
	res = L.data[i - 1];
	sFor(j, i - 1, L.length)
		L.data[j] = L.data[j + 1];
	--L.length;
	return OK;
}
Status SQList::del_all(const ElemType x)
{
	Status find = 0;
	sFor(i, 0, L.length)
	{
		if (L.data[i] != x)
			continue;
		find = 1;
		L.data[i] = Lazy;
	}
	if (!find)
		return ERROR;
	int l = 0, r;
	while (L.data[l] != Lazy) ++l; r = l + 1;
	while (r < L.length)
	{
		while (L.data[r] != Lazy && r < L.length)
			L.data[l++] = L.data[r++];
		++r;
	}
	L.length = l;
	return OK;
}
Status SQList::del_same()
{
	const int Maxa = 10000;
	bool f[Maxa + 10] = {0};
	sFor(i, 0, L.length)
		if (!f[L.data[i]])
			f[L.data[i]] = 1;
		else
			L.data[i] = Lazy;
	int l = 0, r;
	while (L.data[l] != Lazy) ++l; r = l + 1;
	while (r < L.length)
	{
		while (L.data[r] != Lazy && r < L.length)
			L.data[l++] = L.data[r++];
		++r;
	}
	L.length = l;
	return OK;
}

Status SQList::search(const ElemType x, int &pos) const
{
	sFor(i, 0, L.length)
		if (L.data[i] == x)
		{
			pos = i + 1;
			return OK;
		}
	return ERROR;
}
Status SQList::reverse()
{
	int l = 0, r = L.length - 1;
	ElemType tmp;
	while (l < r)
		tmp = L.data[l], L.data[l] = L.data[r], L.data[r] = tmp,
		++l, --r;
	return OK;
}
Status SQList::output() const
{
	cout << "=>";
	if (!L.length)
		return ERROR;
	sFor(i, 0, L.length - 1)
		cout << L.data[i] << "=>";
	cout << L.data[L.length-1];
	return OK;
}

Status SQList::insert(const ElemType x)
{
	if (L.length == L.size)
		L.ReNew_L();
	int pos = L.length + 1;
	sFor(i, 0, L.length)
		if (L.data[i] >= x)
		{
			pos = i + 1;
			break;
		}

	opFor(i, L.length - 1, pos - 1)
		L.data[i + 1] = L.data[i];
	L.data[pos - 1] = x;
	++L.length;
	return pos;
}
Status SQList::Union(const SQList &A, const SQList &B)
{
	if (!empty())
		reset(A.L.length + B.L.length + 10);
	sFor(i, 0, A.L.length)
		insert(A.L.data[i]);
	sFor(i, 0, B.L.length)
		insert(B.L.data[i]);

	return OK;
}

Status SQList::insert(const int i, const ElemType x)
{
	if (i<1 || i>L.length + 1)
		return ERROR;
	if (L.length == L.size)
		L.ReNew_L();
	opFor(j, L.length - 1, i - 1)
		L.data[j + 1] = L.data[j];
	L.data[i - 1] = x;
	++L.length;
	return OK;
}

void unordered_test()
{
	SQList L;
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
	SQList LA, LB, LC;
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
