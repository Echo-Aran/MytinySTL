#include<iostream>
using namespace std;
#include"list.h"

void test_list1()
{
	mystl::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);

	//auto it = lt.begin();
	mystl::list_iterator<int,int&,int*> it = lt.begin();

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	while (it != lt.end())
	{
		(*it) += 1;
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
}
struct A
{
	A(int a1 = 0, int a2 = 0)
		:_a1(a1)
		, _a2(a2)
	{}

	int _a1;
	int _a2;
};

void test_list2()
{
	mystl::list<A> lt;
	lt.push_back(A(1, 1));
	lt.push_back(A(2, 2));
	lt.push_back(A(3, 3));
	lt.push_back(A(4, 4));

	auto it = lt.begin();
	while (it != lt.end())
	{
		//cout << (*it)._a1 << " " << (*it)._a2 << endl;
		cout << it->_a1 << " " << it->_a2 << endl;

		++it;
	}
	cout << endl;
}

void test_list3()
{
	mystl::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_front(5);
	lt.push_front(6);
	lt.push_front(7);
	lt.push_front(8);
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.pop_front();
	lt.pop_back();

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.clear();
	lt.push_back(10);
	lt.push_back(20);
	lt.push_back(30);
	lt.push_back(40);
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	cout << lt.size() << endl;
}

void test_list4()
{
	mystl::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	mystl::list<int> lt1(lt);
	for (auto e : lt1)
	{
		cout << e << " ";
	}
	cout << endl;

	mystl::list<int> lt2;
	lt2.push_back(10);
	lt2.push_back(20);
	lt2.push_back(30);
	lt2.push_back(40);

	for (auto e : lt2)
	{
		cout << e << " ";
	}
	cout << endl;

	lt1 = lt2;

	for (auto e : lt1)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_list5()
{
	mystl::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_front(5);
	lt.push_front(6);
	lt.push_front(7);
	lt.push_front(8);
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	auto rit = lt.rbegin();
	//mystl::list<int>::reverse_iterator rit= lt.rbegin();

	while (rit != lt.rend())
	{
		cout << (*rit) << " ";
		rit++;
	}
}

void test_list6()
{
	mystl::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_front(5);
	lt.push_front(6);
	lt.push_front(7);
	lt.push_front(8);
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	mystl::list<int> lt2(lt);
	for (auto e : lt2)
	{
		cout << e << " ";
	}
	cout << endl;

}

int main()
{
	/*test_list1();
	test_list2(); 
	test_list3();
	test_list4();*/
	//test_list5();
	test_list6();

	return 0;
}