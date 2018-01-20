#pragma once
#include <string>
#include <vector>

class ErrorMatrix {

	std::vector<std::string> instanceClasses;
	std::vector<std::vector<int>> errorMatrix;

public:
	ErrorMatrix(std::vector<std::string> instanceClasses);
	void addResult(std::string expectedValue, std::string value);
	std::string toString();
	std::string getStatisticsString();
	
};