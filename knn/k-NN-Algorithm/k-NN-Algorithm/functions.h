#pragma once
#include <vector>
#include "Instance.h"
#include <string>

/**
	This function fill vec with instances located in file.
	Each line stands for one Instance. Attributes are
	separated by comma.
*/

void readFromFile(std::vector<Instance> &vec, const char* file, int classAttributePosition);
std::string vectorOfInstancesToString(const std::vector<Instance> &vec);
std::vector<Instance> normalization(std::vector<Instance> &vec);
std::vector<Instance> standarization(std::vector<Instance> &vec);
