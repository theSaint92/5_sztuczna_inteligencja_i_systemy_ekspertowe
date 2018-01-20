#include "functions.h"
#include <cmath> //sqrt

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

void readFromFile(std::vector<Instance> &vec, const char* filename, int classAttributePosition)
{
	std::fstream file;
	file.open(filename, std::fstream::in);
	if (file.good() == true)
	{
		std::string currentLine;
		while (!file.eof()) {
			std::getline(file,currentLine);

			if (currentLine.length() != 0) {
				std::istringstream ss(currentLine);
				std::vector<double> attributes;
				std::string instanceClass;

				int position = 1;
				while (!ss.eof())
				{
					std::string s;
					getline(ss, s, ',');

					if (position == classAttributePosition) instanceClass = s;
					else {
						attributes.push_back(std::stod(s));
					}
					position++;

				}

				Instance inst(instanceClass, attributes);
				vec.push_back(inst);
			}
		}
		file.close();
	}
}

std::string vectorOfInstancesToString(const std::vector<Instance> &vec)
{
	std::stringstream ss;
	for (Instance ins : vec) {
		ss << ins.toString() << "\n";
	}
	return ss.str();
}

std::vector<Instance> normalization(std::vector<Instance> &vec)
{
	int attrSize = vec[0].getAttributes().size();
	int vecSize = vec.size();

	//Creating transposed matrix of attributes
	std::vector< std::vector<double> > attrTransposed;
	for (int i = 0; i < attrSize; i++) {
		std::vector<double> attributeColumn;
		for (int j = 0; j < vecSize; j++) {
			attributeColumn.push_back(vec[j].getAttributes()[i]);
		}
		attrTransposed.push_back(attributeColumn);
	}
	
	//Vectors that store maximum and minimum value of each row
	std::vector<double> maxSize;
	std::vector<double> minSize;

	for (int i = 0; i < attrSize; i++) {
		maxSize.push_back(attrTransposed[i][0]);
		minSize.push_back(attrTransposed[i][0]);
	}

	for (int i = 0; i < attrSize; i++) {
		for (int j = 0; j < vecSize; j++) {
			if (maxSize[i] < attrTransposed[i][j]) maxSize[i] = attrTransposed[i][j];
			if (minSize[i] > attrTransposed[i][j]) minSize[i] = attrTransposed[i][j];
		}
	}

	//Tworzymy vector wynikowy który podstawimy do vec
	std::vector<Instance> result;
	std::vector< std::vector<double> > resultAttributes;
	for (int i = 0; i < vecSize; i++) {
		std::vector<double> currentResult;
		for (int j = 0; j < attrSize; j++) {
			currentResult.push_back((attrTransposed[j][i] - minSize[j]) / (maxSize[j] - minSize[j]));
		}
		resultAttributes.push_back(currentResult);
	}

	for (int i = 0; i < vecSize; i++) {
		Instance ins(vec[i].getClass(), resultAttributes[i]);
		result.push_back(ins);
	}

	////Testing
	//for (int i = 0; i < vecSize; i++) {
	//	for (int j = 0; j < attrSize; j++) {
	//		std::cout << attrTransposed[j][i] << "\t";
	//	}
	//	std::cout << "\n";
	//}
	//
	//std::cout << "\nmaxSize: ";
	//for (int i = 0; i < attrSize; i++) {
	//	std::cout << maxSize[i] << "\t";
	//}
	//std::cout << "\nminSize: ";
	//for (int i = 0; i < attrSize; i++) {
	//	std::cout << minSize[i] << "\t";
	//}
	//
	//std::cout << std::endl;
	//std::cout << vectorOfInstancesToString(result) << std::endl;

	return result;
}

std::vector<Instance> standarization(std::vector<Instance> &vec)
{
	int attrSize = vec[0].getAttributes().size();
	int vecSize = vec.size();

	//Creating transposed matrix of attributes
	std::vector< std::vector<double> > attrTransposed;
	for (int i = 0; i < attrSize; i++) {
		std::vector<double> attributeColumn;
		for (int j = 0; j < vecSize; j++) {
			attributeColumn.push_back(vec[j].getAttributes()[i]);
		}
		attrTransposed.push_back(attributeColumn);
	}

	//Vectors that store mean and std value of each row
	std::vector<double> mean;
	std::vector<double> std;

	for (int i = 0; i < attrSize; i++) {
		mean.push_back(0);
		std.push_back(0);
	}

	for (int i = 0; i < attrSize; i++) {
		for (int j = 0; j < vecSize; j++) {
			mean[i] += attrTransposed[i][j];
		}
		mean[i] /= vecSize;
	}

	for (int i = 0; i < attrSize; i++) {
		for (int j = 0; j < vecSize; j++) {
			std[i] += (attrTransposed[i][j] - mean[i])*(attrTransposed[i][j] - mean[i]);
		}
		std[i] /= vecSize-1;
		std[i] = sqrt(std[i]);
	}


	//Tworzymy vector wynikowy który podstawimy do vec
	std::vector<Instance> result;
	std::vector< std::vector<double> > resultAttributes;
	for (int i = 0; i < vecSize; i++) {
		std::vector<double> currentResult;
		for (int j = 0; j < attrSize; j++) {
			currentResult.push_back((attrTransposed[j][i] - mean[j]) / std[j] );
		}
		resultAttributes.push_back(currentResult);
	}

	for (int i = 0; i < vecSize; i++) {
		Instance ins(vec[i].getClass(), resultAttributes[i]);
		result.push_back(ins);
	}

	//Testing
	//for (int i = 0; i < vecSize; i++) {
	//	for (int j = 0; j < attrSize; j++) {
	//		std::cout << attrTransposed[j][i] << "\t";
	//	}
	//	std::cout << "\n";
	//}
	//
	//std::cout << "\nmean: ";
	//for (int i = 0; i < attrSize; i++) {
	//	std::cout << mean[i] << "\t";
	//}
	//std::cout << "\nstd: ";
	//for (int i = 0; i < attrSize; i++) {
	//	std::cout << std[i] << "\t";
	//}
	//
	//std::cout << std::endl;
	//std::cout << vectorOfInstancesToString(result) << std::endl;

	return result;
}

std::vector<std::string> getClasses(const std::vector<Instance> &vec)
{
	std::vector<std::string> result;
	for (Instance ins : vec)
	{
		// classList is non-empty
		bool found = false;
		for (std::string className : result) {
			if (className == ins.getClass())
			{
				found = true;
				break;
			}
		}
		if (!found) {
			result.push_back(ins.getClass());
		}
	}
	return result;
}