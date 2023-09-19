#pragma once
#include"RB_Tree.h"
namespace mystl
{
	template<class K,class V>
	class Map
	{
		//设置为内部类更好，可以直接调用K，V
		struct mapKeyOfT
		{
			const K& operator()(const pair<const K, V>& kv)//传入的是pair类型的
			{
				return kv.first;
			}
		};
	public:
		typedef typename RBTree<K, pair<const K, V>, mapKeyOfT>::iterator iterator;
		typedef typename RBTree<K, pair<const K, V>, mapKeyOfT>::const_iterator const_iterator;

		iterator begin()
		{
			return _t.begin();
		}

		const_iterator begin()const
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		const_iterator end()const
		{
			return _t.end();
		}

		pair<iterator, bool> Insert(const pair<const K, V>& kv)
		{
			return _t.Insert(kv);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = Insert(make_pair(key, V()));
			return ret.first->second;
		}


	private:
		RBTree<K,pair<K,V>,mapKeyOfT> _t;

	};
}