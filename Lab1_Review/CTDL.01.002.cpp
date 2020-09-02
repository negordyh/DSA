#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

bool isDuckNumber(int n) {
	// TODO
while (n % 10 != 0 && n > 10)
		n /= 10;
	if ((n >= 10 && n % 10 == 0) || n == 0)
		return true;
	else
		return false;
}

int main(int narg, char **argv)
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);
	
	int n;
	string line;

	for (int count = 0; ifs.good() && count < 1; count++) {
		getline(ifs, line);
		n = stoi(line);
	}
	ifs.close();
	
    cout << isDuckNumber(n);
	return 0;
}