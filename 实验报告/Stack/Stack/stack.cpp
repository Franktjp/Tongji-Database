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

class linear_Stack
{
private:
	typedef struct SNode
	{
		ElemType data;
		SNode *pre, *nxt;
	}SNode, *stack;
	stack Top, Base;
public:
	linear_Stack();
	~linear_Stack();
	Status clear();

	Status empty() const;
	Status push(const ElemType);
	Status pop(ElemType &);
	ElemType top();
};
linear_Stack::linear_Stack()
{
	stack s = new(nothrow) SNode;
	if (s == NULL)
	{
		puts("No Free Memory");
		exit(Overflow);
	}
	Top = Base = s;
	Top->pre = Top->nxt = NULL;
}
linear_Stack::~linear_Stack()
{
	while (Top != NULL)
	{
		stack p = Top->pre;
		delete Top;
		Top = p;
	}
}
Status linear_Stack::clear()
{
	while (Top != Base)
	{
		stack p = Top->pre;
		delete Top;
		Top = p;
	}
	Top->nxt = NULL;
	return OK;
}
Status linear_Stack::empty()const
{
	return Top == Base;
}
Status linear_Stack::push(const ElemType x)
{
	stack s = new(nothrow) SNode;
	if (s == NULL)
	{
		puts("No Free Memory");
		exit(Overflow);
	}
	s->pre = Top;
	s->nxt = NULL;
	Top->nxt = s;
	Top = s;
	Top->data = x;
	return OK;
}
Status linear_Stack::pop(ElemType &res)
{
	if (Top == Base)
		return ERROR;
	res = Top->data;
	stack s = Top->pre;
	delete Top;
	Top = s;
	Top->nxt = NULL;
	return OK;
}
ElemType linear_Stack::top()
{
	if (Top == Base)
		return INT_MAX;
	return Top->data;
}

class SQ_Stack
{
private:
	struct Stack
	{
		ElemType *data;
		int top, size;

		void ReNew_S();
	}S;
public:
	SQ_Stack();
	~SQ_Stack();
	Status clear();

	Status empty() const;
	Status push(const ElemType);
	Status pop(ElemType &);
	ElemType top();
};
void SQ_Stack::Stack::ReNew_S()
{
	ElemType *New = new(nothrow) ElemType[size + Block_L];
	if (New == NULL)
	{
		puts("No more free memory");
		exit(-1);
	}
	memcpy(New, data, size * sizeof(ElemType));
	delete[]data;
	data = New;
	size += Block_L;
}
SQ_Stack::SQ_Stack()
{
	S.data = new(nothrow) ElemType[Initial_L]{ 0 };
	if (S.data == NULL)
		exit(Overflow);
	S.size = Initial_L;
	S.top = 0;
}
SQ_Stack::~SQ_Stack()
{
	delete[]S.data;
	S.size = S.top = 0;
}
Status SQ_Stack::clear()
{
	S.top = 0;
	return OK;
}
Status SQ_Stack::empty()const
{
	return !S.top;
}
Status SQ_Stack::push(const ElemType x)
{
	if (S.top == S.size)
		S.ReNew_S();
	S.data[S.top++] = x;
	return OK;
}
Status SQ_Stack::pop(ElemType &res)
{
	if (!S.top)
		return ERROR;
	res = S.data[--S.top];
	return OK;
}
ElemType SQ_Stack::top()
{
	if (!S.top)
		return INT_MAX;
	return S.data[S.top - 1];
}


void test_part()
{
#define For(i,l,r) for(int i=l;i<=r;++i)
#define Pause while(_getch()!='\r')

	puts("/**********************/");
	puts("/*������ջ����ջ�Ĳ���*/");
	puts("/**********************/");
	puts("");

	linear_Stack S; SQ_Stack tS;
	while (1)
	{
		cout << "���ṩ���²���:" << endl;
		cout << "1.��ջ" << endl;
		cout << "2.��ջ" << endl;
		cout << "3.�ж�ջ�Ƿ�Ϊ��" << endl;
		cout << "4.��ȡջ��Ԫ�أ���ջΪ�ս�����INT_MAX��" << endl;
		cout << "5.���ջ" << endl;
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
			cout << "��������Ҫ��ջ��Ԫ�أ�";
			int x;
			cin >> x;
			S.push(x); tS.push(x);
			cout << "��ջ�������밴���������..."; Pause; puts(""); puts("");
			continue;
		}
		if (choose == 2)
		{
			int x = 0;
			Status res = S.pop(x);
			if (res == ERROR)
				puts("��ջ��ջʧ�ܣ�ջ����Ԫ��");
			else
				cout << "��ջ��ջ�ɹ���ȡ��Ԫ�أ�" << x << endl;
			x = 0;
			res = tS.pop(x);
			if (res == ERROR)
				puts("����ջ��ջʧ�ܣ�ջ����Ԫ��");
			else
				cout << "����ջ��ջ�ɹ���ȡ��Ԫ�أ�" << x << endl;
			cout << "��ջ�������밴���������..."; Pause; puts(""); puts("");
			continue;
		}
		if (choose == 3)
		{
			if (S.empty())
				cout << "��ǰ��ջΪ�գ�";
			else
				cout << "��ǰ��ջ��Ϊ�գ�";
			if (tS.empty())
				cout << "����ջΪ�գ��밴���������...";
			else
				cout << "����ջ��Ϊ�գ��밴���������...";
			Pause; puts(""); puts("");
			continue;
		}
		if (choose == 4)
		{
			cout << "��ǰ��ջ��Ԫ��ֵΪ" << S.top() <<
				"������ջ��Ԫ��ֵΪ" << tS.top() << " ���밴���������...";
			Pause; puts(""); puts("");
			continue;
		}
		if (choose == 5)
		{
			S.clear(); tS.clear();
			cout << "ջ��ճɹ����밴���������..."; Pause; puts(""); puts("");
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
