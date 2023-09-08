#pragma once

//�����ʵ���������Ķ���Ҫ����ͨ����Щ�ӿڣ�ʵ����Ӧ�Ĺ���
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

	//����ָ��������Ϊ

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
	

	//������֧���ƶ�
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


	//������֧�ֱȽ�
	bool operator!=(const Self& sf)
	{
		return _it != sf._it;
	}

	bool operator==(const Self& sf)
	{
		return _it == sf._it;
	}
};