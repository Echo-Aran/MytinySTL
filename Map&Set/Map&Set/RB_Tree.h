#pragma once
#include<iostream>
using namespace std;

enum Color_Type
{
	Red,
	Black
};

template<class T>
struct RBTreeNode
{
	T _data;
	RBTreeNode* _parent;
	RBTreeNode* _left;
	RBTreeNode* _right;
	Color_Type _color;

	RBTreeNode(const T& data)
		: _data(data)
		, _parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
		, _color(Red)
	{}
		
};

template<class T,class Ref,class Ptr>
struct _TreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef _TreeIterator<T,Ref,Ptr> Self;
	Node* _node;

	typedef _TreeIterator<T, T&, T*> iterator;
	_TreeIterator(const iterator& it)
		:_node(it._node)
	{}


	_TreeIterator(Node* node)
		:_node(node)
	{}

	//T& operator*()
	Ref operator*()
	{
		return _node->_data;
	}
	//T* operator->()
	Ptr operator->()
	{
		return &_node->_data;
	}
	bool operator!=(const Self& s)const
	{
		return _node != s._node;
	}
	bool operator==(const Self& s)const
	{
		return _node == s._node;
	}


	//++ָ�������������һ��
	Self& operator++()
	{
		//���������������������������˵�ֵ
		if (_node->_right)
		{
			Node* mostleft = _node->_right;
			while (mostleft->_left)
			{
				mostleft = mostleft->_left;
			}
			_node = mostleft;
		}
		else//���������Ϊ��
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent)
			{
				if (cur == parent->_left)
				{
					break;
				}
				else
				{
					cur = parent;
					parent = cur->_parent;
				}
			}
			_node = parent;
		}

		//������++ ��--�϶����صĻ��ǵ�������ֻ����������ָ���ֵ�����ı�
		return *this;//???????????????Ϊʲô���Ƿ��� node ��������ͣ�
	}
	Self& operator--()
	{
		//�����������Ϊ�գ����������������Ҷ˵�ֵ
		if (_node->_left)
		{
			Node* subRight = _node->_left;
			while (subRight->_right)
			{
				subRight = subRight->_right;
			}
			_node = subRight;
		}
		else
		{
			Node* cur = Node;
			Node* parent = cur->_parent;
			while (parent&&cur==parent->_left)
			{
				cur = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}

};


template<class K, class T,class KeyOfT>
class RBTree                                                                                                                                                                
{
	typedef RBTreeNode<T> Node;//�ڵ��ڴ�T������

private:
	Node* _root;
	KeyOfT kot;
public:
	//��ͬһ����ģ�壬ͨ�����ƴ����ģ�����ͣ�������ʵ��������ͬ������
	typedef _TreeIterator<T, T&, T*> iterator;
	typedef _TreeIterator<T,const T&,const T*> const_iterator;

	RBTree()
		:_root(nullptr)
	{}

	iterator begin()
	{
		Node* leftMin = _root;
		while (leftMin && leftMin->_left)
		{
			leftMin = leftMin->_left;
		}
		return iterator(leftMin);
	}
	iterator end()
	{
		return iterator(nullptr);
	}
	const_iterator begin()const
	{
		Node* leftMin = _root;
		while (leftMin && leftMin->_left)
		{
			leftMin = leftMin->_left;
		}
		return const_iterator(leftMin);
	}
	const_iterator end()const
	{
		return const_iterator(nullptr);
	}



	Node* find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < key) {
				cur = cur->_right;
			}
			else if (kot(cur->_data) >key) {
				cur = cur->_left;
			}
			else {
				return cur;
			}
		}
		return nullptr;
	}
	pair<iterator, bool> Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_color = Black;
			return make_pair(iterator(_root), true);
		}

		Node* cur = _root;//ָ��ǰ�ڵ��λ��
		Node* parent = nullptr;//��ǰ�ڵ�ĸ��ڵ�

		//�ҵ�����λ��
		while (cur)
		{
			/*if (cur->_kv.first < kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				return false;
			}*/
			if ( kot(cur->_data)<kot(data) ) {
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(cur->_data)> kot(data)) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				return make_pair(iterator(cur), false);
			}
		}

		cur = new Node(data);
		Node* newnode = cur;//��¼newnode��λ�ã�֮��cur���
		cur->_color = Red;
		
		if (kot(cur->_data) < kot(parent->_data)) {
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		//���ڵ�Ϊ��ɫ���������������
		while (parent && parent->_color == Red)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_color == Red)
				{
					// ��ɫ
					parent->_color = uncle->_color = Black;
					grandfather->_color = Red;

					// �������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else//uncle�����ڻ�uncleΪ��
				{
					if (cur == parent->_left)
					{
						//	  g
						//	p
						//c
						RotateR(grandfather);
						parent->_color = Black;
						grandfather->_color = Red;
					}
					else
					{
						//	g
						//p	
						//	c
						RotateL(parent);
						RotateR(grandfather);
						cur->_color = Black;
						grandfather->_color = Red;
					}
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				// u������Ϊ��
				if (uncle && uncle->_color == Red)
				{
					// ��ɫ
					parent->_color = uncle->_color = Black;
					grandfather->_color = Red;

					// �������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_right)
					{
						// g
						//	  p
						//       c
						RotateL(grandfather);
						grandfather->_color = Red;
						parent->_color = Black;
					}
					else
					{
						// g
						//	  p
						// c
						RotateR(parent);
						RotateL(grandfather);
						cur->_color = Black;
						grandfather->_color = Red;
					}
					break;
				}
			}
		}
		_root->_color = Black;
		return make_pair(iterator(newnode), true);
	}
	
	bool IsBalance()
	{
		return _IsBalance(_root);
	}

	int Height()
	{
		return _Height(_root);
	}

	bool checkColor(Node* root, int blacknum, int basenum)
	{
		if (root == nullptr)
		{
			if (blacknum != basenum)
			{
				return false;
			}
			return true;
		}

		if (root->_color == Black)
		{
			++blacknum;
		}

		if (root->_parent && root->_parent->_color == Red && root->_color == Red)
		{
			cout << root->_kv.first << "����������ɫ�ڵ�" << endl;
			return false;
		}

		return  checkColor(root->_left, blacknum, basenum) && checkColor(root->_right, blacknum, basenum);
	}


private:
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pparent = parent->_parent;

		/*1.����subRL��parent֮��Ĺ�ϵ
		����������*/
		parent->_right = subRL;
		if (subRL) {
			subRL->_parent = parent;
		}

		//2.����subR��parent֮��Ĺ�ϵ
		//������������������
		subR->_left = parent;
		parent->_parent = subR;

		/*3.����pparent��subR֮��Ĺ�ϵ
		����һ���ڵ㽨������*/
		if (parent == _root)
		{
			_root = subR;
			subR->_parent == nullptr;
		}
		else
		{
			subR->_parent = pparent;
			if (parent == pparent->_left) {
				pparent->_left = subR;
			}
			else {
				pparent->_right = subR;
			}
		}
	}
	void RotateR(Node* parent)
	{

		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* pparent = parent->_parent;


		//����
		parent->_left = subLR;
		if (subLR) {
			subLR->_parent = parent;
		}

		//������������������
		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			subL->_parent = pparent;
			if (parent == pparent->_left) {
				pparent->_left = subL;
			}
			else {
				pparent->_right = subL;
			}

		}
	}
	int _Height(Node* root)
	{
		if (!root) {
			return 0;
		}
		int left = _Height(root->_left);
		int right = _Height(root->_right);

		return left > right ? left + 1 : right + 1;
	}
	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}
		if (root->_color != Black)
		{
			return false;
		}

		int basenum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_color == Black) {
				++basenum;
			}
			cur = cur->_left;
		}

		return checkColor(root, 0, basenum);
	}

};