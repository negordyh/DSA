#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

void printByPattern(int n) {
    // TODO
int dem = 0;
	for (int i = 1; i < n+1; i++) {
		for (int j = 1; j <= i; j++) {
			dem++;
			cout << dem;
			if (j < i) cout << " ";
		}
		cout << endl;
	}
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
		
    printByPattern(n);

	return 0;
}