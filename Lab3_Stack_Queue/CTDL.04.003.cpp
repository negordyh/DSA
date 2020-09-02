#include <iostream>
#include <fstream>
#include <math.h>
#include <stack>
using namespace std;

bool checkParentheses(const char *arr)
{
	// TODO
stack<char> s;
    char x;

    int i = 0;
    while (arr[i] != NULL) {
        if (arr[i] == '(' || arr[i] == '[' || arr[i] == '{') {

            s.push(arr[i]);
            i++;
                continue;
        }
        if (s.empty()) return false;

        switch (arr[i]) {
        case ')':
            x = s.top();
            if (x !='(')
                return false;
            s.pop();
            i++;
            break;

        case '}':
            x = s.top();
            if (x !='{')
                return false;
            s.pop();
            i++;
            break;

        case ']':
            x = s.top();
            if (x !='[')
                return false;
            s.pop();
            i++;
            break;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string arr;
	getline(ifs, arr);

	cout << checkParentheses(arr.c_str());

	ifs.close();

	return 0;
}
