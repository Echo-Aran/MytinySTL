#pragma once
#include<list>
#include<vector>
#include<deque>

namespace mystl
{
	template<class T, class container = deque<T>>
	class stack
	{
	public:
		void push(const T& x)
		{
			return Con.push_back(x);
		}

		void pop()
		{
			return Con.pop_back();
		}

		T& top()
		{
			return Con.back();
		}
		const T& top()const
		{
			return Con.back();
		}

		size_t size()const
		{
			return Con.size();
		}

		bool empty()const
		{
			return Con.empty();
		}

	private:
		container Con;
	};
}