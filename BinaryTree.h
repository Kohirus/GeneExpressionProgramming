#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <string>
using namespace std;

struct BinaryTreeNode
{
	char data;	/* ����ֵ */
	BinaryTreeNode* leftChild;	/* ������ */
	BinaryTreeNode* rightChild;	/* ������ */

	BinaryTreeNode() :data(NULL), leftChild(NULL), rightChild(NULL) {}
	BinaryTreeNode(char x, BinaryTreeNode* l = NULL, BinaryTreeNode* r = NULL)
		:data(x), leftChild(l), rightChild(r) {}
};

/* �������� */
class BinaryTree
{
public:
	typedef BinaryTreeNode Node;
	BinaryTree() : root(NULL), data("") {}
	BinaryTree(char x, Node* l = NULL, Node* r = NULL)
		: data("") { root = new BinaryTreeNode(x, l, r); }
	~BinaryTree() { Destory(root); };

	/** ������������rootΪ���ڵ������ */
	string Output() { return Output(root); }
	
	/**
	 * ��ĳ���ڵ�����ӽڵ�
	 * @param parent: Ҫ����Ľڵ㣬�����ڵ�
	 * @param value: �½ڵ��ֵ
	 * @param left: �Ƿ����������
	 * return: �Ƿ����ɹ�.���������������Ϊ�ջ��߸��ڵ㲻�����򷵻�false,���򷵻�true
	 */ 
	bool Insert(Node*& parent, const char value, bool left = true);

	/**
	 * ����ֵΪvalue����������Ϊ�յĽ��
	 * @param value: Ҫ���ҵĽڵ��ֵ
	 * return: �ɹ��򷵻����ҵ��Ľڵ��ָ��,���򷵻�NULL
	 */
	Node* Find(const char value) { return Find(root, value); }
	
	/** ��ȡ���ڵ� */ 
	Node* Root() { return root; }
	
	/** ��ȡ���ڵ� */ 
	Node* Parent(Node* current) { return (root == NULL || root == current) ? NULL : Parent(root, current); }

	/** ��ȡ���ӽڵ� */
	Node* LeftChild(Node* current) { return (current != NULL) ? current->leftChild : NULL; }
	
	/** ��ȡ���ӽڵ� */
	Node* RightChild(Node* current) { return (current != NULL) ? current->rightChild : NULL; }
	
	/** ���ٶ����� */
	void Destory() { Destory(root); }

private:
	/**
	 * �������������������нڵ�
	 * @param subTree: ��Ҫ����������������ĸ��ڵ�
	 * return: ��subTreeΪ�������������нڵ㾭����������γɵ��ַ���
	 */
	string Output(Node*& subTree);

	/** ������subTreeΪ���ڵ���Ӷ����� */
	void Destory(Node* subTree);

	/** 
	 * ������ֵ�������������Ϊ�յĽڵ�
	 * @param subTree: ��Ҫ���ҵ��������ڵ�
	 * @param value: Ҫ���ҵĽڵ��ֵ
	 * return: ����ҵ��ýڵ��򷵻�true,���򷵻�false
	 */
	Node* Find(Node*& subTree, const char value);

	/**
	 * �ӽ��subTree��ʼ���������current�ĸ��ڵ�
	 * @param subTree: �����ĸ��ڵ�
	 * @param current: Ҫ�����Ľڵ�
	 * return: ����ҵ��򷵻ظ��ڵ�ĵ�ַ�����򷵻�NULL
	 */
	Node* Parent(Node* subTree, Node* current);

private:
	Node* root; // ���ڵ�
	string data;
};

#endif