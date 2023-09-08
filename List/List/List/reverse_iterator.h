#pragma once

//这个类实例化出来的对象，要可以通过这些接口，实现相应的功能
template<class Iterator,class Ref,class Ptr>
class Reverse_Iterator
{
private:
	Iterator _it;

public:
	typedef Reverse_Iterator<Iterator,Ref,Ptr> Self;

	Reverse_Iterator(Iterator it)
		:_it(it)
	{}

	//具有指针类似行为

	Ref operator*()
	{
		Iterator temp = _it;
		return *(--temp);
	}

	Ptr operator->()
	{
		/*Iterator temp = _it;
		return &(*(--temp));*/
		return &(operator*());
	}
	

	//迭代器支持移动
	Self& operator++()
	{
		--_it;
		return *this;
	}

	Self& operator++(int)
	{
		Self temp = _it;
		--_it;
		return temp;
	}

	Self& operator--()
	{
		++_it;
		return *this;
	}

	Self& operator--(int)
	{
		Self temp = _it;
		++_it;
		return temp;
	}


	//迭代器支持比较
	bool operator!=(const Self& sf)
	{
		return _it != sf._it;
	}

	bool operator==(const Self& sf)
	{
		return _it == sf._it;
	}
};