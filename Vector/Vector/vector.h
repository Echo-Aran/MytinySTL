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
		* �����ϣ��ṩ��vector(size_t n, const T& value = T())֮��
		* vector(int n, const T& value = T())�Ͳ���Ҫ�ṩ�ˣ����Ƕ��ڣ�
		* vector<int> v(10, 5);
		* �������ڱ���ʱ����ΪT�Ѿ���ʵ����Ϊint����10��5��������Ĭ����Ϊint����
		* �Ͳ�����vector(size_t n, const T& value = T())������췽����
		* ����ѡ����ǣ�vector(InputIterator first, InputIterator last)
		* ��Ϊ�������������乹��������������һ�£���˱������ͻὫInputIteratorʵ����Ϊint
		* ����10��5��������һ�����䣬����ʱ�ͱ�����
		* ����Ҫ���Ӹù��췽��
		*/
		vector(size_t n, const T& value = T())
		{
			resize(n, value);
		}

		vector(int n, const T& value = T())
		{
			resize(n, value);
		}


		// ��ʹ��iterator�����������ᵼ�³�ʼ���ĵ���������[first,last)ֻ����vector�ĵ�����
		// ��������������������������[first,last)���������������ĵ�����
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
				//�½�һ��T���͵�����
				T* tmp = new T[n];

				
				if (_start)
				{
					//memcpy(tmp, _start, size());//memcpyֻ�������ڲ����͵�ֵ����
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
			//1.��ǰ����С��size,��size��С��n
			if (n < size())
			{
				_finish = _start + n;
				return;
			}
			//�ռ䲻��������
			if (capacity() < n)
			{
				reserve(n);
			}
			//��size����n
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

		//��posλ��(֮ǰ)����һ��ֵ
		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start && pos <=_finish);

			if (_finish == _endofstorage)
			{
				//2������
				size_t len = pos - _start;
				size_t newcapacity =capacity() == 0 ? 4 : 2 * capacity();
				reserve(newcapacity);
				pos = _start + len;//������·���ռ��,pos������ʧЧ������
			}

			//�ƶ�Ԫ��,��posλ��������
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

		//����ɾ�����ݵ���һ������
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
		iterator _start;//���ݿ�Ŀ�ʼ //��ͬ��������
		iterator _finish;//��Ч���ݵĽ���
		iterator _endofstorage;//�洢������β
	};
}
