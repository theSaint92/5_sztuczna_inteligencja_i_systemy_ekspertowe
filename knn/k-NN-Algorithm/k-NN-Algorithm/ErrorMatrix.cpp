#include "ErrorMatrix.h"
#include <sstream>
#include <iomanip>

ErrorMatrix::ErrorMatrix(std::vector<std::string> instanceClasses) 
{
	this->instanceClasses = instanceClasses;
	int size = instanceClasses.size();
	for (int i = 0; i < size; i++)
	{
		std::vector<int> newVector(size, 0);
		this->errorMatrix.push_back(newVector);
	}
}

void ErrorMatrix::addResult(std::string expectedValue, std::string actuallValue)
{
	int size = instanceClasses.size();
	int expected;
	int actuall;
	for (int i = 0; i < size; i++)
	{
		if (expectedValue == this->instanceClasses[i]) expected = i;
		if (actuallValue == this->instanceClasses[i]) actuall = i;
	}
	this->errorMatrix[expected][actuall]++;
}

std::string ErrorMatrix::toString()
{
	std::stringstream ss;
	int size = instanceClasses.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			ss << std::setw(4) << this->errorMatrix[i][j] << " ";
		}
		ss << "  | " << this->instanceClasses[i] << std::endl;
	}
	return ss.str();
}

std::string ErrorMatrix::getStatisticsString()
{
	std::stringstream ss;
	int size = instanceClasses.size();

	std::vector<int> sizeOfClasses;
	for (int i = 0; i < size; i++) {
		int currentSize = 0;
		for (int j = 0; j < size; j++) {
			currentSize += this->errorMatrix[i][j];
		}
		sizeOfClasses.push_back(currentSize);
	}

	std::vector<int> falsePositive;
	std::vector<int> falseNegative;
	for (int i = 0; i < size; i++) {
		int falseP = 0;
		int falseN = 0;
		for (int j = 0; j < size; j++) {
			if (i != j) {
				falseN += this->errorMatrix[i][j];
				falseP += this->errorMatrix[j][i];
			}
			
		}
		falsePositive.push_back(falseP);
		falseNegative.push_back(falseN);
	}

	ss << " False Positive Ratio (I):\n";
	for (int i = 0; i < size; i++) {
		ss << "   " << instanceClasses[i] << " - ";
		double percent = (double)falsePositive[i]/(this->errorMatrix[i][i] + falsePositive[i]) * 100;
		ss << std::fixed << std::setprecision(2) << percent << "%";
		ss << " (" << falsePositive[i] << ")" << std::endl;
	}

	ss << " False Negative Ratio (II):\n";
	for (int i = 0; i < size; i++) {
		ss << "   " << instanceClasses[i] << " - ";
		double percent = (double)falseNegative[i] /sizeOfClasses[i] * 100;
		ss << std::fixed << std::setprecision(2) << percent << "%";
		ss << " (" << falseNegative[i] << ")" << std::endl;
	}

	ss << " Accuracy: ";
	int total = 0;
	int correct = 0;
	for (int i = 0; i < size; i++) {
		total += sizeOfClasses[i];
		correct += this->errorMatrix[i][i];
	}
	double percent = (double)correct / total * 100;
	ss << std::fixed << std::setprecision(2) << percent << "%";

	return ss.str();
}