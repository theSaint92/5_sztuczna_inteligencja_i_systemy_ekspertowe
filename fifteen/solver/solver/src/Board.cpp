#pragma once

#include "Board.h"
#include <vector>
#include <algorithm> //random_shuffle
#include <sstream> //toString()
#include <string> //toString()
#include <queue> 
#include <stack>
#include <map>
#include <iostream>
#include <utility> //priority_queue

#include "Comparators.h"
#include "Factorial.h"

Transformer* Board::transformer = NULL;
int Board::rows = 0;
int Board::cols = 0;

Board::Board()
{
	Board::rows = 4;
	Board::cols = 4;
	// generete some random state of the puzzle using built-in random generator:
	for (int i = 0; i < 16; i++) this->values.push_back(i);
	std::random_shuffle(this->values.begin(), this->values.end());
}

Board::Board(int rows, int cols)
{
	if (rows*cols > 16 || rows*cols <= 0) throw std::invalid_argument("rows*cols must be in range (1...16)");
	Board::rows = rows;
	Board::cols = cols;
	// generete some random state of the puzzle using built-in random generator:
	int size = Board::rows*Board::cols;
	for (int i = 0; i < size; i++) this->values.push_back(i);
	std::random_shuffle(this->values.begin(), this->values.end());
}

Board::Board(int rows, int cols, std::vector<int> values)
{
	if (rows*cols > 16 || rows*cols <= 0) throw std::invalid_argument("rows*cols must be in range (1...16)");
	if (rows*cols != values.size()) throw std::invalid_argument("rows*cols must be equal to values vector size");
	Board::rows = rows;
	Board::cols = cols;
	this->values = values;
}

Board::Board(int rows, int cols, char justToRecognize)
{
	if (rows*cols > 16 || rows*cols <= 0) throw std::invalid_argument("rows*cols must be in range (1...16)");
	Board::rows = rows;
	Board::cols = cols;
}

uint64_t Board::transformToState()
{
	if( transformer == NULL ) throw std::domain_error("Transformer is not defined!");
	return this->transformer->getState(this->values);
}

void Board::getFromState(uint64_t state)
{
	if (transformer == NULL) throw std::domain_error("Transformer is not defined!");
	this->values = this->transformer->getVector(Board::rows*Board::cols, state);
}

std::string Board::toString()
{
	std::ostringstream oss;

	if (!this->values.empty())
	{
		size_t size = this->values.size();
		
		for (unsigned int i = 0; i < size; i++) {
			oss << this->values[i] << "\t";
			if ((i+1)%Board::cols == 0) oss << "\n";
		}
	}

	return oss.str();
}

void Board::changeTransformer(Transformer &newTransformer)
{
	transformer = &newTransformer;
}

bool Board::moveFreeTile(char moveDirection)
{
	//Getting position of 0 element
	int zeroPosition = -1;
	for (unsigned int i = 0; i < this->values.size(); i++)
	{
		if (!values[i])
		{
			zeroPosition = i;
			break;
		}
	}

	//int currentRow = zeroPosition / cols;
	//int currentCol = zeroPosition%cols;
	//std::cout << "ROW: " << currentRow << ", COLUMN: " << currentCol << std::endl;

	if (zeroPosition == -1) throw std::domain_error("Board doesn't have 0 element?!");

	if (moveDirection == 'L') {
		//We can't left if 0 element is in first column
		if (!(zeroPosition%cols)) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition-1]);
	}
	else if (moveDirection == 'P') {
		//We can't right if 0 element is in last column
		if (!((zeroPosition+1)%cols)) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition + 1]);
	}
	else if (moveDirection == 'G') {
		//We can't up if 0 element is in first row
		if (!(zeroPosition/cols)) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition - Board::cols]);
	}
	else if (moveDirection == 'D') {
		//We can't down if 0 element is in last row
		if (zeroPosition / cols == rows-1) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition + Board::cols]);
	}
	else return false;
	return true;
}

uint64_t Board::getSolvedState() {
	std::vector<int> solvedSeq;
	int size = Board::rows*Board::cols;
	for (int i = 1; i < size; i++) solvedSeq.push_back(i);
	solvedSeq.push_back(0);

	Board* solvedBoard = new Board(Board::rows, Board::cols, solvedSeq);
	uint64_t result = solvedBoard->transformToState();
	delete solvedBoard;
	return result;
}

void Board::getOrderInfo(std::string givenOrder, bool &randomOrder, std::vector<char> &order)
{
	if (givenOrder.size() == 1) {
		if (givenOrder.at(0) == 'R' || givenOrder.at(0) == 'r') {
			randomOrder = true;
			order = { 'L','P','G','D' };
			std::random_shuffle(order.begin(), order.end());
		}
		else throw std::invalid_argument("Unidentified order of search");
	}
	else if (givenOrder.size() == 4) {
		order.clear();
		randomOrder = false;
		for (int i = 0; i < 4; i++) {
			if (givenOrder.at(i) == 'L' || givenOrder.at(i) == 'l') {
				if (!order.empty()) {
					if (std::find(order.begin(), order.end(), 'L') != order.end()) {
						throw std::invalid_argument("Unidentified order of search");
					}
				}
				order.push_back('L');
			}
			else if (givenOrder.at(i) == 'P' || givenOrder.at(i) == 'p') {
				if (!order.empty()) {
					if (std::find(order.begin(), order.end(), 'P') != order.end()) {
						throw std::invalid_argument("Unidentified order of search");
					}
				}
				order.push_back('P');
			}
			else if (givenOrder.at(i) == 'G' || givenOrder.at(i) == 'g') {
				if (!order.empty()) {
					if (std::find(order.begin(), order.end(), 'G') != order.end()) {
						throw std::invalid_argument("Unidentified order of search");
					}
				}
				order.push_back('G');
			}
			else if (givenOrder.at(i) == 'D' || givenOrder.at(i) == 'd') {
				if (!order.empty()) {
					if (std::find(order.begin(), order.end(), 'D') != order.end()) {
						throw std::invalid_argument("Unidentified order of search");
					}
				}
				order.push_back('D');
			}
			else throw std::invalid_argument("Unidentified order of search");
		}
	}
	else throw std::invalid_argument("Unidentified order of search");
}

std::vector<int> Board::getValues() {
	return this->values;
}

char Board::oppositeMove(char move) {
	if (move == 'L') return 'P';
	else if (move == 'P') return 'L';
	else if (move == 'G') return 'D';
	else if (move == 'D') return 'G';
	else if (move == (char)0) return (char)0;
	else throw std::invalid_argument("Unspecified Direction: " + move);
}

bool Board::isSolvable() {
	//Get permutation
	std::vector<int> permutation = this->values;
	//Get rid of 0 element (represents empty puzzle)
	int emptyPuzzleRow;
	for (unsigned int i = 0; i < permutation.size(); i++) {
		if (permutation[i] == 0) {
			permutation.erase(permutation.begin()+ i);
			emptyPuzzleRow = i / Board::cols + 1; //Getting row of empty puzzle
			break;
		}
	}
	//1 row or 1col case
	if (Board::cols == 1 || Board::rows == 1) {
		return std::is_sorted(permutation.begin(), permutation.end());
	}
	//Getting inversions count
	int inversions = 0;
	for (unsigned int i = 0; i < permutation.size(); i++) {
		for (unsigned int j = i+1; j < permutation.size(); j++) {
			if (permutation[i] > permutation[j]) inversions++;
		}
	}

	if (Board::cols % 2 == 1 && inversions%2 == 0) { //Theorem 1
		return true;
	}
	if (Board::cols %2 == 0) { //Theorem 2&3
		if ((Board::rows - emptyPuzzleRow) % 2 == 0 && inversions % 2 == 0) return true; //Theorem 2
		else if ((Board::rows - emptyPuzzleRow) % 2 == 1 && inversions % 2 == 1) return true; //Theorem 3
	}
	return false;
}

Result Board::solveWithBFS(std::string givenOrder) 
{
	Result result;
	try {

		//Getting order vector
		std::vector<char> order;
		bool randomOrder;
		getOrderInfo(givenOrder, randomOrder, order);

		uint64_t startState = this->transformToState();
		uint64_t endState = this->getSolvedState();

		result.visitedStates = 1;
		//Maybe it's already solved?
		if (startState == endState) {
			result.steps = 0;
			return result;
		}

		std::queue<uint64_t> bfsQueue;
		//Map of visited states - pair is <state, move_from_prev_state>
		std::map<uint64_t, char> visitedStates;

		bfsQueue.push(startState);
		visitedStates.insert(std::make_pair(startState, (char)0 ));
		while (!bfsQueue.empty())
		{
			//Shuffle order if it's random
			if (randomOrder) std::random_shuffle(order.begin(), order.end());

			//Get element to search from queue
			uint64_t currentState = bfsQueue.front();
			bfsQueue.pop();

			//Get the move where the previous state comes from
			char moveToPrev = oppositeMove(visitedStates[currentState]);

			//Now get the board of currentstate
			Board currentStateBoard(Board::rows, Board::cols, (char)0);
			currentStateBoard.getFromState(currentState);
			//std::cout << currentStateBoard.toString() << std::endl;

			for (int i = 0; i < 4; i++) {
				if (order[i] != moveToPrev) {
					Board nextStateBoard(Board::rows, Board::cols, currentStateBoard.getValues());
					if (nextStateBoard.moveFreeTile(order[i])) {

						//This if tries to add new state to map - will fail if it already exist
						uint64_t nextState = nextStateBoard.transformToState();
						bool addStateToMap = false;
						addStateToMap = visitedStates.insert(std::make_pair(nextState, order[i])).second;
						if (addStateToMap)
						{
							result.visitedStates++;
							//Check if we have already finished
							if (nextState == endState) {
								result.steps = 1;
								result.seqOfMoves += order[i];
								uint64_t previousState = currentState;
								char lastMove = visitedStates[previousState];
								Board previousStateBoard(Board::rows, Board::cols, (char)0);
								while (lastMove != (char)0) {
									result.steps++;
									result.seqOfMoves += lastMove;

									//Getting previousState and lastMove
									previousStateBoard.getFromState(previousState);
									previousStateBoard.moveFreeTile(oppositeMove(lastMove));
									previousState = previousStateBoard.transformToState();
									lastMove = visitedStates[previousState];
								}
								reverse(result.seqOfMoves.begin(), result.seqOfMoves.end());
								return result;
							}
							else {
								bfsQueue.push(nextState);
							}
						}
					}
				}
			}
		}
	} catch (const std::exception& e) {
		std::string error;
		error.append("Meet an exception! VisitedStates: ");
		error.append(std::to_string(result.visitedStates));
		error.append("\n");
		error.append(e.what());
		throw std::out_of_range(error);
	}

	return result;
}

Result Board::solveWithDFS(std::string givenOrder)
{
	Result result;
	try {

		//Getting order vector
		std::vector<char> order;
		bool randomOrder;
		getOrderInfo(givenOrder, randomOrder, order);

		//We need to reverse it so first searched is actually on top
		reverse(order.begin(), order.end());

		uint64_t startState = this->transformToState();
		uint64_t endState = this->getSolvedState();

		//Maybe it's already solved?
		//if (startState == endState) {
		//	result.steps = 0;
		//	return result;
		//}

		std::stack<uint64_t> dfsStack;
		//Map of visited states - pair is <state, move_from_prev_state>
		std::map<uint64_t, char> visitedStates;

		dfsStack.push(startState);
		visitedStates.insert(std::make_pair(startState, (char)0));
		while (!dfsStack.empty())
		{
			//Shuffle order if it's random
			if (randomOrder) std::random_shuffle(order.begin(), order.end());

			//Get element to search from queue
			uint64_t currentState = dfsStack.top();
			dfsStack.pop();
			result.visitedStates++;

			//Check if we have already finished
			if (currentState == endState) {
				uint64_t previousState = currentState;
				char lastMove = visitedStates[previousState];
				Board previousStateBoard(Board::rows, Board::cols, (char)0);
				while (lastMove != (char)0) {
					result.steps++;
					result.seqOfMoves += lastMove;

					//Getting previousState and lastMove
					previousStateBoard.getFromState(previousState);
					previousStateBoard.moveFreeTile(oppositeMove(lastMove));
					previousState = previousStateBoard.transformToState();
					lastMove = visitedStates[previousState];
				}
				reverse(result.seqOfMoves.begin(), result.seqOfMoves.end());
				return result;
			}
			else {

				//Get the move where the previous state comes from
				char moveToPrev = oppositeMove(visitedStates[currentState]);

				//Now get the board of currentstate
				Board currentStateBoard(Board::rows, Board::cols, (char)0);
				currentStateBoard.getFromState(currentState);
				//std::cout << currentStateBoard.toString() << std::endl;

				for (int i = 0; i < 4; i++) {
					if (order[i] != moveToPrev) {
						Board nextStateBoard(Board::rows, Board::cols, currentStateBoard.getValues());
						if (nextStateBoard.moveFreeTile(order[i])) {

							uint64_t nextState = nextStateBoard.transformToState();
							bool addStateToMap = false;

							//This if tries to add new state to map - will fail if it already exist
							addStateToMap = visitedStates.insert(std::make_pair(nextState, order[i])).second;

							if (addStateToMap)
							{
								dfsStack.push(nextState);
							}
						}
					}
				}
			}
		}
	}
	catch (const std::exception& e) {
		std::string error;
		error.append("Meet an exception! VisitedStates: ");
		error.append(std::to_string(result.visitedStates));
		error.append("\n");
		error.append(e.what());
		throw std::out_of_range(error);
	}
	return result;
}

Result Board::solveWithAStar(int heurisitc)
{
	Result result;
	try 
	{
		uint64_t startState = this->transformToState();
		uint64_t endState = this->getSolvedState();
		char order[4] = { 'L','P','G','D' };

		//auto comparator = [](uint64_t left, uint64_t right) { return manhattan(left) > manhattan(right); };
		//if (strcmp(heuristic, "1") == 0) {
		//	//Ustaw manhattan
		//	std::cout << "MANHATTAN!!!";
		//	auto comparator = [](uint64_t left, uint64_t right) { return manhattan(left) > manhattan(right); };
		//}
		//if (strcmp(heuristic, "2") == 0) {
		//	//Ustaw tileOnPlaceComparator
		//	std::cout << "TILE ON PLACE!!!";
		//	auto comparator = [](uint64_t left, uint64_t right) { return scoreTileRightPlace(left) > scoreTileRightPlace(right); };
		//}
		//auto comparator = [](uint64_t left, uint64_t right) { return scoreTileRightPlace(left) > scoreTileRightPlace(right); };
		////Lambda Expressions
		//auto manhattanComparator = [](uint64_t left, uint64_t right) { return manhattan(left) > manhattan(right); };
		//auto tileOnPlaceComparator = [](uint64_t left, uint64_t right) { return scoreTileRightPlace(left) > scoreTileRightPlace(right); };

		//comparator = manhattanComparator;

		Comparator::heuristic = heurisitc;
		std::priority_queue<uint64_t, std::vector<uint64_t>, Comparator> prioQueue;
		//Map of visited states - pair is <state, move_from_prev_state>
		std::map<uint64_t, char> visitedStates;

		prioQueue.push(startState);
		visitedStates.insert(std::make_pair(startState, (char)0));
		while (!prioQueue.empty())
		{

			//Get element to search from queue
			uint64_t currentState = prioQueue.top();
			prioQueue.pop();
			result.visitedStates++;

			//Check if we have already finished
			if (currentState == endState) {
				uint64_t previousState = currentState;
				char lastMove = visitedStates[previousState];
				Board previousStateBoard(Board::rows, Board::cols, (char)0);
				while (lastMove != (char)0) {
					result.steps++;
					result.seqOfMoves += lastMove;

					//Getting previousState and lastMove
					previousStateBoard.getFromState(previousState);
					previousStateBoard.moveFreeTile(oppositeMove(lastMove));
					previousState = previousStateBoard.transformToState();
					lastMove = visitedStates[previousState];
				}
				reverse(result.seqOfMoves.begin(), result.seqOfMoves.end());
				return result;
			}
			else {

				//Get the move where the previous state comes from
				char moveToPrev = oppositeMove(visitedStates[currentState]);

				//Now get the board of currentstate
				Board currentStateBoard(Board::rows, Board::cols, (char)0);
				currentStateBoard.getFromState(currentState);
				//std::cout << currentStateBoard.toString() << std::endl;

				for (int i = 0; i < 4; i++) {
					if (order[i] != moveToPrev) {
						Board nextStateBoard(Board::rows, Board::cols, currentStateBoard.getValues());
						if (nextStateBoard.moveFreeTile(order[i])) {

							uint64_t nextState = nextStateBoard.transformToState();
							bool addStateToMap = false;
							//This tries to add new state to map - will fail if it already exist
							addStateToMap = visitedStates.insert(std::make_pair(nextState, order[i])).second;

							if (addStateToMap)
							{
								prioQueue.push(nextState);
							}
						}
					}
				}
			}
		}
	}
	catch (const std::exception& e) {
		std::string error;
		error.append("Meet an exception! VisitedStates: ");
		error.append(std::to_string(result.visitedStates));
		error.append("\n");
		error.append(e.what());
		throw std::out_of_range(error);
	}
	return result;
}

//int Board::manhattan(uint64_t &state) {
//	//Current board
//	Board currentStateBoard(Board::rows, Board::cols, (char)0);
//	currentStateBoard.getFromState(state);
//
//	for (int i= 0; i < Board::rows; i++) {
//		for (int j = 0; j < Board::cols; j++) {
//
//		}
//	}
//
//	//Create solved Board of this size
//	std::vector<int> solvedSeq;
//	int size = Board::rows*Board::cols;
//	for (int i = 1; i < size; i++) solvedSeq.push_back(i);
//	solvedSeq.push_back(0);
//	Board solvedBoard(Board::rows, Board::cols, solvedSeq);
//}

//uint64_t Board::scoreTileRightPlace(int rows, int cols; uint64_t const &state) {
//	//Current board
//	uint64_t result = 0;
//	Board currentStateBoard(rows, cols, (char)0);
//	currentStateBoard.getFromState(state);
//	std::vector<int> values = transformer->getVector(cols*rows, state);
//
//	for (int i = 0; i < values.size(); i++) {
//		if (values[i] == i + 1) {
//			result += Factorial::getInstance().get(values.size() - i);
//			std::cout << i << " IS IN RIGHT PLACE: " << result;
//		}
//	}
//	return result;
//}
//
//struct Board::TileOnPlaceComparator {
//	TileOnPlaceComparator(Board b) : board(b){}
//
//	Board board;
//	bool operator()(uint64_t const &u, uint64_t const &v) {
//		return board.scoreTileRightPlace(u) < board.scoreTileRightPlace(v);
//	}
//};