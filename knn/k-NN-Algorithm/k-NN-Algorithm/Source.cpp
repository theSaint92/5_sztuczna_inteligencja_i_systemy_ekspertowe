#include <iostream>

#include "Distance.h"
#include "EuclideanDistance.h"
#include "EuclideanSquaredDistance.h"
#include "ManhattanDistance.h"
#include "ChebyshevDistance.h"
#include "MinkowskiDistance.h"


using namespace std;

int main(int argc, char** argv) {
	cout << "Starting work here";
	MinkowskiDistance d;
	d.p = 0.5;
	cout << d.p;

	double v1[2]{ 0,0 };
	double v2[2]{ 1,1 };

	double result = d.dist(2, v1, v2);

	cout << result;
	
	int klops;
	cin >> klops;
	return 0;
}