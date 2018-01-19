#include <iostream>
#include <set>
#include <vector>
#include <fstream>

#include "Instance.h"
#include "Distance.h"
#include "EuclideanDistance.h"
#include "EuclideanSquaredDistance.h"
#include "ManhattanDistance.h"
#include "ChebyshevDistance.h"
#include "MinkowskiDistance.h"
#include "functions.h"
#include "kFold.h"


using namespace std;

int main(int argc, char** argv) {
	cout << "Starting work here";
	MinkowskiDistance d;
	d.p = 0.5;
	cout << d.p;

	double v1[2]{ 0,0 };
	double v2[2]{ 1,1 };

	double result = d.dist(2, v1, v2);

	cout << result << endl;
	
	std::multiset<double> st;
	st.insert(12);
	st.insert(12);
	st.insert(12);
	st.insert(145);
	st.insert(145);
	st.insert(1);
	st.insert(2);

	for (double i : st) {
		cout << i << endl;
	}

	std::vector<Instance> vec;
	readFromFile(vec, "../../datasets/iris.data", 5);
	//readFromFile(vec, "../../datasets/wine.data", 1);
	std::cout << vectorOfInstancesToString(vec);

	kFold fold;

	fold.createFolds(vec, 15);
	//for (int i = 0; i < 5; i++) {
	//	std::cout << "====================" << std::endl;
	//	std::cout << "FOLD NO" << i << std::endl;
	//	std::cout << "====================" << std::endl;
	//	std::cout << vectorOfInstancesToString(fold.getKFold(i));
	//}
	//std::cout << "====================" << std::endl;
	//std::cout << vectorOfInstancesToString(fold.getKFold(1));
	//std::cout << "====================" << std::endl;
	//std::cout << vectorOfInstancesToString(fold.getAllButKFold(1));

	std::cout << "====================" << std::endl;
	std::cout << "====================" << std::endl;
	std::cout << "====================" << std::endl;
	std::cout << vectorOfInstancesToString(fold.getKFold(1));
	std::cout << "====================" << std::endl;
	std::cout << "====================" << std::endl;
	std::cout << "====================" << std::endl;

	standarization(fold.getKFold(1));

	int klops;
	cin >> klops;
	return 0;


}