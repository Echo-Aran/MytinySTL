#include <iostream>
using namespace std;
#include "vector.h"


void test_vector1()
{
	mystl::vector<char> strV;
	//string str;
	// string要求最后有\0,更好兼容c接口
	// string有很多他的专用接口函数

	mystl::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	mystl::vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_vector2()
{
	mystl::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;


	mystl::vector<int>::reverse_iterator rit = v.rbegin();
	while (rit != v.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;

}

void test_vector3()
{
	mystl::vector<int> v1;
	mystl::vector<int> v2(10, 5);

	/*int array[] = { 1,2,3,4,5 };
	mystl::vector<int> v3(array, array + sizeof(array) / sizeof(array[0]));*/

	mystl::vector<int> v4(v2);

	for (size_t i = 0; i < v2.size(); ++i)
	{
		cout << v2[i] << " ";
	}
	cout << endl;

	/*auto it = v3.begin();
	while (it != v3.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;*/

	for (auto e : v4)
	{
		cout << e << " ";
	}
	cout << endl;
}


int main()
{
	//test_vector1();
	//test_vector2();
	test_vector3();

	return 0;
}