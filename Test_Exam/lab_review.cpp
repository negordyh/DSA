#include <iostream>
#include <string>
using namespace std;
struct node
{
    string name;
    int age;
    int workYear;
    node *next;
    node(string n, int a, int w)
    {
        name = n;
        age = a;
        workYear = w;
        next = NULL;
    }
    ~node()
    {
        cout << "Destructor of Employee" << endl;
    }
};
class EmployeeList
{
    node *root;

public:
    EmployeeList() { root = NULL; };
    EmployeeList(string n, int a, int w)
    {
        root = new node(n, a, w);
    }
    ~EmployeeList()
    {
        while (root != NULL)
        {
            node *tmp = root;
            root = root->next;
            delete tmp;
        }
    }
    bool append(const string &n, int a, int workYear);
    bool del(const string &n);
    void print();
};

bool EmployeeList::append(const string &n, int a, int workYear)
{
    // TODO
    node *pNew = new node(n, a, workYear);
    if (pNew == NULL)
        return false;
    if (this->root == NULL)
        this->root = pNew;
    else if (this->root->next == NULL)
    {
        this->root->next = pNew;
    }
    else
    {
        node *_pre = this->root;
        while (_pre->next != NULL)
        {
            _pre = _pre->next;
        }
        _pre->next = pNew;
    }
    return true;
}

bool EmployeeList::del(const string &n)
{
    node *_pre = this->root;
    if (this->root == NULL)
        return false;
    if (_pre->name == n)
    {
        delete root;
        return true;
    }
    node *loch = this->root->next;
    while (_pre->next != NULL)
    {
        if (_pre->next->name == n)
            break;
        _pre = _pre->next;
        loch = loch->next;
    }
    if (_pre->next != NULL)
    {
        _pre->next = loch->next;
        delete loch;
        return true;
    }
    return false;
}

void EmployeeList::print()
{
    node *_pre = this->root;
    while (_pre != NULL)
    {
        cout << "Name: " << _pre->name << ", Age: " << _pre->age << ", Year Of Work: " << _pre->workYear << " " << endl;
        _pre = _pre->next;
    }
}

int main()
{
    EmployeeList list;
    list.append("Johnny Depp ", 45, 23);
    list.append("Alexander Rybak", 32, 4);
    list.append("Adele", 31, 4);
    if (!list.del("John Henry"))
        cout << "Employee John Henry not found" << endl;
    list.print();
}