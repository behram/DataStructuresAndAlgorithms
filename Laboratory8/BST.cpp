#include <iostream>
#include <fstream>

using namespace std;

struct Element
{
	string key;
	int value;
};

struct Node
{
	Element elem;
	Node *parent;
	Node *leftChild;
	Node *rightChild;
};

struct BST
{
	Node *root;
};

void init(BST & tree)
{
	tree.root = NULL;
	return;
}

bool isEmpty(BST &tree)
{
	return (tree.root == NULL);
}

void insertElem(BST & tree, string key)
{
	Node *p = NULL;
	Node *q = tree.root;

	if(!isEmpty(tree))
	{
		while(q != NULL)
		{
			if(key == q->elem.key)
			{
				q->elem.value++;
				return;
			}
			p = q;
			if(key < q->elem.key)
			{
				q = q->leftChild;
			}
			else
			{
				q = q->rightChild;
			}
		}
	}

	Node *n = new Node();
	Element el;

	el.key = key;
	el.value = 1;
	n->elem = el;
	n->parent = p;

	if(p == NULL)
	{
		tree.root = n;
	}
	else if(key < p->elem.key)
	{
		p->leftChild = n;
	}
	else
	{
		p->rightChild = n;
	}
	return;
}

Node *findNode(Node *node, string key)
{
	Node *p = node;
	while(p != NULL)
	{
		if(key < p->elem.key)
		{
			p = p->leftChild;
		}
		else if(key > p->elem.key)
		{
			p = p->rightChild;
		}
		else
		{
			return p;
		}
	}
	return NULL;
}

Node *minimalNode(Node *node)
{
	Node *p = node;
	while(p != NULL && p->leftChild != NULL)
	{
		if(p->leftChild->elem.key > node->elem.key)
		{
			p = p->leftChild;
		}
		else
		{
			p = p->rightChild;
		}
	}
	return p;
}

bool removeKey(BST & tree, string key)
{
	Node *n = findNode(tree.root, key);
	if(n == NULL)
	{
		return false;
	}

	Node *p = NULL;
	Node *q = NULL;

	if(n->leftChild == NULL || n->rightChild == NULL)
	{
		p = n;
	}
	else
	{
		p = minimalNode(n);
	}

	if(p->leftChild != NULL)
	{
		q = p->leftChild;
	}
	else
	{
		q = p->rightChild;
	}

	if(q != NULL)
	{
		q->parent = p->parent;
	}

	if(p->parent == NULL)
	{
		tree.root = q;
	}
	else if(p == p->parent->leftChild)
	{
		p->parent->leftChild = q;
	}
	else
	{
		p->parent->rightChild = q;
	}

	if(p != n)
	{
		n->elem.key = p->elem.key;
		n->elem.value = p->elem.value;
	}

	return true;
}

void numberOfNodes(Node *n, int &counter)
{
	if(n != NULL)
	{
		counter++;
	}
	if(n->leftChild != NULL)
	{
		numberOfNodes(n->leftChild, counter);
	}
	if(n->rightChild != NULL)
	{
		numberOfNodes(n->rightChild, counter);
	}
	return;
}

int numberOfNodes(BST & tree)
{
	if(isEmpty(tree))
	{
		return 0;
	}
	int c = 0;
	numberOfNodes(tree.root, c);
	return c;
}

Node *findMaxValue(Node *node)
{
	if(node == NULL)
	{
		Node* res = new Node;
		res->elem.value = -1;
		return res;
	}

	Node *l = findMaxValue(node->leftChild);
	Node *c = node;
	Node *r = findMaxValue(node->rightChild);

	if(l->elem.value >= c->elem.value && l->elem.value >= r->elem.value)
	{
		return l;
	}
	else if(r->elem.value >= l->elem.value && r->elem.value >= c->elem.value)
	{
		return r;
	}
	return c;
}

void printTopTen(BST & tree)
{
	int s = std::min(10, numberOfNodes(tree));
	Node *maxValue;

	cout << "Top 10 Most Often Words\n";
	for(int i = 0; i < s; i++)
	{
		maxValue = findMaxValue(tree.root);
		cout << i+1 << " - " << maxValue->elem.key << " "<< maxValue->elem.value << " times occurred\n";
		removeKey(tree, maxValue->elem.key);
	}
}