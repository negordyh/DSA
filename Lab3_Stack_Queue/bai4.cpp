#include <iostream>
#include <fstream>
#include <math.h>
#include <stack>
#include <string>
#pragma endregion


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

int evaluatePostfixExpression(string exp)
{
	// TODO
	stack<int> Stack; 
	int i; 

	for (i = 0; exp[i]; ++i) 
	{ 
		if(exp[i] == ' ')continue; 

		else if (isdigit(exp[i])) 
		{ 
			int num=0; 
			
			//extract full number 
			while(isdigit(exp[i])) 
			{ 
			num = num * 10 + (int)(exp[i] - '0'); 
				i++; 
			} 
			i--; 
			
			//push the element in the stack 
			Stack.push(num);
		} 

		else
		{ 
			int val1 = Stack.pop(val1);
			int val2 = Stack.pop(val2) 
			
			int result = evaluate(exp[j], val2, val1);
			Stack.push(result);
		} 
	} 
	return Stack.pop(); 

}


int main()
{
	char exp[] = "7837-7%%1-/5+6%9%8-"; 
	cout<<"postfix evaluation: "<< evaluatePostfixExpression(exp); 
	return 0; 
}
