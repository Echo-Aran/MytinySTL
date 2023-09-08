#pragma once

#include<iostream>//strlen()
#include<assert.h>
using namespace std;//ostream

namespace mystl {

	//现在没有引用string 的头文件
	//自己实现string，也就是说 下面所有出现的string都是自定义类型

	class string{

	public:

		static const size_t npos = -1;

		typedef char* iterator;
		typedef const char* const_iterator;

		string(const char* str="")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			//strcpy(_str, str);
			memcpy(_str, str, _size+1);
		} 
	
		string(const string& s) 
		{	
			_str = new char[s._capacity + 1];
			memcpy(_str, s._str, s._size + 1);//转换错误是因为结构体 s._str而不是s
			_size = s._size;
			_capacity = s._capacity;
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		const char* c_str() const 
		{
			return _str;
		}

		size_t size() const
		{
			return _size;
		}

		size_t capacity()const
		{
			return _capacity;
		}

		bool empty()const
		{
			return _size == 0;
		}

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str+_size;
		}

		const_iterator begin()const 
		{
			return _str;
		}

		const_iterator end()const
		{
			return _str + _size;
		}

		char& operator[](size_t pos) 
		{
			assert(pos < _size);
			return _str[pos];
		}

		const char& operator[] (size_t pos) const
		{
			assert(pos < _size);
			return _str[pos]; 
		}


		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string& operator+=(const char* str)
		{
			return append(str);
		}

		//string& operator=(const string& s) 
		//{
		//	if (*this != s)
		//	{
		//		string tmp(s);
		//		swap(tmp);

		//		/*char* tmp = new char[s._capacity + 1];
		//		memcpy(tmp, s._str, _size + 1);
		//		delete[] _str;
		//		_str = tmp;
		//		_size = s._size;
		//		_capacity = s._capacity;*/

		//	}
		//	return *this;
		//}

		//与上面的不同：上面在函数体内拷贝构造临时对象，下面在传参的时候就拷贝构造临时对象

		string& operator=(string tmp)
		{
			swap(tmp);

			return *this;
		}

		void resize(size_t n,char ch='\0')
		{
			if (n < _size) 
			{
				_size = n;
				_str[_size] = '\0';
			}
			else 
			{
				reserve(n);
				for (int i = _size; i < n; i++)
				{
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';

			}
		}

		size_t find(const char* str, size_t pos = 0)const
		{
			assert(pos < _size);

			const char* p = strstr(_str, str);//strstr是用来在字符串中查找子串的函数，如果找到，返回子串在主串中的地址，如果没有找到，返回nullptr
			if (p) 
			{
				return p - _str;//地址之差
			}
			else
			{
				return npos;
			}
		}

		void reserve(size_t n=0)
		{
			if (n > _capacity) 
			{
				char* tmp = new char[n + 1];
				//strcpy(tmp, _str);

				memcpy(tmp, _str, _size);//存储空间被重新分配
				delete[] _str;//指针不会被清理，是指针指向的空间被清理
				_str = tmp;
				_capacity = n;
			}
		}

		void push_back(char ch)
		{
			if (_size = _capacity) 
			{
				//2倍扩容
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}


		string& append(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				//至少扩容到_size+len
				reserve(_size + len);
			}

			for (int i = 0; i < len; i++)
			{
				push_back(str[i]);
			}
			return *this;
		}

		// 在pos位置上插入字符c/字符串str，并返回该字符的位置
		string& insert(size_t pos,size_t n,char ch)
		{
			assert(pos <= _size);

			if (n + _size > _capacity) 
			{
				reserve(n + _size);
			}

			//move
			size_t end = _size;
			while (end >= pos && end != npos)
			{
				_str[end + n] = _str[end];
				end--;
			}

			//insert
			for (int i = 0; i < n; i++) 
			{
				_str[pos + i] = ch;
			}

			_size += n;

			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);

			int len = strlen(str);
			if (len + _size > _capacity)
			{
				reserve(len + _size);
			}

			//move
			size_t end = _size;
			while (end >= pos && end != npos)
			{
				_str[end + len] = _str[end];
				end--;
			}

			for (int i = 0; i < len; i++)
			{
				_str[pos + i] = str[i];
			}
			return *this;
		}

		// 删除pos位置上的元素，并返回该元素的下一个位置
        string& erase(size_t pos=0,size_t len=npos)
		{ 
			assert(pos <= _size);
			size_t end = _size;
			if (len==npos||pos + len >= _size) {

				_str[pos] = '\0';
				_size = pos; 

			}
			else {
				size_t i = len + pos;
				for (; i < _size; i++)
				{
					_str[i - len] = _str[i];

				}
				_size -= len;
				_str[_size] = '\0';
			}

			return *this;
		}

		void clear()
		{
			_size = 0;
			_str[_size] = '\0';
		}

		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);

		}

		string substr(size_t pos = 0, size_t len = npos)const
		{
			assert(pos < _size);

			if (len == npos || pos + len > _size) {
				len = _size - pos;
			}
			string tmp;
			tmp.reserve(len);
			for (int i = pos; i < len; i++)
			{
				tmp += _str[i];
			}
			return tmp;
		}

		bool operator<(const string& s)
		{
			int ret = memcmp(_str, s._str, _size <s._size ? _size : s._size);//memcmp,比较str1和str2的前n个字节 返回值<0 < ;=0  = ;>0 >
			return ret < 0 ? true : false;
		}

		bool operator==(const string& s)
		{
			int ret = memcmp(_str, s._str, _size < s._size ? _size : s._size);
			return ret == 0;
		}

		bool operator<=(const string& s)
		{
			return (*this < s || *this == s);
		}
		bool operator>(const string& s)
		{
			return !(*this <= s);
		}
		bool operator>=(const string& s)
		{
			return !(*this < s);
		}
		bool operator!=(const string& s)
		{
			return !(*this == s);
		}


	private:
		size_t _size;
		size_t _capacity;//有效字符,申请空间的时候要+1
		char* _str;
	};

	//我刚刚迷的点s是个类，为什么可以s[i]访问数组
	//上面就是实现，[]就是访问s中的_str[i]
	//上面已经实现了string 下面就正常用就好

	//与c_str的区别：以c语言字符串打出是const char* 遇到 '\0' 就终止
	//流插入是打印整个字符串
	//也就是说c的字符数组，以'\0'算长度，string不看'\0'，以_size为终止算长度
	//因此之前的strcpy也要慎用，遇到'\0'就结束，所以尽量用memcpy


	ostream& operator<<(ostream& out, const string& s)//ostream做了防拷贝，不用引用会报错
	{

		for (auto ch : s)
		{
			out << ch;
		}

		return out;
	}
	istream& operator>>(istream& in, string& s)
	{
		//标准库的实现是在每次调用的时候清零
		s.clear();

		//in >> ch; //默认不读' ' 和'\n'
		char ch = in.get();

		//处理缓冲区前面的空格和换行
		while (ch == ' ' || ch == '\n')
		{
			ch = in.get();
		}

		char buff[128];
		int i = 0;

		while (ch != ' ' && ch != '\n')//遇到空格和换行结束
		{
			//s += ch;//每次都需要扩容
			buff[i++] = ch;//放到桶里
			if (i == 127)
			{
				buff[i] = '\0';
				s += buff;
				i = 0;
			}
			ch = in.get();
		}
		if (i != 0)
		{
			buff[i] = '\0';
			s += buff;
		}
		return in;
	
	}
};
