#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>
using namespace std;

void printNSpace(int n)
{
	for (int i = 0; i < n - 1; i++)
		cout << " ";
}

void printInteger(int &n)
{
	cout << n << " ";
}

template <class T>
class Node
{
public:
	T data;
	Node<T> *left;
	Node<T> *right;

	Node(const T &val)
	{
		data = val;
		left = right = NULL;
	}
};

template <class T>
class BinaryTree
{
private:
	Node<T> *root;
	int size;

protected:
	void clearRec(Node<T> *&);
	void constructFromArrayRec(Node<T> *&, int, T **&, int n);

	// TODO Methods
	int getHeightRec(Node<T> *);
// TODO
bool checknode(Node<T>*);

public:
	BinaryTree()
	{
		this->root = NULL;
		this->size = 0;
	}

	~BinaryTree()
	{
		this->clear();
	}

	void clear();
	void constructFromArray(T **&, int n);
	void printTreeStructure();

	// TODO Methods
	int getHeight();
	bool isBST();
};

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string element;
	getline(ifs, element);
	int size = stoi(element);

	int **data = new int *[size];

	for (int i = 0; i < size; i++)
	{

		getline(ifs, element);

		if (element != "NULL")
		{
			data[i] = new int;
			*(data[i]) = stoi(element);
		}
		else
			data[i] = NULL;
	}

	BinaryTree<int> *tree = new BinaryTree<int>();
	tree->constructFromArray(data, size);
	tree->printTreeStructure();

	cout << (tree->isBST() ? "This is a BST" : "This is not a BST");

	delete tree;

	ifs.close();

	return 0;
}

// TODO
template<class T>
bool BinaryTree<T>::checknode(Node<T>* node) {
	int x = node->data;
	Node<T>* Le = node->left;
	Node<T>* Ri = node->right;
	queue<Node<T>*> q;
	while (Le != NULL) {
		if (Le->data >= x) return false;
		if (Le->left != NULL) q.push(Le->left);
		if (Le->right != NULL) q.push(Le->right);
		if (!q.empty()) {
			Le = q.front();
			q.pop();
		}
		else Le = NULL;
	}
	while (Ri != NULL) {
		if (Ri->data < x) return false;
		if (Ri->left != NULL) q.push(Ri->left);
		if (Ri->right != NULL) q.push(Ri->right);
		if (!q.empty()) {
			Ri = q.front();
			q.pop();
		}
		else Ri = NULL;
	}
	return true;
}

template <class T>
bool BinaryTree<T>::isBST()
{
// TODO
Node<T>* tmp = root;
	queue<Node<T>*> q;
	while (tmp != NULL) {
		if (!checknode(tmp)) return false;
		if (tmp->left != NULL) q.push(tmp->left);
		if (tmp->right != NULL) q.push(tmp->right);
		if (!q.empty()) {
			tmp = q.front();
			q.pop();
		}
		else tmp = NULL;
	}
	return true;        
}

template <class T>
int BinaryTree<T>::getHeightRec(Node<T> *node)
{
// TODO
if (node == NULL)
		return 0;
	int lh = this->getHeightRec(node->left);
	int rh = this->getHeightRec(node->right);
	return (lh > rh ? lh : rh) + 1;     
}

template <class T>
int BinaryTree<T>::getHeight()
{
// TODO
	return this->getHeightRec(this->root);
}

template <class T>
void BinaryTree<T>::clearRec(Node<T> *&node)
{
	if (node != NULL)
	{
		this->clearRec(node->left);
		this->clearRec(node->right);
		delete node;
		node = NULL;
	}
}

template <class T>
void BinaryTree<T>::clear()
{
	this->clearRec(this->root);
	this->size = 0;
}

template <class T>
void BinaryTree<T>::constructFromArrayRec(Node<T> *&node, int index, T **&array, int n)
{
	if (index < n)
	{
		if (array[index] == NULL)
		{
			node = NULL;
		}
		else
		{
			Node<T> *temp = new Node<T>(*(array[index]));
			node = temp;
			this->size++;

			this->constructFromArrayRec(node->left, 2 * index + 1, array, n);
			this->constructFromArrayRec(node->right, 2 * index + 2, array, n);
		}
	}
}

template <class T>
void BinaryTree<T>::constructFromArray(T **&array, int n)
{
	this->clear();
	this->constructFromArrayRec(this->root, 0, array, n);
}

template <class T>
void BinaryTree<T>::printTreeStructure()
{
	int height = this->getHeight();

	if (this->root == NULL)
	{
		cout << "NULL\n";
		return;
	}
	queue<Node<T> *> q;
	q.push(root);
	Node<T> *temp;
	int count = 0;
	int maxNode = 1;
	int level = 0;
	int space = pow(2, height);
	printNSpace(space / 2);
	while (!q.empty())
	{
		temp = q.front();
		q.pop();

		if (temp == NULL)
		{
			cout << " ";
			q.push(NULL);
			q.push(NULL);
		}
		else
		{

			cout << temp->data;
			q.push(temp->left);
			q.push(temp->right);
		}
		printNSpace(space);
		count++;
		if (count == maxNode)
		{
			cout << endl;
			count = 0;
			maxNode *= 2;
			level++;
			space /= 2;
			printNSpace(space / 2);
		}
		if (level == height)
			return;
	}
}