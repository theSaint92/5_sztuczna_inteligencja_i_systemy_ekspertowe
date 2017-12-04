#include "stdafx.h"
#include "Board.h"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>


Board::Board()
{
	this->rows = 4;
	this->cols = 4;
	// generete some random state of the puzzle using built-in random generator:
	for (int i = 0; i < 16; i++) this->values.push_back(i);
	std::random_shuffle(this->values.begin(), this->values.end());
}

Board::Board(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
	// generete some random state of the puzzle using built-in random generator:
	int size = this->rows*this->cols;
	for (int i = 0; i < size; i++) this->values.push_back(i);
	std::random_shuffle(this->values.begin(), this->values.end());
}

Board::Board(int rows, int cols, std::vector<int> values)
{
	this->rows = rows;
	this->cols = cols;
	this->values = values;
}

Board::~Board()
{
}

int Board::transformToState()
{
	return 2;
}

std::string Board::toString()
{
	std::ostringstream oss;

	if (!this->values.empty())
	{
		// Convert all but the last element to avoid a trailing ","
		std::copy(this->values.begin(), this->values.end() - 1,
			std::ostream_iterator<int>(oss, " "));

		// Now add the last element with no delimiter
		oss << this->values.back();
	}

	return oss.str();
}