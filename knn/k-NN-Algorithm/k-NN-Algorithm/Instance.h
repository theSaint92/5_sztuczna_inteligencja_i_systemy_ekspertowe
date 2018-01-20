#pragma once
#include <vector>
#include <string>

class Instance
{
private:
	std::string instanceClass;
	std::vector<double> attributes;

public:
	Instance();
	Instance(std::vector<double> attributes);
	Instance(std::string instanceClass, std::vector<double> attributes);

	//Getters
	std::string getClass();
	std::vector<double> getAttributes();

	//Setters
	void setClass(std::string instanceClass);
	void setAttributes(std::vector<double> attributes);
	
	//toString()
	std::string toString();
};

