#include<iostream>
#include"AntClassic.h"

using namespace std;

int main() {
	int N = 6;
	AntClassic ac(N);
	double** lengths = new double* [N];
	double** pherom = new double* [N];
	for (int i = 0; i < N; i++) {
		lengths[i] = new double [N];
		pherom[i] = new double [N] {0.5};
	}
/*	lengths[0] = {0, 10, 17, 10};
	lengths[1] = { 10, 0, 10, 10 };
	lengths[2] = { 17, 10, 0, 10 };
	lengths[3] = { 10, 10, 10, 0 };*/
	for (int i = 0; i < N; i++) {
		for (int y = 0; y < N; y++) {
			cin >> lengths[i][y];
		}
	}
	ac.initWays(lengths, pherom);
	ac.initConsts(1, 1, 4, 0.8);
	ac.start(50);
	ac.printMinWay();
}