#include<iostream>
using namespace std;
#include"stack.h"
#include"queue.h"
#include"priority_queue.h"
#include"Date.h"

void test_stack()
{
	//stack<int, vector<int>> st1;
	mystl::stack<int> st1;
	st1.push(1);
	st1.push(2);
	st1.push(3);
	st1.push(4);

	while (!st1.empty())
	{
		cout << st1.top() << " ";
		st1.pop();
	}
	cout << endl;

	mystl::stack<int, list<int>> st2;
	st2.push(1);
	st2.push(2);
	st2.push(3);
	st2.push(4);

	while (!st2.empty())
	{
		cout << st2.top() << " ";
		st2.pop();
	}
	cout << endl;
}

void test_queue()
{
	mystl::queue<int, list<int>> q;

	//queue<int, vector<int>> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}

void test_priority_queue1()
{
	// 默认是大堆 -- less
	//priority_queue<int> pq;

	// 仿函数控制实现小堆
	mystl::priority_queue<int, vector<int>, mystl::Greater<int>> pq;

	pq.push(3);
	pq.push(5);
	pq.push(1);
	pq.push(4);

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}



void test_priority_queue2()
{
	// 仿函数控制实现小堆
	/*mystl::priority_queue<Date, vector<Date>, mystl::Less<Date>> pq;

	pq.push(Date(2023, 7, 20));
	pq.push(Date(2023, 6, 20));
	pq.push(Date(2023, 8, 20));

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;*/

	struct LessPDate
	{
		bool operator()(const Date* p1, const Date* p2)
		{
			return *p1 < *p2;
		}
	};
	
	//新构造一个仿函数LessPDate，Less和Greater比较的都是其存储地址，每一次的结果都会变
	mystl::priority_queue<Date*,vector<Date*>,LessPDate> pq;
	pq.push(new Date(2023, 7, 20));
	pq.push(new Date(2023, 6, 20));
	pq.push(new Date(2023, 8, 20));

	while (!pq.empty())
	{
		cout << *pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

int main()
{
	//test_stack();
	//test_queue();
	//test_priority_queue1();
	test_priority_queue2();

	return 0;
}