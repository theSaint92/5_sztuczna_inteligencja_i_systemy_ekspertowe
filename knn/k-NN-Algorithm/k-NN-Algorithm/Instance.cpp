#include "Instance.h"
#include <sstream>
#include <iomanip>

Instance::Instance()
{
	std::vector<double> empty;
	this->attributes = empty;
	this->instanceClass = "";
}

Instance::Instance(std::vector<double> attributes)
{
	this->attributes = attributes;
	this->instanceClass = "";
}

Instance::Instance(std::string instanceClass, std::vector<double> attributes)
{
	this->instanceClass = instanceClass;
	this->attributes = attributes;
}

std::string Instance::getClass() 
{
	return this->instanceClass;
}

std::vector<double> Instance::getAttributes()
{
	return this->attributes;
}

void Instance::setClass(std::string instanceClass)
{
	this->instanceClass = instanceClass;
}

void Instance::setAttributes(std::vector<double> attributes)
{
	this->attributes = attributes;
}

std::string Instance::toString()
{
	std::stringstream ss;

	unsigned int size = this->attributes.size();
	for (unsigned int i = 0; i < size ; i++) {
		ss << std::setw(7) << std::setprecision(5) << this->attributes[i] << " ";
	}
	ss << ": " << this->instanceClass;

	return ss.str();
}