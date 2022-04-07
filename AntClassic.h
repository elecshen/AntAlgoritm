#pragma once
#include<iostream>
#include<math.h>
#include<random>
#include<time.h>

class AntClassic
{
	struct Way {
		double length = 0.0;
		double proximity = 0.0; // 1/L^b
		double pheromones = 0.0;
	};

	struct Ant {
		int* orderOfVisitedCities;
		double lengthOfWay = 0;
	};

private:
	int N, currentCity, numOfAvailableWays;
	Way** wayArr;
	bool* checkedCity;
	int* orderOfVisitedCities, * orderOfCitiesWithMinWayLength;
	double a, b, Q, P, minWayLength = -1;
	double* probabilities, * lengthsOfWay;
	Ant* swarmOfAnts;

	void getReady() {
		for (int i = 0; i < N; i++) {
			swarmOfAnts[i].orderOfVisitedCities = new int[N] {-1};
			for (int y = 0; y < N; y++) {
				wayArr[i][y].proximity = pow(1.0 / wayArr[i][y].length, b);
			}
		}
		srand(time(0));
	}

	void howManyWaysIsAvailable() {
		for (int i = 0; i < N; i++)
			if (orderOfVisitedCities[i] == -1) {
				numOfAvailableWays = N - i - 1;
				break;
			}
	}

	void calculateProbability() {
		double sum = 0;
		for (int i = 0; i < N; i++) {
			if (!checkedCity[i])
				probabilities[i] = pow(wayArr[currentCity][i].pheromones, a) * wayArr[currentCity][i].proximity;
			else
				probabilities[i] = 0;

			sum += probabilities[i];
		}
		for (int i = 0; i < N; i++)
			probabilities[i] = probabilities[i] / sum;
	}

	int chooseWay() {
		double choiñe = double(rand()) / RAND_MAX, tempChoice = 0;
		int num = 0, realNum = 0;
		while (num < N) {
			tempChoice += probabilities[num];
			if (probabilities[num++] != 0) realNum = num;
			if (tempChoice > choiñe) break;
		}
		return realNum - 1;
	}

	void goToCity(int cityNumber) {
		checkedCity[cityNumber] = true;
		for (int i = 0; i < N; i++)
			if (orderOfVisitedCities[i] == -1) {
				orderOfVisitedCities[i] = cityNumber;
				break;
			}
		currentCity = cityNumber;
	}

	void saveResultOfWay(int numOfAnt) {
		for (int i = 0; i < N - 1; i++) {
			swarmOfAnts[numOfAnt].lengthOfWay += wayArr[orderOfVisitedCities[i]][orderOfVisitedCities[i + 1]].length;
			swarmOfAnts[numOfAnt].orderOfVisitedCities[i] = orderOfVisitedCities[i];
		}
		swarmOfAnts[numOfAnt].lengthOfWay += wayArr[orderOfVisitedCities[N - 1]][orderOfVisitedCities[0]].length;
		swarmOfAnts[numOfAnt].orderOfVisitedCities[N - 1] = orderOfVisitedCities[N - 1];
	}

	void clearWay() {
		for (int i = 0; i < N; i++) {
			checkedCity[i] = 0;
			orderOfVisitedCities[i] = -1;
		}
	}

	void vaporizePheromones() {
		for (int i = 0; i < N; i++) {
			for (int y = 0; y < N; y++) {
				wayArr[i][y].pheromones *= P;
			}
		}
	}

	void spreadPheromones() {
		double newPheramones;
		for (int i = 0; i < N; i++) {
			for (int y = 0; y < N - 1; y++) {
				newPheramones = Q / swarmOfAnts[i].lengthOfWay;
				wayArr[swarmOfAnts[i].orderOfVisitedCities[y]][swarmOfAnts[i].orderOfVisitedCities[y + 1]].pheromones += newPheramones;
				wayArr[swarmOfAnts[i].orderOfVisitedCities[y + 1]][swarmOfAnts[i].orderOfVisitedCities[y]].pheromones += newPheramones;
			}
			newPheramones = Q / swarmOfAnts[i].lengthOfWay;
			wayArr[swarmOfAnts[i].orderOfVisitedCities[N - 1]][swarmOfAnts[i].orderOfVisitedCities[0]].pheromones += newPheramones;
			wayArr[swarmOfAnts[i].orderOfVisitedCities[0]][swarmOfAnts[i].orderOfVisitedCities[N - 1]].pheromones += newPheramones;
		}
	}

	void saveMinWayAndRestartSwarm() {
		int minIndex = 0;
		double min = swarmOfAnts[minIndex].lengthOfWay;
		for (int i = 1; i < N; i++)
			if (swarmOfAnts[i].lengthOfWay < min) {
				min = swarmOfAnts[i].lengthOfWay;
				minIndex = i;
			}

		minWayLength = min;
		for (int i = 0; i < N; i++)
			orderOfCitiesWithMinWayLength[i] = swarmOfAnts[minIndex].orderOfVisitedCities[i];

		for (int i = 0; i < N; i++) {
			swarmOfAnts[i].lengthOfWay = 0;
			for (int y = 0; y < N; y++)
				swarmOfAnts[i].orderOfVisitedCities[y] = -1;
		}
	}

public:
	AntClassic(int NumOfCity) : N(NumOfCity) {
		wayArr = new Way * [N];
		for (int i = 0; i < N; i++) {
			wayArr[i] = new Way[N];
		}
		checkedCity = new bool[N] {0};
		orderOfVisitedCities = new int[N] {-1};
		orderOfCitiesWithMinWayLength = new int[N] {-1};
		probabilities = new double[N];
		lengthsOfWay = new double[N] {0};
		swarmOfAnts = new Ant[N];
	}

	void initWays(double** lengths, double** pheromones) {
		for (int i = 0; i < N; i++)
			for (int y = 0; y < N; y++) {
				wayArr[i][y].length = lengths[i][y];
				wayArr[i][y].pheromones = pheromones[i][y];
			}
	}

	void initConsts(double const_a, double const_b, double const_Q, double const_P) {
		a = const_a;
		b = const_b;
		Q = const_Q;
		P = const_P;
	}

	void start(int limitOfSwarmIterations) {
		getReady();
		while (limitOfSwarmIterations-- > 0) {
			for (int i = 0; i < N; i++) {
				goToCity(i);
				for (int y = 0; y < N - 1; y++) {
					calculateProbability();
					goToCity(chooseWay());
				}
				saveResultOfWay(i);
				clearWay();
			}
			vaporizePheromones();
			spreadPheromones();
			saveMinWayAndRestartSwarm();
		}
	}

	void printMinWay() {
		std::cout << "Length of shortest way is " << minWayLength << std::endl << "Order of cities:";
		for (int i = 0; i < N; i++) {
			std::cout << " " << orderOfCitiesWithMinWayLength[i + 1];
		}
	}
};

