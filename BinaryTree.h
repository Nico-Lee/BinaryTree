#pragma once
#include<iostream>
#include<queue>
#include<stack>
using namespace std;

enum PointerTag
{
	THREAD,//线索
	LINK,//链接
};

template<class T>
struct BinaryTreeNode
{
	
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	PointerTag _leftTag;
	PointerTag _rightTag;
	T _data;
	BinaryTreeNode(const T& data)
		: _data(data)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
		, _left(NULL)
	{
	}
};

template<class T>
class BinaryTree
{
	
public:
	typedef BinaryTreeNode<T> Node;
	BinaryTree();
	BinaryTree(const T* arry, size_t size, const T& invalid);
	BinaryTree(const BinaryTree<T>& b);
	BinaryTree<T>& operator=(BinaryTree& b);
	~BinaryTree();
	void SequenceOrder();//层序遍历
	void PrevOrder();//前序遍历
	void PrevOrder_Nrec();//前序非递归实现
	void PrevOrderTag();//前序线索化遍历
	void PrevOrderTagPrint();//前序线索化打印
	void MidOrder();//中序遍历
	void MideOrder_Nrec();//中序遍历非递归实现
	void MidOrderTag();//中序线索化
	void MidOrderTagPrint();//中序线索打印
	void RearOrder();//后序遍历
	void RearOrder_Nrec();//后序遍历非递归实现
	//void RearOrderTag();//后序线索化
	//void RearOrderTagPrint();
	size_t LeafCount();//叶子结点个数
	size_t LevelKNodeCount(size_t k);//求第K层节点的个数
	size_t Size();//结点个数
	size_t Deepth();//树的深度
	void GetBinaryTree(const T* prevorder, const T* inorder, size_t size);//根据前序遍历后序遍历序列构造二叉树
	bool IsCompleteBinaryTree();//判断是否是完全二叉树
	int* GetPathSumToN(int n);//得到一条和为n的路径
protected:
	/*Node* prev;*///使用全局的变量在操作系统中会有线程安全的问题，
	//使用传参的方式较好
	Node* _CreatTree(const T* arry, size_t& index, size_t size, const T& invalid);
	Node* _CopyTree(Node* root);
	void _DeleteTree(Node* root);
	void _PrevOrder(Node* root);
	void _PrevOrderTag(Node* root, Node*& prev);
	void _MidOrder(Node* root);
	void _MidOrderTag(Node* root, Node*& prev);
	void _RearOrder(Node* root);
	//void _RearOrderTag(Node* root, Node*& prev);
	size_t _LeafCount(Node* root);
	size_t _Size(Node* root);
	size_t _Deepth(Node* root);
	size_t _LevelKNodeCount(Node* root, size_t k);
	Node* _GetBinaryTreeCore(const T* prevorder, const T* endprevorder
		, const T* inorder, const T* endinorder);
protected:
	Node* _root;
};
