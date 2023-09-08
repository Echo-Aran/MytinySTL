#pragma once
#include <assert.h>
#include"reverse_iterator.h"

namespace mystl {
	template<class T>
	class vector 
	{
	public:

		typedef T* iterator;
		typedef const T* const_iterator;

		typedef Reverse_Iterator<iterator, T&, T*> reverse_iterator;
		typedef Reverse_Iterator<const_iterator, const T&, const T*> const_reverse_iterator;

		iterator begin()
		{
			return _start;
		}
		//cbegin return a const iterator
		const_iterator cbegin()const
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator cend()const
		{
			return _finish;
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator crbegin()const
		{
			return reverse_iterator(cend());

		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator crend()const
		{
			return const_reverse_iterator(cbegin());
		}

		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{}

		vector(const vector<T>& v)
		{
			_start = new T[v.capacity()];
			for (size_t i = 0; i < v.size(); i++)
			{
				_start[i] = v._start[i];
			}
			_finish = _start + v.size();
			_endofstorage = _start + v.capacity();
		}

		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}



		/*
		* 理论上，提供了vector(size_t n, const T& value = T())之后
		* vector(int n, const T& value = T())就不需要提供了，但是对于：
		* vector<int> v(10, 5);
		* 编译器在编译时，认为T已经被实例化为int，而10和5编译器会默认其为int类型
		* 就不会走vector(size_t n, const T& value = T())这个构造方法，
		* 最终选择的是：vector(InputIterator first, InputIterator last)
		* 因为编译器觉得区间构造两个参数类型一致，因此编译器就会将InputIterator实例化为int
		* 但是10和5根本不是一个区间，编译时就报错了
		* 故需要增加该构造方法
		*/
		vector(size_t n, const T& value = T())
		{
			resize(n, value);
		}

		vector(int n, const T& value = T())
		{
			resize(n, value);
		}


		// 若使用iterator做迭代器，会导致初始化的迭代器区间[first,last)只能是vector的迭代器
		// 重新声明迭代器，迭代器区间[first,last)可以是任意容器的迭代器
		/*template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			while (first != end)
			{
				push_back(*first);
				++first;
			}
		}*/

		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}

		

		//capacity
		size_t size()const
		{
			return _finish - _start;
		}

		size_t capacity()const
		{
			return  _endofstorage - _start;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				//新建一个T类型的数组
				T* tmp = new T[n];

				
				if (_start)
				{
					//memcpy(tmp, _start, size());//memcpy只适用于内部类型的值拷贝
					for (size_t i = 0; i < sz; i++) 
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}

				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}

		void resize(size_t n, const T& value = T())
		{
			//1.当前个数小于size,将size缩小到n
			if (n < size())
			{
				_finish = _start + n;
				return;
			}
			//空间不够则扩容
			if (capacity() < n)
			{
				reserve(n);
			}
			//将size扩大到n
			iterator it = _finish;
			_finish = _start + n;
			while (it != _finish)
			{
				*it = value;
				++it;
			}

		}

		//access
		T& operator[](size_t pos)
		{
			assert(pos < size());
			return _start[pos];
		}

		const T& operator[](size_t pos)const
		{
			assert(pos < size());
			return _start[pos];
		}

		//modify
		void push_back(const T& x)
		{
			insert(end(), x);
		}

		void pop_back()
		{
			erase(--end());
		}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}

		//在pos位置(之前)插入一个值
		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start && pos <=_finish);

			if (_finish == _endofstorage)
			{
				//2倍扩容
				size_t len = pos - _start;
				size_t newcapacity =capacity() == 0 ? 4 : 2 * capacity();
				reserve(newcapacity);
				pos = _start + len;//解决重新分配空间后,pos迭代器失效的问题
			}

			//移动元素,把pos位置留出来
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				end--;
			}
			*pos = x;
			++_finish;
			return pos;
		}

		//返回删除数据的下一个数据
		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos < _finish);

			iterator it = pos;
			while (it < _finish)
			{
				*it = *(it + 1);
				it++;
			}
			_finish--;
			return pos;
		}

	private:
		iterator _start;//数据块的开始 //等同于数组名
		iterator _finish;//有效数据的结束
		iterator _endofstorage;//存储容量的尾
	};
}
