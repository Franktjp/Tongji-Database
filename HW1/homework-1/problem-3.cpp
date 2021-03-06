#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define For(i,l,r) for(int i=l; i<=r; ++i)
#define sFor(i,l,r) for(int i=l; i<r; ++i)
#define opFor(i,r,l) for(int i=r; i>=l; --i)
#define OK 1
#define ERROR 0
#define START_LENGTH 100
#define NEW_LENGTH 10

using namespace std;

typedef int ElemType;
typedef int Statue;

class SQList
{
public:
	struct LinkList
	{
		ElemType *elem;
		int length, tail;
	} L;
	void ReNew_L()
	{
		ElemType *New = new(nothrow) ElemType[L.length + NEW_LENGTH];
		if (New == NULL)
		{
			puts("No more free memory");
			exit(-1);
		}
		memcpy(New, L.elem, L.length * sizeof(ElemType));
		delete[]L.elem;
		L.elem = New;
		L.length += NEW_LENGTH;
	}
	SQList();
	~SQList();
	int getLength();
	Statue add(const ElemType);
	void output();
};

SQList::SQList()
{
	L.length = START_LENGTH;
	L.tail = 0;
	L.elem = new(nothrow) ElemType[L.length];
	if (L.elem == NULL)
	{
		puts("No more free memory");
		exit(-1);
	}
}

SQList::~SQList()
{
	delete[]L.elem;
}

int SQList::getLength()
{
	return L.length;
}

Statue SQList::add(const ElemType x)
{
	if (L.length == L.tail)
		ReNew_L();
	int pos = L.tail + 1;
	sFor(i, 0, L.tail)
		if (L.elem[i] >= x)
		{
			pos = i + 1;
			break;
		}

	opFor(i, L.tail - 1, pos - 1)
		L.elem[i + 1] = L.elem[i];
	L.elem[pos - 1] = x;
	++L.tail;
	return pos;
}

void SQList::output()
{
	if (!L.tail)
	{
		puts("");
		return;
	}
	sFor(i, 0, L.tail - 1)
		printf("%d ", L.elem[i]);
	printf("%d\n", L.elem[L.tail - 1]);
}

int main()
{
	SQList LA, LB, LC;
	int x;
	const int LoveTaihouForever = 1;
	while (LoveTaihouForever)
	{
		scanf(" %d", &x);
		if (!x)
			break;
		LA.add(x);
	}
	while (LoveTaihouForever)
	{
		scanf(" %d", &x);
		if (!x)
			break;
		LB.add(x);
	}

	sFor(i, 0, LA.L.tail)
		LC.add(LA.L.elem[i]);
	sFor(i, 0, LB.L.tail)
		LC.add(LB.L.elem[i]);
	LC.output();

	//system("pause");
	return 0;
}