#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <string>
using namespace std;

void printInteger(int element) {
    cout << element << " ";
}

int compareInteger(int a, int b) {
    if(a==b) return 0;
else if(a>b) return 1;
else return -1;
    //TODO
}

template<class T>
class AList {
private:
    T* storage;
    int size;
    int capacity;

protected:
    void setCapacity(int capacity);
    void ensureCapacity(int minCapacity);
    void pack();
    void trim();
    void rangeCheck(int index);

    // HELPER Methods: You can implement additionally if necessary
    //TODO
public:
    AList() {
        this->storage = NULL;
        this->size = 0;
        this->capacity = 0;
    }

    AList(T* storage, int size) {
        this->size = this->capacity = size;
        this->storage = new T[size];

        for (int i = 0; i < size; i++) {
            this->storage[i] = storage[i];
        }
    }

    ~AList() {
        if (storage != NULL)
		    delete[] storage;
    }

    void clear();
	void set(int index, T value);
	T& get(int index);
    int getSize();
	void removeAt(int index);
	void insertAt(int index, T value);
    void print(void (*printElement)(T element));

    // TODO Methods
    int getIndexOfSorted(T value, int (*compare)(T a, T b));
};

int main() {
    ifstream ifs;
	ifs.open("file4.txt");
	
	string line;

    getline(ifs, line);
    int size = stoi(line);

    AList<int>* intList = new AList<int>();

    for (int i = 0; i < size && ifs.good(); i++) {
        getline(ifs, line);
        intList->insertAt(intList->getSize(), stoi(line));
    }

    getline(ifs, line);
    int value = stoi(line);

    cout << intList->getIndexOfSorted(value, compareInteger) << endl;
    
    ifs.close();

    return 0;
}

// HELPER methods implementation
//TODO 

// TODO Methods implementation
template <class T>
int AList<T>::getIndexOfSorted(T value, int (*compare)(T a, T b)) {
    
    //TODO
    int l=0;
    int r=this->size;
    while (l <= r) { 
        int m = l + (r - l) / 2; 
  
        // Check if x is present at mid 
        if (storage[m] == value) 
            return m; 
  
        // If x greater, ignore left half 
        if (storage[m] < value) 
            l = m + 1; 
  
        // If x is smaller, ignore right half 
        else
            r = m - 1; 
    } 
    return -1; 
}

template<class T>
void AList<T>::setCapacity(int capacity) {
    T *newStorage = new T[capacity];
    memcpy(newStorage, storage, sizeof(T) * size);
    this->capacity = capacity;
    delete[] storage;
    storage = newStorage;
}

template<class T>
void AList<T>::ensureCapacity(int minCapacity) {
    if (minCapacity > capacity) {
        int newCapacity = (capacity * 3) / 2 + 1;
        if (newCapacity < minCapacity)
            newCapacity = minCapacity;
        setCapacity(newCapacity);
    }
}

template<class T>
void AList<T>::pack() {
    if (size <= capacity / 2) {
        int newCapacity = (size * 3) / 2 + 1;
        setCapacity(newCapacity);
    }
}

template<class T>
void AList<T>::trim() {
    int newCapacity = size;
    setCapacity(newCapacity);
}

template<class T>
void AList<T>::rangeCheck(int index) {
    if (index < 0 || index >= size)
        throw "Index out of bounds!";
}

template<class T>
void AList<T>::clear() {
	if (storage != NULL)
		delete[] storage;
	size = 0;
	capacity = 10;
	storage = new T[capacity];
}

template<class T>
void AList<T>::set(int index, T value) {
	rangeCheck(index);
	storage[index] = value;
}

template<class T>
T& AList<T>::get(int index) {
	rangeCheck(index);
	return storage[index];
}

template<class T>
int AList<T>::getSize() {
	return this->size;
}

template<class T>
void AList<T>::insertAt(int index, T value) {
	if (index < 0 || index > size ) {
		throw "Index out of bounds!";
	}
	ensureCapacity(size+1);
	memmove(storage + index + 1, storage + index, sizeof(T) * (size-index));
	storage[index] = value;
	size++;
}

template<class T>
void AList<T>::removeAt(int index) {
	rangeCheck(index);
	memmove(storage + index, storage + index + 1, sizeof(T) * (size - index - 1));
	size--;
	pack();
}

template<class T>
void AList<T>::print(void (*printElement)(T element)) {
    for (int i = 0; i < size; i++) {
        printElement(storage[i]);
    }
}