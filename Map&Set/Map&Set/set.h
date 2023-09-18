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
			const K& operator()(const K& key)//�������K���͵�
			{
				return key;
			}
		};
		RBTree<K, K, setKeyofT> _t;

	public:
		//�ײ��Ƕ����ķ�װ
		typedef typename RBTree<K, K, setKeyofT>::const_iterator iterator;//���������������϶���const���������������set�е�ֵ�޸�
		typedef typename RBTree<K, K, setKeyofT>::const_iterator const_iterator;
		
		iterator begin()const
		{
			//������������_t����const���Σ����õ���RBTree��const_iterator begin()const
			//���������set�У�const��iterator�����
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