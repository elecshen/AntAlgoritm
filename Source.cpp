#include<iostream>
#include"AntClassic.h"

using namespace std;

int main() {
	int N;
	cin >> N;
	AntClassic ac(N);
	double** lengths = new double* [N];
	double** pherom = new double* [N];
	for (int i = 0; i < N; i++) {
		lengths[i] = new double [N];
		pherom[i] = new double [N] {0.5}; // начальное количество
	}
	for (int i = 0; i < N; i++) {
		for (int y = 0; y < N; y++) {
			cin >> lengths[i][y];
		}
	}
	ac.initWays(lengths, pherom);
	//            a  b  Q  P
	ac.initConsts(1, 1, 4, 0.8);
	ac.start(50000);
	ac.printMinWay();
}