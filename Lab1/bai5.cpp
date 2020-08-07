#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>

using namespace std;


int lcs(const char* x, const char* y, int m, int n) {
	// TODO
    int count = 0;
    if (m == 0 || n == 0)  
        return count;  
    if (x[m-1] == y[n-1])  
        count = 1 + lcs(x, y, m-1, n-1);  
    else
        count = max(lcs(x, y, m, n-1), lcs(x, y, m-1, n));  
    return count;
}

int max(int a, int b)  
{  
    return (a > b)? a : b;  
}  

int main() {
        string x;
        string y;
	    x = "mvdxyz";
        y = "xyzabcd";

	cout << lcs(x.c_str(), y.c_str(), x.length(), y.length());

	return 0;

}