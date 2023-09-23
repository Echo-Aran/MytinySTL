#include"Hash_Table.h"
#include<iostream>
#include<string>
using namespace std;

//int main()
//{
//	open_address::Hash_table<int, int> ht;
//	int a[] = { 1,111,4,7,15,25,44,9 };
//	for (auto e : a)
//	{
//		ht.Insert(make_pair(e, e));
//	}
//
//	ht.Erase(15);
//
//	auto ret = ht.Find(4);
//	//ret->_kv.first = 41;
//	ret->_kv.second = 400;
//
//	//HashTable<string, string, StringHashFunc> dict;
//	open_address::Hash_table<string, string> dict;
//	dict.Insert(make_pair("sort", "ÅÅÐò"));
//	dict.Insert(make_pair("left", "xxx"));
//	auto dret = dict.Find("left");
//	//dret->_kv.first = "xx";
//	dret->_kv.second = "×ó±ß";
//
//	string s1("xxx");
//	string s2("xxx");
//
//
//	/*HashFunc<string> hf;
//	cout << hf(s1) << endl;
//	cout << hf(s2) << endl;
//	cout << hf("bacd") << endl;
//	cout << hf("abcd") << endl;
//	cout << hf("abbe") << endl;
//	cout << hf("https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&rsv_idx=1&tn=65081411_1_oem_dg&wd=STATE&fenlei=256&rsv_pq=0xdd48647300054f47&rsv_t=1cd5rO%2BE6TJzo6qf9QKcibznhQ9J3lFwGEzmkc0Goazr3HuQSIIc2zD78Pt0&rqlang=en&rsv_enter=1&rsv_dl=tb&rsv_sug3=2&rsv_n=2&rsv_sug1=1&rsv_sug7=100&rsv_sug2=0&rsv_btype=i&prefixsug=STAT%2526gt%253B&rsp=5&inputT=656&rsv_sug4=796") << endl;*/
//
//	return 0;
//}


//int main()
//{
//	open_address::HashTable<int, int> ht;
//	int a[] = { 1,111,4,7,15,25,44,9 };
//	for (auto e : a)
//	{
//		ht.Insert(make_pair(e, e));
//	}
//
//	ht.Erase(15);
//
//	auto ret = ht.Find(4);
//	//ret->_kv.first = 41;
//	ret->_kv.second = 400;
//
//	//HashTable<string, string, StringHashFunc> dict;
//	open_address::HashTable<string, string> dict;
//	dict.Insert(make_pair("sort", "ÅÅÐò"));
//	dict.Insert(make_pair("left", "xxx"));
//	auto dret = dict.Find("left");
//	//dret->_kv.first = "xx";
//	dret->_kv.second = "×ó±ß";
//
//	string s1("xxx");
//	string s2("xxx");
//
//
//	open_address::DefaultHashFunc<string> hf;
//	cout << hf(s1) << endl;
//	cout << hf(s2) << endl;
//	cout << hf("bacd") << endl;
//	cout << hf("abcd") << endl;
//	cout << hf("abbe") << endl;
//	cout << hf("https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&rsv_idx=1&tn=65081411_1_oem_dg&wd=STATE&fenlei=256&rsv_pq=0xdd48647300054f47&rsv_t=1cd5rO%2BE6TJzo6qf9QKcibznhQ9J3lFwGEzmkc0Goazr3HuQSIIc2zD78Pt0&rqlang=en&rsv_enter=1&rsv_dl=tb&rsv_sug3=2&rsv_n=2&rsv_sug1=1&rsv_sug7=100&rsv_sug2=0&rsv_btype=i&prefixsug=STAT%2526gt%253B&rsp=5&inputT=656&rsv_sug4=796") << endl;
//
//	return 0;
//}

int main()
{
	hash_bucket::HashTable<int, int> ht;
	int a[] = { 1,111,4,7,15,25,44,9 };
	for (auto e : a)
	{
		ht.Insert(make_pair(e, e));
	}
	ht.Print();

	ht.Insert(make_pair(14, 14));
	ht.Print();

	ht.Insert(make_pair(24, 24));
	ht.Print();

	ht.Insert(make_pair(34, 34));
	ht.Print();

	ht.Erase(44);
	ht.Erase(4);
	ht.Erase(24);
	ht.Print();

	hash_bucket::HashTable<string, string> dict;
	dict.Insert(make_pair("sort", "ÅÅÐò"));
	dict.Insert(make_pair("left", "xxx"));
	dict.Insert(make_pair("insert", "²åÈë"));
	dict.Insert(make_pair("string", "×Ö·û´®"));
	dict.Insert(make_pair("bucket", "Í°"));

	auto dret = dict.Find("left");
	//dret->_kv.first = "xx";
	dret->_kv.second = "×ó±ß";
	dict.Print();

	return 0;
}