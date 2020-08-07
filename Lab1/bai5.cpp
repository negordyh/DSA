#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>

using namespace std;


int lengthOfLonggestCommonSubstring(const char* x, const char* y, int m, int n) {
	// TODO
int lengthOfLonggestCommonSubstring[m+1][n+1]; 
    int result = 0; 

    for (int i=0; i<=m; i++) 
    { 
        for (int j=0; j<=n; j++) 
        { 
            if (i == 0 || j == 0) 
                lengthOfLonggestCommonSubstring[i][j] = 0; 
  
            else if (x[i-1] == y[j-1]) 
            { 
                lengthOfLonggestCommonSubstring[i][j] = lengthOfLonggestCommonSubstring[i-1][j-1] + 1; 
                result = max(result, lengthOfLonggestCommonSubstring[i][j]); 
            } 
            else lengthOfLonggestCommonSubstring[i][j] = 0; 
        } 
    } 
    return result; 
}


int main() {
        string x;
        string y;
	    x = "abc123789";
        y = "abc123456";

	cout << lengthOfLonggestCommonSubstring(x.c_str(), y.c_str(), x.length(), y.length());

	return 0;

}