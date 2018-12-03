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

class linear_Queue
{
private:
	typedef struct QNode
	{
		ElemType data;
		QNode *nxt;
	}QNode, *queue;
	queue head, tail;
public:
	linear_Queue();
	~linear_Queue();
	Status clear();

	Status empty() const;
	Status push(const ElemType);
	Status pop(ElemType &);
	ElemType front()const;
};
linear_Queue::linear_Queue()
{
	queue q = new(nothrow) QNode;
	if (q == NULL)
	{
		puts("No Free Memory");
		exit(Overflow);
	}
	q->nxt = NULL;
	head = tail = q;
}
linear_Queue::~linear_Queue()
{
	while (head != NULL)
	{
		queue q = head->nxt;
		delete head;
		head = q;
	}
	head = tail = NULL;
}
Status linear_Queue::clear()
{
	while (head != tail)
	{
		queue q = head->nxt;
		delete head;
		head = q;
	}
	return OK;
}
Status linear_Queue::empty()const
{
	return head == tail;
}
Status linear_Queue::push(const ElemType x)
{
	queue q = new(nothrow) QNode;
	if (q == NULL)
	{
		puts("No Free Memory");
		exit(Overflow);
	}
	q->data = x;
	tail->nxt = q;
	q->nxt = NULL;
	tail = q;
	return OK;
}
Status linear_Queue::pop(ElemType &res)
{
	if (head == tail)
		return ERROR;
	queue q = head->nxt;
	delete head;
	head = q;
	res = head->data;
	return OK;
}
ElemType linear_Queue::front()const
{
	if (head == tail)
		return INT_MAX;
	return head->nxt->data;
}

class SQ_Queue
{
private:
	struct Queue
	{
		ElemType *data;
		int head, tail, size;

		void ReNew_S();
	}S;
public:
	SQ_Queue();
	~SQ_Queue();
	Status clear();

	Status empty() const;
	Status push(const ElemType);
	Status pop(ElemType &);
	ElemType front()const;
};
void SQ_Queue::Queue::ReNew_S()
{
	ElemType *New = new(nothrow) ElemType[size + Block_L]{ 0 };
	if (New == NULL)
	{
		puts("No more free memory");
		exit(-1);
	}
	memcpy(New, data, sizeof(ElemType)*tail);
	int j = size + Block_L;
	for (int i = size - 1; i >= head; --i)
		New[--j] = data[i];
	head = j;
	delete[]data;
	data = New;
	size += Block_L;
}
SQ_Queue::SQ_Queue()
{
	S.data = new(nothrow) ElemType[Initial_L]{ 0 };
	if (S.data == NULL)
		exit(Overflow);
	S.size = Initial_L;
	S.head = S.tail = 0;
}
SQ_Queue::~SQ_Queue()
{
	delete[]S.data;
	S.size = S.head = S.tail = 0;
}
Status SQ_Queue::clear()
{
	S.head = S.tail = 0;
	return OK;
}
Status SQ_Queue::empty()const
{
	return S.head == S.tail;
}
Status SQ_Queue::push(const ElemType x)
{
	S.data[S.tail++] = x;
	if (S.tail == S.size)
		S.tail = 0;
	if (S.head == S.tail)
		S.ReNew_S();
	return OK;
}
Status SQ_Queue::pop(ElemType &res)
{
	if (S.head == S.tail)
		return ERROR;
	res = S.data[S.head++];
	if (S.head == S.size)
		S.head = 0;
	return OK;
}
ElemType SQ_Queue::front()const
{
	if (S.head == S.tail)
		return INT_MAX;
	return S.data[S.head];
}


void test_part()
{
#define For(i,l,r) for(int i=l;i<=r;++i)
#define Pause while(_getch()!='\r')

	puts("/****************************/");
	puts("/*��ѭ����������ʽ���еĲ���*/");
	puts("/****************************/");
	puts("");

	linear_Queue S; SQ_Queue tS;
	while (1)
	{
		cout << "���ṩ���²���:" << endl;
		cout << "1.������" << endl;
		cout << "2.������" << endl;
		cout << "3.�ж϶����Ƿ�Ϊ��" << endl;
		cout << "4.��ȡ��ͷԪ�أ�������Ϊ�ս�����INT_MAX��" << endl;
		cout << "5.��ն���" << endl;
		cout << "0.�˳�" << endl;
		cout << "[0-5]";
		int choose;
		while (1)
		{
			choose = _getch();
			if (choose >= '0' && choose <= '5')
				break;
		}
		puts(""); choose -= 48;
		if (!choose)
			break;
		if (choose == 1)
		{
			cout << "��������Ҫ�����е�Ԫ�أ�";
			int x;
			cin >> x;
			S.push(x); tS.push(x);
			cout << "�����н������밴���������..."; Pause; puts(""); puts("");
			continue;
		}
		if (choose == 2)
		{
			int x = 0;
			Status res = S.pop(x);
			if (res == ERROR)
				puts("��ʽ���г�����ʧ�ܣ�ջ����Ԫ��");
			else
				cout << "��ʽ���г����гɹ���ȡ��Ԫ�أ�" << x << endl;
			x = 0;
			res = tS.pop(x);
			if (res == ERROR)
				puts("ѭ�����г�����ʧ�ܣ�ջ����Ԫ��");
			else
				cout << "ѭ�����г����гɹ���ȡ��Ԫ�أ�" << x << endl;
			cout << "�����н������밴���������..."; Pause; puts(""); puts("");
			continue;
		}
		if (choose == 3)
		{
			if (S.empty())
				cout << "��ǰ��ʽ����Ϊ�գ�";
			else
				cout << "��ǰ��ʽ���в�Ϊ�գ�";
			if (tS.empty())
				cout << "ѭ������Ϊ�գ��밴���������...";
			else
				cout << "ѭ�����в�Ϊ�գ��밴���������...";
			Pause; puts(""); puts("");
			continue;
		}
		if (choose == 4)
		{
			cout << "��ǰ��ʽ����ͷԪ��ֵΪ" << S.front() <<
				"��ѭ������ͷԪ��ֵΪ" << tS.front() << " ���밴���������...";
			Pause; puts(""); puts("");
			continue;
		}
		if (choose == 5)
		{
			S.clear(); tS.clear();
			cout << "������ճɹ����밴���������..."; Pause; puts(""); puts("");
			continue;
		}
	}
	cout << "���Խ������밴���������..."; Pause; puts(""); puts("");
}

int main()
{
	/*test_part*/
	test_part();
	/***********/


	return 0;
}
