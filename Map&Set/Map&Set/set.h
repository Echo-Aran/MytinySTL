#pragma once
#include"RB_Tree.h"
namespace mystl
{
	template<class K>
	class Set
	{
	private:
		struct setKeyofT
		{
			const K& operator()(const K& key)//传入的是K类型的
			{
				return key;
			}
		};
		RBTree<K, K, setKeyofT> _t;

	public:
		//底层是对树的封装
		typedef typename RBTree<K, K, setKeyofT>::const_iterator iterator;//两个迭代器本质上都是const迭代器，不允许对set中的值修改
		typedef typename RBTree<K, K, setKeyofT>::const_iterator const_iterator;
		
		iterator begin()const
		{
			//这样传进来的_t就有const修饰，调用的是RBTree中const_iterator begin()const
			//可以满足和set中（const）iterator的配对
			return _t.begin();
		}
		/*const_iterator begin()const
		{
			return _t.begin();
		}*/

		iterator end()const
		{
			return _t.end();
		}
		/*const_iterator end()const
		{
			return _t.end();
		}*/


		// iterator RBTree::const_iterator
		pair<iterator, bool> Insert(const K& k)
		{
			// pair<RBTree::iterator, bool>
			/*return _t.Insert(k);*/
			pair<typename RBTree<K, K, setKeyofT>::iterator, bool> ret = _t.Insert(k);
			return pair<iterator, bool>(ret.first, ret.second);
		}
	};
}