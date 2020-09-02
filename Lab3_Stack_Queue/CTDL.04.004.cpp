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
	if (x == '/') {
		if (op2 == 0)
			throw "Divide by zero";
		else
			return op1 / op2;
	}
	if (x == '%') {
		if (op2 == 0) throw "Divide by zero";
		else return op1 % op2;
	}
	return NULL;
}

int evaluatePostfixExpression(string exp)
{
	// TODO
stack<int> Stack;
	int i;

	for (i = 0; exp[i]!=NULL; i++)
	{
		if (isdigit(exp[i]))
		{
			int num = (int)(exp[i] - '0');
			//push the element in the stack 
			Stack.push(num);
		}

		else
		{
			int val1=Stack.top();
			Stack.pop();
			int val2 = Stack.top();
			Stack.pop();
			int result = evaluate(exp[i], val2, val1);
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
		cout << evaluatePostfixExpression(arr);
	}
	catch (const char *msg)
	{
		cout << msg;
	}

	ifs.close();

	return 0;
}
