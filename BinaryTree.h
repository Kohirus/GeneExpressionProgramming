#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <string>
using namespace std;

struct BinaryTreeNode
{
	char data;	/* 数据值 */
	BinaryTreeNode* leftChild;	/* 左子树 */
	BinaryTreeNode* rightChild;	/* 右子树 */

	BinaryTreeNode() :data(NULL), leftChild(NULL), rightChild(NULL) {}
	BinaryTreeNode(char x, BinaryTreeNode* l = NULL, BinaryTreeNode* r = NULL)
		:data(x), leftChild(l), rightChild(r) {}
};

/* 二叉树类 */
class BinaryTree
{
public:
	typedef BinaryTreeNode Node;
	BinaryTree() : root(NULL), data("") {}
	BinaryTree(char x, Node* l = NULL, Node* r = NULL)
		: data("") { root = new BinaryTreeNode(x, l, r); }
	~BinaryTree() { Destory(root); };

	/** 中序遍历输出以root为根节点的内容 */
	string Output() { return Output(root); }
	
	/**
	 * 向某个节点添加子节点
	 * @param parent: 要插入的节点，即父节点
	 * @param value: 新节点的值
	 * @param left: 是否插入左子树
	 * return: 是否插入成功.如果左、右子树均不为空或者父节点不存在则返回false,否则返回true
	 */ 
	bool Insert(Node*& parent, const char value, bool left = true);

	/**
	 * 查找值为value且左右子树为空的结点
	 * @param value: 要查找的节点的值
	 * return: 成功则返回所找到的节点的指针,否则返回NULL
	 */
	Node* Find(const char value) { return Find(root, value); }
	
	/** 获取根节点 */ 
	Node* Root() { return root; }
	
	/** 获取父节点 */ 
	Node* Parent(Node* current) { return (root == NULL || root == current) ? NULL : Parent(root, current); }

	/** 获取左子节点 */
	Node* LeftChild(Node* current) { return (current != NULL) ? current->leftChild : NULL; }
	
	/** 获取右子节点 */
	Node* RightChild(Node* current) { return (current != NULL) ? current->rightChild : NULL; }
	
	/** 销毁二叉树 */
	void Destory() { Destory(root); }

private:
	/**
	 * 中序遍历二叉树输出所有节点
	 * @param subTree: 需要输出二叉树的子树的根节点
	 * return: 以subTree为根的子树的所有节点经过中序遍历形成的字符串
	 */
	string Output(Node*& subTree);

	/** 销毁以subTree为根节点的子二叉树 */
	void Destory(Node* subTree);

	/** 
	 * 查找数值相等且左右子树为空的节点
	 * @param subTree: 需要查找的子树根节点
	 * @param value: 要查找的节点的值
	 * return: 如果找到该节点则返回true,否则返回false
	 */
	Node* Find(Node*& subTree, const char value);

	/**
	 * 从结点subTree开始，搜索结点current的父节点
	 * @param subTree: 子树的根节点
	 * @param current: 要搜索的节点
	 * return: 如果找到则返回父节点的地址，否则返回NULL
	 */
	Node* Parent(Node* subTree, Node* current);

private:
	Node* root; // 根节点
	string data;
};

#endif