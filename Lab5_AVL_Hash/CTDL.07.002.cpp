#include <iostream>
#include <fstream>
#include <math.h>
#define MAX_SIZE 1000
using namespace std;

template <class T>
class MaxHeap
{
private:
	T arr[MAX_SIZE];
	int count;

protected:
	void reHeapUp(int pos);
	void reHeapDown(int pos);

public:
	MaxHeap();
	bool insert(T &valIn);
	bool remove(T &valOut);
	void print();
	T *toArray();
	int getSize();

	void buildHeap(T *a, int size);
	void printValuesLargerThan(T k);
};

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string line;
	getline(ifs, line);
	int size = stoi(line);

	int* arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		getline(ifs, line);
		int element = stoi(line);
		arr[i] = element;
	}

	MaxHeap<int>* heap = new MaxHeap<int>();
	heap->buildHeap(arr, size);
	heap->print();
	delete heap;

	ifs.close();

	return 0;
}

template <class T>
void MaxHeap<T>::reHeapUp(int position) {
	// TODO
	if (position > 0 && position < count) {
		int parent = (position - 1) / 2;
		if (arr[parent] < arr[position]) {
			T tmp = arr[parent];
			arr[parent] = arr[position];
			arr[position] = tmp;
			reHeapUp(parent);
		}
	}
	return;
}

template <class T>
void MaxHeap<T>::reHeapDown(int position) {
	// TODO
if (position >= 0 && position < count) {
		int Lc = 2 * position + 1;
		int Rc = 2 * position + 2;
		int bigc = NULL;
		if (Lc < count) {
			if (Rc < count) {
				if (arr[Lc] >= arr[Rc]) bigc = Lc;
				else bigc = Rc;
			}
			else bigc = Lc;
		}
		if (bigc != NULL) {
			if (arr[bigc] > arr[position]) {
				T tmp = arr[bigc];
				arr[bigc] = arr[position];
				arr[position] = tmp;
				reHeapDown(bigc);
			}
		}
	}
	return;
}

template <class T>
T* MaxHeap<T>::toArray() {
	return arr;
}

template <class T>
int MaxHeap<T>::getSize() {
	return count;
}

template <class T>
bool MaxHeap<T>::insert(T& valIn) {
	// TODO
if (count < MAX_SIZE) {
		arr[count] = valIn;
		count++;
		reHeapUp(count - 1);
		return true;
	}
	return false;
}

template <class T>
MaxHeap<T>::MaxHeap() {
	count = 0;
}

template <class T>
bool MaxHeap<T>::remove(T& valOut) {
	// TODO
if (count > 0) {
		valOut = arr[0];
		arr[0] = arr[count - 1];
		count--;
		reHeapDown(0);
		return true;
	}
	return false;
}

template <class T>
void MaxHeap<T>::buildHeap(T *a, int size)
{
	// TODO
if (count == 0) {
		for (int i = 0; i < size; i++) insert(a[i]);
	}
	return;
}

template <class T>
void MaxHeap<T>::print()
{
	for (int i = 0; i < count; i++)
		cout << arr[i] << " ";
	cout << endl;
}