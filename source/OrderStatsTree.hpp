#pragma once

#include <functional>

namespace ToopLoox
{

template <typename Key>
class OrderStatsTree
{
public:
	enum NodeType
	{
		ROOT, LEFT, RIGHT
	};

private:
	struct Node
	{
		~Node()
		{
			if (left)
			{
				delete left;
			}

			if (right)
			{
				delete right;
			}
		}

		void update()
		{
			height = 1 + std::max(leftHeight(), rightHeight());
			countRecursive = count + leftCountRecursive() + rightCountRecursive();
		}

		unsigned leftHeight() const
		{
			return left ? left->height : 0;
		}

		unsigned rightHeight() const
		{
			return right ? right->height : 0;
		}

		unsigned leftCountRecursive() const
		{
			return left ? left->countRecursive : 0;
		}

		unsigned rightCountRecursive() const
		{
			return right ? right->countRecursive : 0;
		}

		Key key{};
		Node* left = nullptr;
		Node* right = nullptr;
		unsigned count = 0;
		unsigned countRecursive = 0;
		unsigned height = 0;
	};

public:
	~OrderStatsTree()
	{
		if (root)
		{
			delete root;
		}
	}

	void add(Key key)
	{
		root = addInternal(key, root);
	}

	unsigned getSize() const
	{
		return root ? root->countRecursive : 0;
	}

	Key operator[](unsigned index) const
	{
		if (index >= getSize())
		{
			throw std::out_of_range("index out of range");
		}

		Node* current = root;
		while (true)
		{
			if (index < current->leftCountRecursive())
			{
				current = current->left;
				continue;
			}

			index -= current->leftCountRecursive();

			if (index < current->count)
			{
				return current->key;
			}

			index -= current->count;
			current = current->right;
		}
	}

	template <typename NodeCallback>
	void forEachPreorder(const NodeCallback& callback)
	{
		if (root)
		{
			forEachPreorder(callback, root->key, root, NodeType::ROOT);
		}
	}

private:
	template <typename NodeCallback>
	void forEachPreorder(const NodeCallback& callback, Key parentKey, Node* node, NodeType type)
	{
		callback(node->key, parentKey, node->height, node->count, node->countRecursive, type);

		if (node->left)
		{
			forEachPreorder(callback, node->key, node->left, NodeType::LEFT);
		}

		if (node->right)
		{
			forEachPreorder(callback, node->key, node->right, NodeType::RIGHT);
		}
	}

	Node* addInternal(Key key, Node* node)
	{
		if (!node)
		{
			Node* newNode = new Node();
			newNode->count = newNode->countRecursive = 1;
			newNode->key = key;
			newNode->height = 1;
			return newNode;
		}
		
		++node->countRecursive;

		if (key < node->key)
		{
			node->left = addInternal(key, node->left);
		}
		else if (key > node->key)
		{
			node->right = addInternal(key, node->right);
		}
		else
		{
			++node->count;
			return node;
		}

		node->update();
		auto balance = static_cast<int>(node->leftHeight()) - static_cast<int>(node->rightHeight());

		if (balance > 1 && key < node->left->key)
		{
			return rotateRight(node);
		}

		if (balance < -1 && key > node->right->key)
		{
			return rotateLeft(node);
		}

		if (balance > 1 && key > node->left->key)
		{
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}

		if (balance < -1 && key < node->right->key)
		{
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}

		return node;
	}


	Node* rotateRight(Node* node)
	{
		Node* newRoot = node->left;
		Node* temp = newRoot->right;
		newRoot->right = node;
		node->left = temp;
		node->update();
		newRoot->update();
		return newRoot;
	}

	Node* rotateLeft(Node* node)
	{
		Node* newRoot = node->right;
		Node* temp = newRoot->left;
		newRoot->left = node;
		node->right = temp;
		node->update();
		newRoot->update();
		return newRoot;
	}

private:
	Node* root = nullptr;
};


}
