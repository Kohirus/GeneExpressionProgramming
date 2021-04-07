#include "BinaryTree.h"

bool BinaryTree::Insert(Node*& parent, const char value, bool left)
{
	if (parent != NULL)
	{
		// 默认插入左节点
		if (left)
		{
			if (parent->leftChild == NULL)
			{
				Node* new_node = new Node(value);
				parent->leftChild = new_node;
				return true;
			}
			else if (parent->rightChild == NULL)
			{
				Node* new_node = new Node(value);
				parent->rightChild = new_node;
				return true;
			}
		}
		else
		{
			if (parent->rightChild == NULL)
			{
				Node* new_node = new Node(value);
				parent->rightChild = new_node;
				return true;
			}
			else if (parent->leftChild == NULL)
			{
				Node* new_node = new Node(value);
				parent->leftChild = new_node;
				return true;
			}
		}
	}
	return false;
}

string BinaryTree::Output(Node*& subTree)
{
	if (subTree != NULL)
	{
		data += "(";
		Output(subTree->leftChild);
		data += string(1,subTree->data);
		Output(subTree->rightChild);
		data += ")";
	}
	return data;
}

BinaryTree::Node* BinaryTree::Find(Node*& subTree, const char value)
{
	Node* target = NULL;
	if (subTree != NULL)
	{
		if (subTree->data == value && !subTree->leftChild && !subTree->rightChild)
		{
			return subTree;
		}
		else
		{
			if ((target = Find(subTree->leftChild, value)) != NULL)
				return target;
			else
				return Find(subTree->rightChild, value);
		}
	}
	else
		return NULL;
}

void BinaryTree::Destory(Node* subTree)
{
	if (subTree != NULL)
	{
		Destory(subTree->leftChild);
		Destory(subTree->rightChild);
		delete subTree;
		subTree = NULL;
	}
}

BinaryTree::Node* BinaryTree::Parent(Node* subTree, Node* current)
{
	{
		if (subTree == NULL)
		{
			return NULL;
		}
		if (subTree->leftChild == current || subTree->rightChild == current) //如果找到，返回父节点subTree
		{
			return subTree;
		}
		Node* p;
		if ((p = Parent(subTree->leftChild, current)) != NULL) //递归在左子树中搜索
		{
			return p;
		}
		else
		{
			return Parent(subTree->rightChild, current); //递归右子树中搜索
		}
	}
}