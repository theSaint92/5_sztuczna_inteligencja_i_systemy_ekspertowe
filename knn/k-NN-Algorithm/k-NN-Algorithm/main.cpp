#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

#include "Instance.h"
#include "Distance.h"
#include "EuclideanDistance.h"
#include "EuclideanSquaredDistance.h"
#include "ManhattanDistance.h"
#include "ChebyshevDistance.h"
#include "MinkowskiDistance.h"
#include "functions.h"
#include "kFold.h"
#include "kNNClassifier.h"
#include "ErrorMatrix.h"

enum DISTANCE {
	EUCLIDEAN = 1,
	EUCLIDEANSQUARED,
	MANHATTAN,
	CHEBYSHEV,
	MINKOWSKI,
};

int main(int argc, char** argv) {

	/*
	* Picking how program works (some rework might happen here)
	*/
	char* data = "";
	int placeOfClassAttribute = 1;
	bool normalize = false;
	bool standarize = false;
	int numOfFolds = 3;
	int numOfNeighbours = 10;
	int distanceFunc = DISTANCE::EUCLIDEAN;
	double minkowskiOrder = 3;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--data") == 0 || strcmp(argv[i], "-d") == 0) {
			if (i < argc - 1) {
				data = argv[i + 1];
				i++;
				if (i < argc - 1) {
					std::string h2 = argv[i + 1];
					placeOfClassAttribute = std::stoi(h2);
					i++;
				}
	
			}
		}
		else if (strcmp(argv[i], "--normalize") == 0 || strcmp(argv[i], "-n") == 0) {
			normalize = true;
		}
		else if (strcmp(argv[i], "--standarize") == 0 || strcmp(argv[i], "-s") == 0) {
			standarize = true;
		}
		else if (strcmp(argv[i], "--folds") == 0 || strcmp(argv[i], "-f") == 0) {
			if (i < argc - 1) {
				std::string h = argv[i + 1];
				numOfFolds = std::stoi(h);
				i++;
			}
		}
		else if (strcmp(argv[i], "--neighbours") == 0 || strcmp(argv[i], "-ne") == 0) {
			if (i < argc - 1) {
				std::string h = argv[i + 1];
				numOfNeighbours = std::stoi(h);
				i++;
			}
		}
		else if (strcmp(argv[i], "--distance") == 0 || strcmp(argv[i], "-di") == 0) {
			if (i < argc - 1) {
				std::string h = argv[i + 1];
				distanceFunc = std::stoi(h);
				i++;
				if (distanceFunc == DISTANCE::MINKOWSKI)
				{
					if (i < argc - 1) {
						std::string h2 = argv[i + 1];
						minkowskiOrder = std::stod(h2);
						i++;
					}
				}	
			}
		}
		else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
			std::cout << "USAGE: k-NN-Alhorithm.exe -d filename [ -h ] [ -s | -n ] [ -ne number [number] ] [ -f number ] [ -di number ]  \n";
			std::cout << "\tWHERE:\n";
			std::cout << "\t-h  \t--help		\tPrint this menu\n";
			std::cout << "\t-d n\t--data n	\tSets dataset to work with (obligatory). n specify index of class attribute\n";
			std::cout << "\t-n  \t--normalize	\tNormalize dataset before classification\n";
			std::cout << "\t-s  \t--standarize	\tStandarize dataset before classification\n";
			std::cout << "\t-f  \t--folds		\tSets number of folds in crossvalidation\n";
			std::cout << "\t-ne \t--neighbours	\tNumber of nearest neighbours to find\n";
			std::cout << "\t-di \t--distance	\tMetric used to calculete distance\n";
			std::cout << "\t			\t  1    Euclidean \n";
			std::cout << "\t			\t  2    Euclidean Squered (default) (Might save time)\n";
			std::cout << "\t			\t  3    Manhattan \n";
			std::cout << "\t			\t  4    Chebyshev \n";
			std::cout << "\t			\t  5 p  Minkovski of order p (default p=3) \n";
			return 0;
		}
		else {
			std::cerr << "Invalid argument! Write --help/-h to get help";
			return 0;
		}
	}
	if (data == "") {
		std::cerr << "You must provide dataset! (Command -d,--data). Write --help/-h to get help";
		return 1;
	}

	//Reading data from file
	std::vector<Instance> vec;
	readFromFile(vec, data, placeOfClassAttribute);

	//Normalizing data
	if (normalize)
	{
		vec = normalization(vec);
	}

	//Standarizing data
	if (standarize)
	{
		vec = standarization(vec);
	}

	//Creating folds
	kFold fold;
	fold.createFolds(vec, numOfFolds);

	//Creating Distance Class
	Distance* d;
	std::string distanceString;
	if (distanceFunc == DISTANCE::EUCLIDEAN) {
		d = new EuclideanDistance();
		distanceString = "Euclidean";
	}
	else if (distanceFunc == DISTANCE::EUCLIDEANSQUARED) {
		d = new EuclideanSquaredDistance();
		distanceString = "Euclidean Squared";
	}
	else if (distanceFunc == DISTANCE::MANHATTAN) {
		d = new ManhattanDistance();
		distanceString = "Manhattan";
	}
	else if (distanceFunc == DISTANCE::CHEBYSHEV) {
		d = new ChebyshevDistance();
		distanceString = "Chebyshev";
	}
	else if (distanceFunc == DISTANCE::MINKOWSKI) {
		d = new MinkowskiDistance(minkowskiOrder);
		distanceString = "Minkowski of order ";
		std::ostringstream os;
		os << minkowskiOrder;
		std::string str = os.str();
		distanceString.append(str);
	}	
	else {
		std::cerr << "There is no such distance function!. Write --help/-h to get help";
		return 1;
	}


	//OK - LET'S CLASSIFY SOME!
	std::vector<std::string> classes = getClasses(vec);
	ErrorMatrix err(classes);

	clock_t begin = clock();
	for (int i = 0; i < numOfFolds; i++) {
		std::vector<Instance> trainingSet = fold.getAllButKFold(i);
		std::vector<Instance> validationSet = fold.getKFold(i);

		//Building classifier
		kNNClassifier kl;
		kl.build(trainingSet);
		kl.setNumOfNeighbours(numOfNeighbours);
		kl.setDistanceMetrics(d);

		for (Instance ins : validationSet) {
			err.addResult(ins.getClass(), kl.classify(ins.getAttributes()));
		}
	}
	clock_t end = clock();

	//Printing results
	std::cout << "==================INFO ABOUT TEST=================\n";

	std::string file = data;
	size_t found;
	found = file.find_last_of("/\\");
	std::cout << "File: " << file.substr(found + 1);

	std::cout << " ,Attributes: " << vec[0].getAttributes().size();
	std::cout << " ,Instances: " << vec.size() << std::endl;

	std::cout << "Classes: ";
	int size = classes.size();
	for (int i = 0; i < size; i++) {
		std::cout << classes[i];
		if (i < size - 1) std::cout << ", ";
	}
	std::cout << std::endl;

	std::cout << "Method: " << numOfFolds << "-fold cross-validation" << std::endl;
	std::cout << "Metric: " << distanceString << std::endl;
	std::cout << "Nearest neighbours checked: " << numOfNeighbours << std::endl;
	std::cout << "Standarized=" << ((standarize) ? "yes" : "no");
	std::cout << " ,Normalization=" << ((normalize) ? "yes" : "no") << std::endl;
	std::cout << "Computing time: " << end - begin << "ms" << std::endl;

	std::cout << "===================TEST RESULTS===================\n";
	std::cout << "Error Matrix:\n";
	std::cout << err.toString();
	std::cout << "Statistics:\n";
	std::cout << err.getStatisticsString();
	std::cout << std::endl;
	

	delete d;
	return 0;
}