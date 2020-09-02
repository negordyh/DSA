#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <queue>
#define MAX_SIZE 1000
using namespace std;

int minCost(int arr[], int n) 
{ 
	// TODO
int tmp;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (arr[j] < arr[i]) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
	queue<int> q;
	queue<int> qt;
	int result = 0;

	for (int i = 0; i < n;i++) {
		q.push(arr[i]);
	}

	while (!q.empty()) {
		//connect
		tmp = q.front();
		q.pop();
		if (q.empty()) return result;
		tmp += q.front();
		result += tmp;
		q.pop();
		//reheap
		int check = 0;
		while (!q.empty()) {
			if (q.front() >= tmp) { qt.push(tmp); check++; break; }
			qt.push(q.front());
			q.pop();
		} 
		if (check == 0) qt.push(tmp);
		while (!q.empty()) {
			qt.push(q.front());
			q.pop();
		}
		while (!qt.empty()) {
			q.push(qt.front());
			qt.pop();
		}
	}
	return result;
} 

int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1], ifstream::in);

	string line;
	getline(ifs, line);
	int size = stoi(line);

	int *arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		getline(ifs, line);
		int element = stoi(line);
		arr[i] = element;
	}

	cout << "Total cost for connecting ropes is " << minCost(arr, size); 

	ifs.close();

	return 0;
}