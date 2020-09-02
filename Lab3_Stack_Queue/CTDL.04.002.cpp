#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

template <class T>
class Node
{
public:
	T data;
	Node *link;

	Node(const T &val)
	{
		data = val;
		link = NULL;
	}
};

template <class T>
class Queue
{
private:
	Node<T> *frontPtr;
	Node<T> *rearPtr;
	int count;

public:
	Queue()
	{
		frontPtr = frontPtr = NULL;
		count = 0;
	}
	~Queue()
	{
		clear();
	}
	void print2Console();

	// TODO Methods

	/*
		Clear all elements of queue
		- Input: none
		- Output: none
	*/
	void clear();

	/*
		Determine if the queue is empty
		- Input: none
		- Output: return true if empty otherwise return false
	*/
	bool isEmpty();

	/*
		Get the size of the queue
		- Input: none
		- Output: return the queue size
	*/
	int size();

	/*
		Get the reference to the front data
		- Input: none
		- Output: return the reference to the front data
		- Exception: throw "Empty queue!" if the queue is empty
	*/
	T &front();

	/*
		Get the reference to the rear data
		- Input: none
		- Output: return the reference to the rear data
		- Exception: throw "Empty queue!" if the queue is empty
	*/
	T &rear();

	/*
		Push new element into the queue
		- Input: the value to be pushed
		- Output: none
	*/
	void enQueue(const T &val);

	/*
		Remove an element from the queue
		- Input: the value to be removed
		- Output: return 1 if successful otherwise return 0 (the queue is empty)
	*/
	int deQueue(T &valOUt);
};

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	Queue<int> *queue = new Queue<int>();

	int code, data;
	while (ifs.good())
	{
		ifs >> code;
		switch (code)
		{
		case 0:
			ifs >> data;
			queue->enQueue(data);
			break;
		case 1:
			if (queue->deQueue(data))
				cout << data << endl;
			break;
		case 2:
			try
			{
				data = queue->front();
				cout << data << endl;
			}
			catch (const char *msg)
			{
				cout << msg << endl;
			}
			break;
		case 3:
			try
			{
				data = queue->rear();
				cout << data << endl;
			}
			catch (const char *msg)
			{
				cout << msg << endl;
			}
			break;
		case 4:
			queue->clear();
			break;
		case 5:
			cout << queue->isEmpty() << endl;
			break;
		}
		cout << "Queue size " << queue->size() << ": ";
		queue->print2Console();
		cout << endl;
	}
	delete queue;

	ifs.close();

	return 0;
}

template <class T>
void Queue<T>::clear()
{
	// TODO
if (isEmpty()) return;
	while (frontPtr != NULL)
	{
		frontPtr = frontPtr->link;
	}
	rearPtr = NULL;
	count = 0;
}

template <class T>
bool Queue<T>::isEmpty()
{
	// TODO
if (count == 0)return 1;
	else return 0;
}

template <class T>
int Queue<T>::size()
{
	// TODO
return count;
}

template <class T>
T &Queue<T>::front()
{
	// TODO
if (isEmpty()) throw "Empty queue!";
	else return frontPtr->data;
}

template <class T>
T &Queue<T>::rear()
{
	// TODO
if (isEmpty()) throw "Empty queue!";
	else return rearPtr->data;
}

template <class T>
void Queue<T>::enQueue(const T &val)
{
	// TODO
Node<T>* pNew = new Node<T>(val);
	if (isEmpty()) {
		frontPtr = pNew;
		rearPtr = pNew;
	}
	else {
		rearPtr->link = pNew;
		rearPtr = pNew;
	}
	count++;    
}

template <class T>
int Queue<T>::deQueue(T &valOut)
{
	// TODO
if (isEmpty())return 0;
    valOut = frontPtr->data;
	frontPtr = frontPtr->link;
	count--;
	return 1;
}

template <class T>
void Queue<T>::print2Console()
{
	Node<T> *p = frontPtr;
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->link;
	}
}