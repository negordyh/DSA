#include <iostream>
#include <fstream>
#include <math.h>
#include <stack>
using namespace std;

int evaluate(char x, int op1, int op2)
{
	// TODO
    if (x == '*') return op1 * op2;
	if (x == '+') return op1 + op2;
	if (x == '-') return op1 - op2;
	if (x == '/') return op1 / op2;
	if (x == '%') return op1 % op2;
    return 0;
}

int evaluatePrefixExpression(const char *exp)
{
	// TODO
stack<char> Stack; 
  
    for (int j = sizeof(exp)/sizeof(exp[0]) - 1; j >= 0; j--) { 
        if (exp[j] != '*' || exp[j] != '+' || exp[j] != '-' || exp[j] != '/') 
            Stack.push(exp[j] - '0'); 
  
        else { 
  
            double o1 = Stack.top(); 
            Stack.pop(); 
            double o2 = Stack.top(); 
            Stack.pop(); 
  
            int result = evaluate(exp[j], o1, o2);
			Stack.push(result);
        } 
    } 
  
    return Stack.top(); 
}

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string arr;
	getline(ifs, arr);

	try
	{
		cout << evaluatePrefixExpression(arr.c_str());
	}
	catch (const char *msg)
	{
		cout << msg;
	}

	ifs.close();

	return 0;
}
