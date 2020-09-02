#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

template <class T>
struct L1Item
{
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List
{
    L1Item<T> *_pHead; // The head pointer of linked list
    size_t _size;      // number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List()
    {
        this->clean();
    }

    
    bool isEmpty()
    {
        return _pHead == NULL;
    }
    size_t getSize()
    {
        return _size;
    }

    /*
        Give the reference to the element i-th in the list (i starting with 0).
        Input: 
            - i: the index of element.
        Output: the reference to the element.
    */
    T &at(int i);  

    /*
        Give the reference to the element i-th in the list (i starting with 0).
        Input: 
            - i: the index of element.
        Output: the reference to the element.
    */       
    T &operator[](int i);

    /*
        Find an element similar to a in the list. 
        Set the found index to idx, set idx to -1 if failed.
        Input: 
            - a: the value to compare with
            - idx: place to store result index
        Output: return true if found, otherwise return false.
    */
    bool find(T &a, int &idx); 
    
    /*
        Insert an element into the list at location i.
        Input: 
            - i: the index to insert
            - a: value to insert
        Output: return 0 if success, -1 if otherwise or range check index failed.
    */
    int insert(int i, T &a);

    /*
        Remove an element at location i in the list
        Input: 
            - i: the index to remove
        Output: return 0 if success, -1 if otherwise or range check index failed.
    */
    int remove(int i);

    /*
        Append (insert tail) to the list
        Input: 
            - a: the value to insert
        Output: return 0 if success, -1 if otherwise.
    */
    int append(T &a);

    /*
        Prepend (insert head) to the list
        Input: 
            - a: the value to insert
        Output: return 0 if success, -1 if otherwise.
    */
    int prepend(T &a); 

    /*
        Remove the first element if the list
        Input: none
        Output: return 0 if success, -1 if otherwise (empty list).
    */
    int removeHead();

    /*
        Remove the last element if the list
        Input: none
        Output: return 0 if success, -1 if otherwise (empty list).
    */
    int removeTail(); 

    /*
        Reverse the list.
        Input: none
        Output: none.
    */
    void reverse();

    /*
        Traverse the list
        Input:
            - op: pointer to function processing each element
        Output: none.
    */
    void traverse(void (*op)(T &));

    /*
        Clean the list: delete all elements in list
        Input: none.
        Output: none.
    */
    void clean();
};

void printInt(int &data)
{
    cout << data << " ";
}

int main(int argc, char *argv[])
{
    ifstream ifs;
    ifs.open(argv[1], ifstream::in);

    L1List<int> *list = new L1List<int>();
    int code, data, index;
    while (ifs.good()) {
        ifs >> code;
        switch (code) {
            case 0: ifs >> data; cout << list->prepend(data); break;
            case 1: ifs >> data; cout << list->append(data); break;
            case 2: cout << list->removeHead(); break;
            case 3: cout << list->removeTail(); break;
            // case 4: ifs >> index >> data; cout << list->insert(index, data); break;
            // case 5: ifs >> index; cout << list->remove(index); break;
            // case 6: ifs >> data; cout << (list->find(data, index) ? index : -1); break;
            // case 7: list->reverse(); break;
        }
        if (code != 7) cout << endl;
    }
    list->traverse(printInt);
    delete list;

    ifs.close();

    return 0;
}

template <class T>
T &L1List<T>::at(int i)
{
    // TODO
if (i > this->_size || i < 0) return NULL;
    L1Item<T>* _pre;
    _pre = this->_pHead;
    for (int j = 0; j <= i; j++) {
        _pre = _pre->pNext;
    }
    return _pre->data;
}

template <class T>
T &L1List<T>::operator[](int i)
{
    // TODO
if (i > this->_size || i < 0) return NULL;
    L1Item<T>* _pre;
    _pre = this->_pHead;
    for (int j = 0; j <= i; j++) {
        _pre = _pre->pNext;
    }
    return _pre->data;

}

template <class T>
int L1List<T>::append(T &a)
{
    // TODO
L1Item<T>* pNew = new L1Item<T>(a);
   if (pNew == NULL) return -1;
    if (_size == 0) this->_pHead = pNew;
    else if (_size == 1)
    {
        this->_pHead->pNext = pNew;
    }
    else
    {
        L1Item<T>* _pre = this->_pHead;
        while (_pre->pNext != NULL)
        {
            _pre = _pre->pNext;
        }
        _pre->pNext = pNew;
    }
    this->_size++;
    return 0;
}

template <class T>
int L1List<T>::prepend(T &a)
{
    // TODO
L1Item<T>* pNew = new  L1Item<T>(a);
    if (pNew == NULL) return -1;
    if (_size == 0) this->_pHead = pNew;
    else { pNew->pNext = this->_pHead; this->_pHead = pNew; }
    this->_size++;
    return 0;
}

template <class T>
int L1List<T>::removeHead()
{
    // TODO
if (_size == 0) return -1;
    else {
        this->_pHead =this->_pHead->pNext; 
    }
    this->_size--;
    return 0;
}

template <class T>
int L1List<T>::removeTail()
{
    // TODO
L1Item<T>* _pre = this->_pHead;
    if (_size == 0) return -1;
    else if (_size == 1) {
        this->_pHead = NULL;
    }
    else {
        while (_pre->pNext->pNext != NULL) {
            _pre = _pre->pNext;
        }
    }
    _pre->pNext = NULL ;
    this->_size--;
    return 0;
}

template <class T>
void L1List<T>::clean()
{
}

template <class T>
void L1List<T>::traverse(void (*op)(T &))
{
    L1Item<T> *pTemp = this->_pHead;
    while (pTemp != NULL)
    {
        op(pTemp->data);
        pTemp = pTemp->pNext;
    }
}