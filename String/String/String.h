#pragma once

#include<iostream>//strlen()
#include<assert.h>
using namespace std;//ostream

namespace mystl {

	//����û������string ��ͷ�ļ�
	//�Լ�ʵ��string��Ҳ����˵ �������г��ֵ�string�����Զ�������

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
			memcpy(_str, s._str, s._size + 1);//ת����������Ϊ�ṹ�� s._str������s
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

		//������Ĳ�ͬ�������ں������ڿ���������ʱ���������ڴ��ε�ʱ��Ϳ���������ʱ����

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

			const char* p = strstr(_str, str);//strstr���������ַ����в����Ӵ��ĺ���������ҵ��������Ӵ��������еĵ�ַ�����û���ҵ�������nullptr
			if (p) 
			{
				return p - _str;//��ַ֮��
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

				memcpy(tmp, _str, _size);//�洢�ռ䱻���·���
				delete[] _str;//ָ�벻�ᱻ������ָ��ָ��Ŀռ䱻����
				_str = tmp;
				_capacity = n;
			}
		}

		void push_back(char ch)
		{
			if (_size = _capacity) 
			{
				//2������
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
				//�������ݵ�_size+len
				reserve(_size + len);
			}

			for (int i = 0; i < len; i++)
			{
				push_back(str[i]);
			}
			return *this;
		}

		// ��posλ���ϲ����ַ�c/�ַ���str�������ظ��ַ���λ��
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

		// ɾ��posλ���ϵ�Ԫ�أ������ظ�Ԫ�ص���һ��λ��
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
			int ret = memcmp(_str, s._str, _size <s._size ? _size : s._size);//memcmp,�Ƚ�str1��str2��ǰn���ֽ� ����ֵ<0 < ;=0  = ;>0 >
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
		size_t _capacity;//��Ч�ַ�,����ռ��ʱ��Ҫ+1
		char* _str;
	};

	//�Ҹո��Եĵ�s�Ǹ��࣬Ϊʲô����s[i]��������
	//�������ʵ�֣�[]���Ƿ���s�е�_str[i]
	//�����Ѿ�ʵ����string ����������þͺ�

	//��c_str��������c�����ַ��������const char* ���� '\0' ����ֹ
	//�������Ǵ�ӡ�����ַ���
	//Ҳ����˵c���ַ����飬��'\0'�㳤�ȣ�string����'\0'����_sizeΪ��ֹ�㳤��
	//���֮ǰ��strcpyҲҪ���ã�����'\0'�ͽ��������Ծ�����memcpy


	ostream& operator<<(ostream& out, const string& s)//ostream���˷��������������ûᱨ��
	{

		for (auto ch : s)
		{
			out << ch;
		}

		return out;
	}
	istream& operator>>(istream& in, string& s)
	{
		//��׼���ʵ������ÿ�ε��õ�ʱ������
		s.clear();

		//in >> ch; //Ĭ�ϲ���' ' ��'\n'
		char ch = in.get();

		//��������ǰ��Ŀո�ͻ���
		while (ch == ' ' || ch == '\n')
		{
			ch = in.get();
		}

		char buff[128];
		int i = 0;

		while (ch != ' ' && ch != '\n')//�����ո�ͻ��н���
		{
			//s += ch;//ÿ�ζ���Ҫ����
			buff[i++] = ch;//�ŵ�Ͱ��
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
