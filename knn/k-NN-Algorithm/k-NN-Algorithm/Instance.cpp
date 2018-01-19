#include "Instance.h"

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
