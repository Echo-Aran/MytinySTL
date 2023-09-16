#pragma once
#include<assert.h>
#include"reverse_iterator.h"

namespace mystl
{
	//List的节点
	template<class T>
	struct listNode
	{
		listNode<T>* _prev;
		listNode<T>* _next;
		T _val;

		listNode(const T& val = T())
			:_prev(nullptr)
			, _next(nullptr)
			, _val(val)
		{}

	};

	//List的迭代器：本质指针,指向链表节点
	template<class T,class Ref,class Ptr>
	class list_iterator
	{
		typedef listNode<T> Node;
		// typedef __list_iterator<T, T&, T*> iterator;
		// typedef __list_iterator<T, const T&, const T*> const_iterator;
	public:
		Node* _pnode;

		list_iterator(Node* pnode)
			:_pnode(pnode)
		{}

		Ref operator*()
		{
			return _pnode->_val;//->结构体指针访问结构体成员变量的方式
		}

		Ptr operator->()
		{
			return &(_pnode->_val);
		}

		
		typedef list_iterator<T, Ref, Ptr> Self;
		Self& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}

		Self operator++(int)
		{
			Self tmp(*this);

			_pnode = _pnode->_next;

			return tmp;
		}

		Self operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}

		Self operator--(int)
		{
			Self tmp(*this);

			_pnode = _pnode->_prev;

			return tmp;
		}

		bool operator==(const Self& it)
		{
			return _pnode == it._pnode;
		}

		bool operator!=(const Self& it)
		{
			return _pnode != it._pnode;
		}
		
	};


	template<class T>
	class list
	{
	private:
		typedef listNode<T> Node;

	public:
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

		typedef Reverse_Iterator<iterator, T&, T*> reverse_iterator;
		typedef Reverse_Iterator<const_iterator,const T&,const T*> const_reverse_iterator;
		
		
		///////////////////////////////////////////////////////////////
		// List的构造
		void createHead()
		{
			//创建双向list的头节点
			_head = new Node;//new返回的是动态分配内存的指针
			_head->_next = _head;
			_head->_prev = _head;

			_size = 0;
		}

		list()
		{
			createHead();
		}

		template <class Iterator>
		list(Iterator first, Iterator last)
		{
			createHead();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		list(const list<T>& lt)
		{
			createHead();

			// 用lt中的元素构造临时的temp,然后与当前对象交换
			list<T> temp(lt.begin(), lt.end());
			swap(temp);
		}

		list(int n, const T& value = T())
		{
			createHead();
			for (int i = 0; i < n; ++i)
				push_back(value);
		}

		

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		list<T>& operator=(list<T> lt)
		{
			//this->swap(lt);
			swap(lt);

			return *this;
		}



		///////////////////////////////////////////////////////////////
		// List的迭代器
		iterator begin()
		{
			return _head->_next;
		}
		//Returns an iterator referring to the past-the-end element in the list container.
		iterator end()
		{
			return _head;
		}
		const_iterator cbegin()const
		{
			return _head->_next;
		}
		const_iterator cend()const
		{
			return _head;
		}

		//之前iterator那个测试不能正常跑起来是因为没有写下面这两个
		iterator begin()const
		{
			return _head->_next;
		}
		iterator end()const
		{
			return _head;
		}



		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator crbegin()const
		{
			return const_reverse_iterator(cend());
		}

		const_reverse_iterator crend()const
		{
			return const_reverse_iterator(cbegin());
		}






		void push_back(const T& x)
		{
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(end(), x);
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		size_t size()
		{
			return _size;
		}

		//pos位置之前插入
		iterator insert(iterator pos,const T& x)
		{
			Node* newnode = new Node(x);
			Node* cur = pos._pnode;
			Node* prev = cur->_prev;

			cur->_prev = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			prev->_next = newnode;

			++_size;
			return newnode;
		}

		iterator erase(iterator pos)
		{
			Node* cur = pos._pnode;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;

			delete cur;
			--_size;

			return next;
		}

		void clear()
		{
			iterator it=begin();
			while (it != end())
			{
				it = erase(it);
				//删除以后迭代器失效，每次需要重新赋值
			}
			_size = 0;
		}

	private:
		Node* _head;//头指针，指向头节点
		size_t _size;
	};

}