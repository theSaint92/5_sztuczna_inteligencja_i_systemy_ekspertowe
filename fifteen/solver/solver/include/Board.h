#pragma once

#include <vector>
#include <string>

class Board
{
private:
	int rows;
	int cols;
	std::vector<int> values;

public:

	//Constructors and Destructors
	Board();
	Board(int rows, int cols);
	Board(int rows, int cols, std::vector<int> values);

	~Board();

	//Getters
	int getRows();
	int getCols();
	std::vector<int> getValues();

	//Methods
	uint64_t transformToState();
	void getFromState(uint64_t state);
	std::string toString();
};

