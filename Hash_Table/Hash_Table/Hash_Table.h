#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class K>
struct DefaultHashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

//�ػ�
template<>
struct DefaultHashFunc<string>
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

//����Ѱַ��
namespace open_address
{
	//��ϣ����洢��ֵ��
	enum State
	{
		Delete,
		Empty,
		Exist
	};

	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		State _state = Empty;
	};


	template<class K, class V, class HashFunc = DefaultHashFunc<K>>
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
			//����
			if (_n * 10 / _table.size() > 7)
			{
				size_t newsize = _table.size() * 2;
				Hash_table<K, V> newTable;
				newTable._table.resize(newsize);

				//�����ɱ�����ݲ��뵽�±�
				for (size_t i = 0; i < _table.size(); i++)
				{
					if (_table[i]._state == Exist)
					{
						newTable.Insert(_table[i]._kv);
					}
				}

				_table.swap(newTable._table);
			}

			//����̽��
			HashFunc hf;
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
			HashFunc hf;
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
}

namespace hash_bucket
{
	template<class K,class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode* _next;

		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			,_next(nullptr)
		{}
	};

	template<class K,class V,class HashFunc=DefaultHashFunc<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;

		size_t _n = 0;//�洢������Ч����
		vector<Node*> _table;//ָ������
	public:
		HashTable()
		{
			_table.resize(10, nullptr);
		}

		~HashTable()
		{
			for (size_t i = 0; i < _table.size(); i++)
			{
				Node* cur = _table[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_table[i] = nullptr;
			}
		}

		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first)) 
			{
				return false;
			}

			HashFunc hf;

			//����������==_table.size()������
			if (_n == _table.size())
			{
				size_t newSize = _table.size() * 2;
				vector<Node*> newTable;
				newTable.resize(newSize, nullptr);

				//�����ɱ��ı�ָ��ֱϵ�Ǹ���˳��ǣ��
				for (size_t i = 0; i < _table.size(); i++)
				{
					Node* cur = _table[i];
					while (cur)
					{
						Node* next = cur->_next;

						// ͷ�嵽�±�
						size_t hashi = hf(cur->_kv.first) % newSize;
						cur->_next = nullptr;
						newTable[hashi] = cur;

						cur = next;
					}
					_table[i] = nullptr;
				}
				//������
				_table.swap(newTable);
			}

			size_t hashi = hf(kv.first) % _table.size();
			// ͷ��
			Node* newnode = new Node(kv);
			newnode->_next = _table[hashi];
			_table[hashi] = newnode;
			++_n;
			return true;

		}

		Node* Find(const K& key)const
		{
			HashFunc hf;
			size_t hashi = hf(key) % _table.size();

			Node* cur = _table[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}
				else
				{
					cur = cur->_next;
				}
			}
			return nullptr;
		}

		bool Erase(const K& key)
		{
			HashFunc hf;
			size_t hashi = hf(key) % _table.size();
			Node* prev = nullptr;
			Node* cur = _table[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == nullptr)
					{
						_table[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}

					delete cur;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}

		void Print()
		{
			for (size_t i = 0; i < _table.size(); i++)
			{
				printf("[%d]->", i);
				Node* cur = _table[i];
				while (cur)
				{
					cout << cur->_kv.first << ":" << cur->_kv.second << "->";
					cur = cur->_next;
				}
				printf("NULL\n");
			}
			cout << endl;
		}
	};
}