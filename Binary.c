#define _CRT_SECURE_NO_WARNINGS 1
#include"BinaryTree.h"
#include<assert.h>



template<class T>
BinaryTree<T>::BinaryTree()
	:_root(NULL)
{}

template<class T>
BinaryTree<T>::BinaryTree(const T* arry, size_t size, const T& invalid)
{
	size_t index = 0;
	_root = _CreatTree(arry, index, size, invalid);
}
template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& b)
{
	_root = _CopyTree(b._root);
}
template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree& b)
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
template<class T>
BinaryTree<T>::~BinaryTree()
{
	_DeleteTree(_root);
}
template<class T>
void BinaryTree<T>::SequenceOrder()//层序遍历
{
	queue<Node*> q;
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
		cout << q.front()->_data << " ";
		q.pop();
	}
}
template<class T>
void BinaryTree<T>::PrevOrder()//前序遍历
{
	_PrevOrder(_root);
}
template<class T>
void BinaryTree<T>::PrevOrder_Nrec()//前序非递归实现
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
template<class T>
void BinaryTree<T>::PrevOrderTag()
{
	Node* prev = NULL;
	_PrevOrderTag(_root, prev);
}
template<class T>
void BinaryTree<T>::MidOrder()
{
	_MidOrder(_root);
}
template<class T>
void BinaryTree<T>::MideOrder_Nrec()
{
	stack<Node*> s;
	Node* cur = _root;
	while (!s.empty() || cur)
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
template<class T>
void BinaryTree<T>::MidOrderTag()
{
	_MidOrderTag(_root);
}

template<class T>
void BinaryTree<T>::RearOrder()
{
	_RearOrder(_root);
}
template<class T>
void BinaryTree<T>::RearOrder_Nrec()
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
template<class T>
size_t BinaryTree<T>::LeafCount()
{
	return _LeafCount(_root);
}

template<class T>
size_t BinaryTree<T>::LevelKNodeCount(size_t k)
{
	return _LevelKNodeCount(_root, k);
}
template<class T>
size_t BinaryTree<T>::Size()
{
	return _Size(_root);
}
template<class T>
size_t BinaryTree<T>::Deepth()
{
	return _Deepth(_root);
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::_CreatTree(const T* arry, size_t& index, size_t size, const T& invalid)
{
	Node* root = NULL;
	if (index < size && arry[index] != invalid)
	{
		root = new Node(arry[index]);
		root->_left = _CreatTree(arry, ++index, size, invalid);
		root->_right = _CreatTree(arry, ++index, size, invalid);
	}
	return root;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::_CopyTree(Node* root)
{
	if (root == NULL)
	{
		return NULL;
	}
	Node* node = NULL;//不能使用_root,_root是所有_CopyTree共有的
	node = new Node(root->_data);
	node->_left = _CopyTree(root->_left);
	node->_right = _CopyTree(root->_right);
	return node;
}

template<class T>
void BinaryTree<T>::_DeleteTree(Node* root)
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

template<class T>
void BinaryTree<T>::_PrevOrder(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	cout << root->_data << " ";
	_PrevOrder(root->_left);
	_PrevOrder(root->_right);
}

template<class T>
void BinaryTree<T>::_PrevOrderTag(Node* root , Node*& prev)
{
	if (root == NULL)
		return;
	if (!root->_left)
	{
		root->_leftTag = THREAD;
		root->_left = prev;
	}
	if (prev && !prev->_right)
	{
		prev->_rightTag = THREAD;
		prev->_right = root;
	}
	prev = root;
	if (root->_leftTag == LINK)
		_PrevOrderTag(root->_left, prev);
	if (root->_rightTag == LINK)
		_PrevOrderTag(root->_right, prev);
}


template<class T>
void BinaryTree<T>::_MidOrder(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	_MidOrder(root->_left);
	cout << root->_data << " ";
	_MidOrder(root->_right);
}
template<class T>
void BinaryTree<T>::_MidOrderTag(Node* root ,Node*& prev)
{
	if (root == NULL)
	{
		return;
	}

	_MidOrderTag(root->_left, prev);


	if (!root->_left)
	{
		root->_leftTag = THREAD;
		root->_left = prev;
	}
	if (prev&&!prev->_right)
	{
		prev->_rightTag = THREAD;
		prev->_right = root;
	}
	prev = root;

	_MidOrderTag(root->_right, prev);
}
template<class T>
void BinaryTree<T>::_RearOrder(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	_RearOrder(root->_left);
	_RearOrder(root->_right);
	cout << root->_data << " ";
}
//template<class T>
//void BinaryTree<T>::_RearOrderTag(Node* root)//后序线索二叉树
//{
//	if (root == NULL)
//	{
//		return;
//	}
//	if (root->_leftTag == LINK)
//		_RearOrderTag(root->_left);
//	if (root->_rightTag == LINK)
//		_RearOrderTag(root->_right);
//
//	if (!root->_left)
//	{
//		root->_leftTag = THREAD;
//		root->_left = prev;
//	}
//	if (prev&&!prev->_right)
//	{
//		prev->_rightTag = THREAD;
//		prev->_right = root;
//	}
//	prev = root;
//
//}
//void RearOrderTagPrint()
//{
//	Node* cur = _root;
//	Node* flag = NULL;
//	while (cur)
//	{
//		while (cur->_leftTag == LINK)
//		{
//			cur = cur->_left;
//		}
//		if (cur->_left)
//		{
//			cur = cur->_left;
//			cout << cur->_data << " ";
//		}
//		else
//		{
//
//		}
//	}
//}

template<class T>
size_t BinaryTree<T>::_LeafCount(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->_left == NULL && root->_right == NULL)
	{
		return 1;
	}

	return (_LeafCount(root->_left) + _LeafCount(root->_right));
}
template<class T>
size_t BinaryTree<T>::_Size(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return _Size(root->_left) + _Size(root->_right) + 1;
}
template<class T>
size_t BinaryTree<T>::_Deepth(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	size_t leftDeep = _Deepth(root->_left) + 1;
	size_t rightDeep = _Deepth(root->_right) + 1;
	return leftDeep > rightDeep ? leftDeep : rightDeep;
}
template<class T>
size_t BinaryTree<T>::_LevelKNodeCount(Node* root, size_t k)
{
	if (root == NULL)
	{
		return 0;
	}
	if (k == 1)
	{
		return 1;
	}
	return _LevelKNodeCount(root->_left, k - 1)
		+ _LevelKNodeCount(root->_right, k - 1);
}

template<class T>
void BinaryTree<T>::GetBinaryTree(const T* prevorder, const T* inorder,size_t size)
{
	if (prevorder == NULL || inorder == NULL || size < 0)
		return;
	_root = _GetBinaryTreeCore(prevorder, prevorder + size - 1, inorder, inorder + size - 1);
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::_GetBinaryTreeCore(const T* prevorder, const T* endprevorder
	, const T* inorder, const T* endinorder)
{
	T rootvalue = prevorder[0];
	Node* root = new Node(rootvalue);
	root->_data = rootvalue;
	root->_left = root->_right = NULL;
	if (prevorder == endprevorder)
	{
		if (inorder == endinorder && *prevorder == *inorder)
		{
			return root;
		}
		else
		{
			cout << "invalid input" << endl;
			assert(0);
		}

	}
	const T* inordertmp = inorder;
	while (inordertmp <= endinorder&&*inordertmp != rootvalue)
		++inordertmp;
	if (inordertmp == endinorder && *inordertmp != rootvalue)//没有找到根
	{
		cout << "invalie input";
		assert(0);
	}
	int leftsize = inordertmp - inorder;//中序序列左边剩余的个数
	const T* leftendprevorder = prevorder + leftsize;
	if (leftsize > 0)
	{
		root->_left = _GetBinaryTreeCore(prevorder + 1, leftendprevorder, inorder, inordertmp - 1);
	}
	if (leftsize < endprevorder - prevorder)
	{
		root->_right = _GetBinaryTreeCore(leftendprevorder+1, endprevorder, inordertmp+1, endinorder);
	}
	return root;
}


template<class T>
bool BinaryTree<T>::IsCompleteBinaryTree()
{
	if (_root == NULL)
		return true;
	queue<Node*> que;
	que.push(_root);
	bool flag = false;
	while (!que.empty())
	{
		Node* temp = que.front();
		que.pop();
		if (flag)
		{
			if (temp->_left || temp->_right)
				return false;
		}
		else
		{
			if (temp->_left && temp->_right)
			{
				que.push(temp->_left);
				que.push(temp->_right);
			}
			else if (temp->_right)
				return false;
			else if (temp->_left)
			{
				que.push(temp->_left);
				flag = true;
			}
			else
				flag = true;
		}
	}
	return true;
}
