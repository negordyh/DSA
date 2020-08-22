#include <iostream>
#include <fstream>
#include <math.h>
#include <stack>
#include <string>
#pragma endregion

using namespace std;

bool checkParentheses(const char *arr)
{
	//TODO
    stack<char> s; 
    char x; 
  
    
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) { 
        if (arr[i] == '(' || arr[i] == '[' || arr[i] == '{') { 
            
            s.push(arr[i]); 
            continue; 
        } 

        if (s.empty()) 
            return false; 
  
        switch (arr[i]) { 
        case ')': 
            x = s.top(); 
            s.pop(); 
            if (x == '{' || x == '[') 
                return false; 
            break; 
  
        case '}': 
  
            s.pop(); 
            if (x == '(' || x == '[') 
                return false; 
            break; 
  
        case ']': 

            x = s.top(); 
            s.pop(); 
            if (x == '(' || x == '{') 
                return false; 
            break; 
        } 
    } 

    return (s.empty()); 
}

int main()
{
	ifstream ifs;
	ifs.open("file3.txt");

	string arr;
	getline(ifs, arr);

	cout << checkParentheses(arr.c_str());

	ifs.close();

	return 0;
}
