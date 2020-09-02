#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;


template <class T>
class Node {
public:
	T data;
	Node *link;
	Node() {
		this->link = NULL;
	}

	Node(T data) {
		this->data = data;
		this->link = NULL;
	}
};

template <class T>
class Stack {
private:
	Node<T> * head;
	int count;
public:
	Stack() {
		head = NULL;
		count = 0;
	}

	~Stack() {
		clear();
	}
    void print2Console();

    // TODO Methods

	/*
		Push an element into the stack
		- Input: the value to push
		- Output: none
	*/
	void push(const T& val);

	/*
		Pop an element from the stack
		- Input: the value to store the top element
		- Output: return 1 if success, otherwise return 0 (the stack is empty)
	*/
	int pop(T& val);

	/*
		Get the top element of the stack
		- Input: none
		- Output: return the reference to top element
		- Exception: throw message "Empty stack!" if stack is empty
	*/
    T& top();

	/*
		Clear all elements of the stack
		- Input: none
		- Output: none
	*/
	void clear();

	/*
		Determine if the stack is empty
		- Input: none
		- Output: return true if empty, otherwise return false.
	*/
	bool isEmpty();
};


int main(int argc, char *argv[])
{
    ifstream ifs;
    ifs.open(argv[1], ifstream::in);

    Stack<int>* stack = new Stack<int>();
    
    int code, data;
    while (ifs.good()) {
        ifs >> code;
        switch (code) {
            case 0: ifs >> data; stack->push(data); break;
            case 1: if (stack->pop(data)) cout << data << endl; break;
            case 2: 
                try { data = stack->top(); cout << data << endl; } catch (const char* msg) { cout << msg << endl;} 
                break;
            case 3: stack->clear(); break;
            case 4: cout << stack->isEmpty() << endl; break;
        }

        stack->print2Console(); cout << endl;
    }
    delete stack;

    ifs.close();

    return 0;
}

template <class T>
void Stack<T>::clear() {
	// TODO
if (isEmpty()) return;
	while (this->head!=NULL)
	{
		this->head = this->head->link;
	}
	this->count = 0;
}

template <class T>
bool Stack<T>::isEmpty() {
	// TODO
if (this->count == 0) return 1;
	else return 0;
}

template <class T>
void Stack<T>::push(const T& val) {
	// TODO
Node<T>* pNew = new Node<T>(val);
	if (isEmpty()) { this->head = pNew; this->count++; return; }
	pNew->link = this->head;
	this->head = pNew;
	this->count++;
}

template <class T>
int Stack<T>::pop(T& val) {
	// TODO
if (isEmpty()) return 0;
	val = this->head->data;
	this->head = this->head->link;
	this->count--;
	return 1;
}

template <class T>
T& Stack<T>::top() {
    // TODO
if (isEmpty())throw"Empty stack!";
	else return this->head->data;
}

template <class T>
void Stack<T>::print2Console() {
	Node<T>*p = head;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->link;
	}
}