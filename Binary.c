#pragma once
#include<iostream>
#include<queue>
#include<stack>
using namespace std;

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	T _data;
	BinaryTreeNode(const T& data)
		: _data(data)
		, _right(NULL)
		, _left(NULL)
	{
	}

};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const T* arry, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreatTree(arry, index, size, invalid);
	}
	BinaryTree(const BinaryTree<T>& b)
	{
		_root = _CopyTree(b._root);
	}
	BinaryTree<T>& operator=(BinaryTree& b)
	{
		//if (this != &b)
		//{
		//	BinaryTree<T> tmp = b;
		//	delete _root;
		//	_root = tmp._root;
		//}
		//return *this;

		//现代写法
		swap(_root, b._root);
		return *this;
	}
	~BinaryTree()
	{
		_DeleteTree(_root);
	}
	void SequenceOrder()//层序遍历
	{
		queue<BinaryTreeNode<T>*> q;
		if (_root)
			q.push(_root);
		while (!q.empty())
		{
			if (q.front()->_left)
			{
				q.push(q.front()->_left);
			}
			if (q.front()->_right)
			{
				q.push(q.front()->_right);
			}
			cout << q.front()->_data<< " ";
			q.pop();
		}
	}
	void PrevOrder()//前序遍历
	{
		_PrevOrder(_root);
	}
	void PrevOrder_Nrec()//前序非递归实现
	{
		stack<Node*> s;
		if (_root)
			s.push(_root);
		while (!s.empty())
		{
			Node* top = s.top();
			cout << top->_data << " ";
			s.pop();
			if (top->_right)
			{
				s.push(top->_right);
			}
			if (top->_left)
			{
				s.push(top->_left);
			}
		}
	}
	void MidOrder()//中序遍历
	{
		_MidOrder(_root);
	}
	void MideOrder_Nrec()//中序遍历非递归实现
	{
		stack<Node*> s;
		Node* cur = _root;
		while (!s.empty()||cur)
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			if (!s.empty())
			{
				Node* tmp = s.top();
				s.pop();
				cout << tmp->_data << " ";
				cur = tmp->_right;
			}
		}
	}
	void RearOrder()//后序遍历
	{
		_RearOrder(_root);
	}
	void RearOrder_Nrec()//后序遍历非递归实现
	{
		stack<Node*> s;
		Node* cur = _root;
		Node* prev = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			if (!s.empty())
			{
				Node* top = s.top();
				if (top->_right == prev)//判断是否已经访问了根节点的右子树
				{
					s.pop();
					cout << top->_data << " ";
					prev = top;
				}
				else
				{
					cur = top->_right;//如果没有就去访问右子树
					prev = top->_right;
				}
			}
		}
	}
	size_t LeafCount()
	{
		return _LeafCount(_root);
	}
	size_t Size()
	{
		return _Size(_root);
	}
	size_t Deepth()
	{
		return _Deepth(_root);
	}


protected:
	BinaryTreeNode<T>* _CreatTree(const T* arry, size_t& index, size_t size, const T& invalid)
	{
		BinaryTreeNode<T>* root = NULL;
		if (index < size && arry[index] != invalid)
		{
			root = new BinaryTreeNode<T>(arry[index]);
			root->_left = _CreatTree(arry, ++index, size, invalid);
			root->_right = _CreatTree(arry, ++index, size, invalid);
		}
		return root;
	}
	BinaryTreeNode<T>* _CopyTree(BinaryTreeNode<T>* root)
	{
		BinaryTreeNode<T>* node = NULL;//不能使用_root,_root是所有_CopyTree共有的
		if (root == NULL)
		{
			return NULL;
		}
		node = new BinaryTreeNode<T>(root->_data);
		node->_left = _CopyTree(root->_left);
		node->_right = _CopyTree(root->_right);
		return node;
	}
	void _DeleteTree(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->_left == NULL && root->_right == NULL)
		{
			delete root;
			return;//删除节点后返回
		}
		_DeleteTree(root->_left);
		_DeleteTree(root->_right);
	}
	void _PrevOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		cout << root->_data <<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	
	void _MidOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		_MidOrder(root->_left);
		cout << root->_data << " ";
		_MidOrder(root->_right);
	}
	void _RearOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		_RearOrder(root->_left);
		_RearOrder(root->_right);
		cout << root->_data << " ";
	}
	size_t _LeafCount(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		if (root->_left==NULL && root->_right ==NULL)
		{
			return 1;
		}

		return (_LeafCount(root->_left)+_LeafCount(root->_right));
	}
	size_t _Size(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	size_t _Deepth(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		size_t leftDeep = _Deepth(root->_left)+1;
		size_t rightDeep = _Deepth(root->_right)+1;
		return leftDeep > rightDeep ? leftDeep: rightDeep;
	}

protected:
	BinaryTreeNode<T>* _root;
};
