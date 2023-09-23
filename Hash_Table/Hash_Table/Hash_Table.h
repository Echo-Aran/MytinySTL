#pragma once
#include<iostream>
#include<vector>
using namespace std;
//哈希表里存储键值对
enum State
{
	Delete,
	Empty,
	Exist
};

template<class K,class V>
struct HashData
{
	pair<K, V> _kv;
	State _state = Empty;
};



template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

//特化
template<>
struct HashFunc<string>
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto ch : str)
		{
			hash *= 131;
			hash += ch;
		}

		return hash;
	}
};




template<class K, class V>
class Hash_table
{
	size_t _n = 0;
	vector<HashData<K, V>> _table;
public:
	Hash_table()
		:_n(10)
	{
		_table.resize(10);
	}

	bool Insert(const pair<K, V>& kv)
	{
		//扩容
		if (_n * 10 / _table.size() > 7)
		{
			size_t newsize = _table.size() * 2;
			Hash_table<K, V> newTable;
			newTable._table.resize(newsize);

			//遍历旧表的数据插入到新表
			for (size_t i = 0; i < _table.size(); i++)
			{
				if (_table[i]._state == Exist)
				{
					newTable.Insert(_table[i]._kv);
				}
			}

			_table.swap(newTable._table);
		}

		//线性探测
		HashFunc<K> hf;
		size_t hashi = hf(kv.first) % _table.size();
		while (_table[hashi]._state == Exist)
		{
			++hashi;
			hashi %= _table.size();
		}
		_table[hashi]._kv = kv;
		_table[hashi]._state = Exist;
		++_n;
		return true;
	}

	HashData<const K, V>* Find(const K& key)const
	{
		HashFunc<K> hf;
		size_t hashi = hf(key) % _table.size();
		while (_table[hashi]._state != Empty)
		{
			if (_table[hashi]._state == Exist && _table[hashi]._kv.first == key)
			{
				return (HashData<const K, V>*) & _table[hashi];
			}
			++hashi;
			hashi %= _table.size();
		}
		return nullptr;
	}

	bool Erase(const K& key)
	{
		HashData<const K, V>* ret = Find(key);
		if (ret)
		{
			ret->_state = Delete;
			--_n;

			return true;
		}

		return false;
	}

};