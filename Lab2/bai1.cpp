#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <string>
using namespace std;

void printInteger(int element) {
    cout << element << " ";
}

template<class T>
class AList {
private:
    T* data;
    int size;
    int capacity;

public:
    AList() {
        cout << "Default constructor called!" << endl;
        //TODO
        size = 0;
        capacity = 0;
        data = NULL;
        }

    AList(T* data, int size) {
        cout << "User-define constructor called!" << endl;
        //TODO
        data = new T[size];
        
    }

    void print(void (*printElement)(T element)) {
        for (int i = 0; i < size; i++) {
            printElement(data[i]);
        }
    }

    ~AList() {
        cout << "Destructor AList called!" << endl;
        //TODO
        delete [] data;
    }
};

int main(int argc, char* argv[]) {
    ifstream ifs;
	ifs.open(argv[1], ifstream::in);
	
	string line;

    getline(ifs, line);
    int code = stoi(line);


    if (code == 1) {
        AList<int>* intList = new AList<int>();
        intList->print(printInteger);
        delete intList;
    }
    else if (code == 2) {
        getline(ifs, line);
        int size = std::stoi(line);

        int* data = new int[size];
        for (int count = 0; ifs.good() && count < size; count++) {
            getline(ifs, line);
            data[count] = stoi(line);
        }

        AList<int>* intList = new AList<int>(data, size);
        intList->print(printInteger);
        delete intList;
    }

    ifs.close();

    return 0;
}

