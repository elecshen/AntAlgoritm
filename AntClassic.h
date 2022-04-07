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

	void getReady();

	void howManyWaysIsAvailable();

	void calculateProbability();

	int chooseWay();

	void goToCity(int cityNumber);

	void saveResultOfWay(int numOfAnt);

	void clearWay();

	void vaporizePheromones();

	void spreadPheromones();

	void saveMinWayAndRestartSwarm();

public:
	AntClassic(int NumOfCity);

	void initWays(double** lengths, double** pheromones);

	void initConsts(double const_a, double const_b, double const_Q, double const_P);

	void start(int limitOfSwarmIterations);

	void printMinWay();
};

