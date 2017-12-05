#include "Board.h"
#include <vector>
#include <algorithm> //random_shuffle
#include <sstream> //toString()
#include <string> //toString()


Board::Board()
{
	this->transformer = new HexaTransformer();
	this->rows = 4;
	this->cols = 4;
	// generete some random state of the puzzle using built-in random generator:
	for (int i = 0; i < 16; i++) this->values.push_back(i);
	std::random_shuffle(this->values.begin(), this->values.end());
}

Board::Board(int rows, int cols)
{
	if (rows*cols > 16 || rows*cols <= 0) throw std::invalid_argument("rows*cols must be in range (1...16)");
	this->transformer = new HexaTransformer();
	this->rows = rows;
	this->cols = cols;
	// generete some random state of the puzzle using built-in random generator:
	int size = this->rows*this->cols;
	for (int i = 0; i < size; i++) this->values.push_back(i);
	std::random_shuffle(this->values.begin(), this->values.end());
}

Board::Board(int rows, int cols, std::vector<int> values)
{
	if (rows*cols > 16 || rows*cols <= 0) throw std::invalid_argument("rows*cols must be in range (1...16)");
	if (rows*cols != values.size()) throw std::invalid_argument("rows*cols must be equal to values vector size");
	this->transformer = new HexaTransformer();
	this->rows = rows;
	this->cols = cols;
	this->values = values;
}

Board::~Board() 
{
	delete this->transformer;
}

uint64_t Board::transformToState()
{
	return this->transformer->getState(this->values);
}

void Board::getFromState(uint64_t state)
{
	this->values = transformer->getVector(this->rows*this->cols, state);
}

std::string Board::toString()
{
	std::ostringstream oss;

	if (!this->values.empty())
	{
		int size = this->values.size();
		
		for (int i = 0; i < size; i++) {
			oss << this->values[i] << "\t";
			if ((i+1)%this->cols == 0) oss << "\n";
		}
	}

	return oss.str();
}

void Board::changeTransformer(const std::string &transformer)
{
	if (!transformer.compare("hexadecimal"))
	{
		delete this->transformer;
		this->transformer = new HexaTransformer();
	}
	else if (!transformer.compare("factorial"))
	{
		delete this->transformer;
		this->transformer = new FactorialTransformer();
	}
	
}