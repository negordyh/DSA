#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>
using namespace std;

enum BalanceValue
{
	LH = -1,
	EH = 0,
	RH = 1
};

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
	BalanceValue balance;

	Node(const T &val)
	{
		data = val;
		left = right = NULL;
		balance = EH;
	}
};

template <class T>
class AVL
{
private:
	Node<T> *root;

protected:
	void clearRec(Node<T> *&);
	int getHeightRec(Node<T> *);
	Node<T> *rotateRight(Node<T> *&node);
	Node<T> *rotateLeft(Node<T> *&node);
	Node<T> *leftBalance(Node<T> *&node, bool &taller);
	Node<T> *rightBalance(Node<T> *&node, bool &taller);
	Node<T> *removeLeftBalance(Node<T> *&node, bool &shorter);
	Node<T> *removeRightBalance(Node<T> *&node, bool &shorter);

	//TODO Methods
	Node<T> *insertRec(Node<T> *&node, const T &value, bool &taller);
	Node<T> *removeRec(Node<T> *&node, const T &value, bool &shorter, bool &success);

public:
	AVL()
	{
		this->root = NULL;
	}

	~AVL()
	{
		this->clear();
	}

	void clear();
	int getHeight();
	void printTreeStructure();

	// TODO Methods
	void insert(const T &value);
	void remove(const T &value);
};

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string line;
	getline(ifs, line);
	int size = stoi(line);

	AVL<int> *tree = new AVL<int>();
	for (int i = 0; i < size; i++)
	{
		getline(ifs, line);
		tree->insert(stoi(line));
	}

	cout << "After insertion: " << endl;
	tree->printTreeStructure();

	getline(ifs, line);
	size = stoi(line);

	for (int i = 0; i < size; i++)
	{
		getline(ifs, line);
		int number = stoi(line);
		tree->remove(number);
		cout << "After delete " << number << ":" << endl;
		tree->printTreeStructure();
	}

	delete tree;

	ifs.close();

	return 0;
}

template <class T>
Node<T> *AVL<T>::rotateRight(Node<T> *&node)
{
	// TODO
Node<T>* tmp = node;
	Node<T>* pNew = new Node<T>(tmp->data);
	pNew->balance = tmp->balance;
	pNew->right = tmp->right;
	pNew->left = tmp->left->right;
	tmp->right = pNew;
	tmp->data = tmp->left->data;
	tmp->balance = tmp->left->balance;
	tmp->left = tmp->left->left;
    return tmp;
}

template <class T>
Node<T> *AVL<T>::rotateLeft(Node<T> *&node)
{
	// TODO
Node<T>* tmp = node;
	Node<T>* pNew = new Node<T>(tmp->data);
	pNew->balance = tmp->balance;
	pNew->left = tmp->left;
	pNew->right = tmp->right->left;
	tmp->left = pNew;
	tmp->data = tmp->right->data;
	tmp->balance = tmp->right->balance;
	tmp->right = tmp->right->right;
    return tmp;
}

template <class T>
Node<T> *AVL<T>::insertRec(Node<T> *&node, const T &value, bool &taller)
{
	// TODO
if (node == NULL) {
		node = new Node<T>(value);
		taller = true;
		return node;
	}
	if (value < node->data) {
		node->left = insertRec(node->left, value, taller);
		if (taller) {
			if (node->balance == RH) {
				node->balance = EH;
				taller = false;
			}
			else if (node->balance == EH)node->balance = LH;
			else {
				leftBalance(node,taller); taller = false; ;
			}
		}
	}
	else {
		node->right = insertRec(node->right, value, taller);
		if (taller) {
			if (node->balance == LH) {
				node->balance = EH;
				taller = false;
			}
			else if (node->balance == EH)node->balance = RH;
			else { rightBalance(node,taller); taller = false;  }
		}
	}

	return node;
}

template <class T>
void AVL<T>::insert(const T &value)
{
	// TODO
bool x = false;
	this->root=insertRec(this->root, value, x);
}

template <class T>
Node<T> *AVL<T>::rightBalance(Node<T> *&node, bool &taller)
{
	// TODO
if (node->right->balance == RH) {
		node->balance = EH;
		node->right->balance = EH;
		node = rotateLeft(node);
	}
	else {
		if (node->right->left->balance == RH) {
			node->balance = LH;
			node->right->balance = EH;
		}
		else if (node->right->left->balance == EH) {
			node->balance = EH;
			node->right->balance = EH;
		}
		else {
			node->balance = EH;
			node->right->balance = RH;
		}
		node->right->left->balance = EH;
		node->right = rotateRight(node->right);
		node = rotateLeft(node);
	}
	return node;
}

template <class T>
Node<T> *AVL<T>::leftBalance(Node<T> *&node, bool &taller)
{
	// TODO
if (node->left->balance == LH) {
		node->balance = EH;
		node->left->balance = EH;
		node = rotateRight(node);
	}
	else {
		if (node->left->right->balance == LH) {
			node->balance = RH;
			node->left->balance = EH;
		}
		else if (node->left->right->balance == EH) {
			node->balance = EH;
			node->left->balance = EH;
		}
		else {
			node->balance = EH;
			node->left->balance = LH;
		}
		node->left->right->balance = EH;
		node->left = rotateLeft(node->left);
		node = rotateRight(node);
	}
	return node;
}

template <class T>
Node<T> *AVL<T>::removeRec(Node<T> *&node, const T &value, bool &shorter, bool &success)
{
	// TODO
 if(node==NULL)
    {
        shorter=false;
        success=false;
        return NULL;
    }
    if(value<node->data)
    {
        node->left=removeRec(node->left,value,shorter,success);
        if(shorter)
        {
            node=removeRightBalance(node,shorter);
        }
    }
    else if(value>node->data)
    {
        node->right=removeRec(node->right,value,shorter,success);
        if(shorter)
        {
            node=removeLeftBalance(node,shorter);
        }
    }
    else
    {
        Node<T> *deleteNode =node;
        if(node->right==NULL)
        {
            Node<T> *newRoot=node->left;
            success=true;
            shorter=true;
            delete deleteNode;
            return newRoot;
        }
        else if(node ->left==NULL)
        {
            Node<T> *newRoot=node->right;
            success=true;
            shorter=true;
            delete deleteNode;
            return newRoot;
        }
        else
        {
            Node<T> *exchPtr=node->left;
            while(exchPtr->right!=NULL)
            {
                exchPtr=exchPtr->right;
            }  
            node->data=exchPtr->data;
            node->left=removeRec(node->left,exchPtr->data,shorter,success);
            if(shorter)
            {
                node=removeRightBalance(node,shorter);
            }
        }
        
    }
    return node;
}

template <class T>
void AVL<T>::remove(const T &value)
{
	// TODO
bool x=false;
    bool y=false;
    this->root=removeRec(root,value,x,y);
}

template <class T>
Node<T> *AVL<T>::removeRightBalance(Node<T> *&node, bool &shorter)
{
	// TODO

	if(node->balance==LH)
    {
        node->balance=EH;
    }
    else if(node->balance==EH)
    {
        node->balance=RH;
        shorter=false;
    }
    else
    {
        Node<T>* rightTree=node->right;
        if(rightTree->balance==LH)
        {
            Node<T>*leftTree=rightTree->left;
            if(leftTree->balance==LH)
            {
                rightTree->balance=RH;
                node->balance=EH;
            }
            else if(rightTree->balance==EH)
            {
                node->balance=LH;
                rightTree->balance=EH;
            }
            else
            {
                node->balance=LH;
                rightTree->balance=EH;
            }
            leftTree->balance=EH;
            node->right=rotateRight(rightTree);
            node=rotateLeft(node);
        }
        else
        {
            if(rightTree->balance!=EH)
            {
                node->balance=EH;
                rightTree->balance=EH;
            }
            else
            {
                node->balance=RH;
                rightTree->balance=LH;
                shorter=false;
            }
            node=rotateLeft(node);
            
        }
        
    }
    return node;
}

template <class T>
Node<T> *AVL<T>::removeLeftBalance(Node<T> *&node, bool &shorter)
{
	// TODO
if(node->balance==RH)
    {
        node->balance=EH;
    }
    else if(node->balance==EH)
    {
        node->balance=LH;
        shorter=false;
    }
    else
    {
        Node<T>* leftTree=node->left;
        if(leftTree->balance==RH)
        {
            Node<T>*rightTree=leftTree->right;
            if(rightTree->balance==RH)
            {
                leftTree->balance=LH;
                node->balance=EH;
            }
            else if(rightTree->balance==EH)
            {
                node->balance=RH;
                leftTree->balance=EH;
            }
            else
            {
                node->balance=LH;
                leftTree->balance=EH;
            }
            rightTree->balance=EH;
            node->right=rotateLeft(leftTree);
            node=rotateRight(node);
        }
        else
        {
            if(leftTree->balance!=EH)
            {
                node->balance=EH;
                leftTree->balance=EH;
            }
            else
            {
                node->balance=LH;
                leftTree->balance=RH;
                shorter=false;
            }
            node=rotateRight(node);
            
        }
        
    }
    return node;
}

template <class T>
int AVL<T>::getHeightRec(Node<T> *node)
{
	if (node == NULL)
		return 0;
	int lh = this->getHeightRec(node->left);
	int rh = this->getHeightRec(node->right);
	return (lh > rh ? lh : rh) + 1;
}

template <class T>
int AVL<T>::getHeight()
{
	return this->getHeightRec(this->root);
}

template <class T>
void AVL<T>::clearRec(Node<T> *&node)
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
void AVL<T>::clear()
{
	this->clearRec(this->root);
}

template <class T>
void AVL<T>::printTreeStructure()
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