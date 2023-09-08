#define _CRT_SECURE_NO_WARNINGS
#include"String.h"
void test1() {
	mystl::string s1("hello world");
	cout << s1.c_str() << endl;

	/*mystl::string s2(s1);
	cout << s2.c_str() << endl;*/
}

void test2() {
	mystl::string s1("to be not to be that is the question");
	//c_str：str是私有的，提供接口
	//<<运算符还没有重载
	cout << s1.c_str() << endl;

	s1.insert(6, "or ");
	cout << s1.c_str() << endl;

}

void test3() {
	mystl::string s1("This is an example sentence.");
	cout << s1.c_str() << endl;

	s1.erase(10, 8);
	cout << s1.c_str() << endl;

}
void test4() {
	mystl::string s1("This is an example sentence.");
	cout << s1<< endl;

}
int main() {
	test4();

	return 0;
}