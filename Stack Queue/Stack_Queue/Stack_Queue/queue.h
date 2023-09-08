#pragma once
#include<list>
#include<vector>
#include<deque>

namespace mystl
{
	template<class T, class container = deque<T>>
	class queue
	{
	public:
		void push(const T& x)
		{
			return Con.push_back(x);
		}

		void pop()
		{
			return Con.pop_front();
		}

		T& front()
		{
			return Con.front();
		}
		const T& front()const
		{
			return Con.front();
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