#pragma once
#include<functional>
namespace mystl
{
	//仿函数:具有函数行为的对象或者类
	//Less 仿函数类
	template<class T>
	class Less
	{
	public:
		bool operator()(const T& x,const T& y)
		{
			return x < y;
		}
	};

	template<class T>
	class Greater
	{
	public:
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};

	template<class T,class container=vector<T>,class compare=Less<T>>
	class priority_queue
	{
	private:
		container _con;
		compare Com;

		void AdjustUp(int child)
		{
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				if (Com(_con[child], _con[parent]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}

		}

		void AdjustDown(int parent)
		{
			int child = parent * 2 + 1;
			size_t n = _con.size();

			while (child < n)
			{
				if (child + 1 < _con.size() && Com(_con[child], _con[child + 1]))
				{
					++child;
				}

				if (Com(_con[child], _con[parent]))
				{
					swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}

		}

	public:

		priority_queue()
		{}

		//typedef container::iterator InputIterator;
		template<class InputIterator>
		priority_queue(InputIterator first,InputIterator last)
		{
			while (first != last)
			{
				_con.push_back(*first);
				++first;
			}
		}

		void push(const T& x)
		{
			_con.push_back(x);
			AdjustUp(_con.size()-1);
		}

		void pop()
		{
			size_t n = _con.size();
			swap(_con[0], _con[n - 1]);
			_con.pop_back();
			AdjustDown(0);
		}


		bool empty()
		{
			return _con.empty();
		}

		size_t size()const
		{
			return _con.size();
		}

		const T& top()
		{
			return _con[0];
		}

	};
}