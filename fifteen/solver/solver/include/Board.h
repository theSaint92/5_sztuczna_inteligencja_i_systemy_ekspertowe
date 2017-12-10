#pragma once

#include "Transformer.h"
#include "HexaTransformer.h"
#include "FactorialTransformer.h"
#include "Result.h"
#include <vector>
#include <string>

class Board
{
private:
	static Transformer* transformer;
	std::vector<int> values;

	char oppositeMove(char move);
	void getOrderInfo(std::string givenOrder, bool &randomOrder, std::vector<char> &order); //edits order and randomOrder correctly based on givenOrder
	uint64_t getSolvedState(); //Returns how solved state of board looks
	

public:

	static int rows;
	static int cols;

	//Constructors
	Board();
	Board(int rows, int cols);
	Board(int rows, int cols, std::vector<int> values);
	Board(int rows, int cols, char justToRecognize); //Constructor that doesnt initialize vector values to save some time;

	~Board(){};

	//Getters
	int getRows();
	int getCols();
	std::vector<int> getValues();

	//Methods
	uint64_t transformToState();
	void getFromState(uint64_t state);
	std::string toString();
	static void changeTransformer(Transformer &transformer);
	bool moveFreeTile(char moveDirection);
	bool isSolvable();

	//Solving methods
	Result solveWithBFS(std::string order);
	Result solveWithDFS(std::string order);
	Result solveWithAStar(int heuristic);

	//Some "power" measures
	//int manhattan(uint64_t &state);
	//uint64_t scoreTileRightPlace(uint64_t const &state);
	//
	//struct TileOnPlaceComparator;
};

