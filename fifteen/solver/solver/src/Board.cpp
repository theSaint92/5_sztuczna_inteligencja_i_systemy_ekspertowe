#include "Board.h"
#include <vector>
#include <algorithm> //random_shuffle
#include <sstream> //toString()
#include <string> //toString()
#include <queue> 
#include <map>
#include <iostream>

Transformer* Board::transformer = NULL;

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
	if (rows*cols > 16 || rows*cols <= 0) throw std::invalid_argument("rows*cols must be in range (1...16)");
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
	this->rows = rows;
	this->cols = cols;
	this->values = values;
}

Board::Board(int rows, int cols, char justToRecognize)
{
	if (rows*cols > 16 || rows*cols <= 0) throw std::invalid_argument("rows*cols must be in range (1...16)");
	this->rows = rows;
	this->cols = cols;
}

uint64_t Board::transformToState()
{
	if( transformer == NULL ) throw std::domain_error("Transformer is not defined!");
	return this->transformer->getState(this->values);
}

void Board::getFromState(uint64_t state)
{
	if (transformer == NULL) throw std::domain_error("Transformer is not defined!");
	this->values = this->transformer->getVector(this->rows*this->cols, state);
}

std::string Board::toString()
{
	std::ostringstream oss;

	if (!this->values.empty())
	{
		size_t size = this->values.size();
		
		for (int i = 0; i < size; i++) {
			oss << this->values[i] << "\t";
			if ((i+1)%this->cols == 0) oss << "\n";
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
	if (zeroPosition == -1) throw std::domain_error("Board doesn't have 0 element?!");

	if (moveDirection == 'L') {
		//We can't left if 0 element is in first column
		if (!(zeroPosition%rows)) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition-1]);
	}
	else if (moveDirection == 'P') {
		//We can't right if 0 element is in last column
		if (!((zeroPosition+1)%rows)) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition + 1]);
	}
	else if (moveDirection == 'G') {
		//We can't up if 0 element is in first row
		if (zeroPosition<this->cols) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition - this->cols]);
	}
	else if (moveDirection == 'D') {
		//We can't down if 0 element is in last row
		if (zeroPosition>(this->cols*this->rows-this->rows-1)) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition + this->cols]);
	}
	else return false;
	return true;
}

uint64_t Board::getSolvedState() {
	std::vector<int> solvedSeq;
	int size = this->rows*this->cols;
	for (int i = 1; i < size; i++) solvedSeq.push_back(i);
	solvedSeq.push_back(0);

	Board* solvedBoard = new Board(this->rows, this->cols, solvedSeq);
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

Result Board::solveWithBFS(std::string givenOrder) 
{
	Result result;

	//Getting order vector
	std::vector<char> order;
	bool randomOrder;
	getOrderInfo(givenOrder, randomOrder, order);

	uint64_t startState = this->transformToState();
	uint64_t endState = this->getSolvedState();

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

		//Remove from search elements, the element where it came from
		//I think it saves us some time
		char prevMove = visitedStates[currentState];

		std::string str(order.begin(), order.end());

		//Now get the board of currentstate
		Board currentStateBoard(this->rows, this->cols, (char)0);
		currentStateBoard.getFromState(currentState);
		currentStateBoard.getValues();

		for (int i = 0; i < 4; i++) {
			if (order[i] != oppositeMove(prevMove)) {
				Board nextStateBoard(this->rows, this->cols, currentStateBoard.getValues());
				if (nextStateBoard.moveFreeTile(order[i])) {

					//This if tries to add new state to map - will fail if it already exist
					uint64_t nextState = nextStateBoard.transformToState();
					if (visitedStates.insert(std::make_pair(nextState, order[i])).second)
					{
						//Sprawdzamy czy nie mozemy juz tego zakonczyc
						if (nextState == endState) {
							result.steps = 1;
							result.seqOfMoves += order[i];
							uint64_t previousState = currentState;
							char lastMove = visitedStates[previousState];
							while (lastMove != (char)0) {
								result.steps++;
								result.seqOfMoves += lastMove;

								//Getting previousState and lastMove
								Board previousStateBoard(this->rows, this->cols, (char)0);
								previousStateBoard.getFromState(previousState);
								previousStateBoard.moveFreeTile(oppositeMove(lastMove));
								previousState = previousStateBoard.transformToState();
								lastMove = visitedStates[previousState];
							}
							reverse(result.seqOfMoves.begin(), result.seqOfMoves.end());
							return result;
						}
						else bfsQueue.push(nextState);
					}
				}
			}
		}
	}

	//void bfs(vector< vector<int> > const &graph, char lStart, char lEnd) {
	//	int vStart = lStart - 'a';
	//	int vEnd = lEnd - 'a';
	//
	//	vector<int> prev(graph.size(), -1);
	//	vector<int> dist(graph.size(), -1);
	//
	//	queue<int> bfsQueue;
	//	bfsQueue.push(vStart);
	//	dist[vStart] = 0;
	//	prev[vStart] = vStart;
	//
	//	while (!bfsQueue.empty()) {
	//		int v = bfsQueue.front();
	//		bfsQueue.pop();
	//
	//		for (int i = 0; i < graph[v].size(); i++) {
	//			int u = graph[v][i];
	//			if (prev[u] == -1) {
	//				cerr << char('a' + v) << " -> " << char('a' + u) << '\n';
	//				bfsQueue.push(u);
	//				dist[u] = dist[v] + 1;
	//				prev[u] = v;
	//				/* if(u == vEnd) {
	//				return;
	//				} */
	//			}
	//		}
	//	}
	//
	//	for (int i = 0; i < graph.size(); i++) {
	//		cerr << char('a' + i) << ": ";
	//		cerr << "dist=" << dist[i] << ", ";
	//		cerr << "prev=" << (prev[i] == -1 ? '-' : char('a' + prev[i])) << ", ";
	//		cerr << '\n';
	//	}
	//
	//	// expample: generate and print path to the final state
	//	if (prev[vEnd] != -1) { // vEnd found
	//		vector<char> path;
	//		path.push_back('a' + vEnd);
	//		int v = vEnd;
	//		while (prev[v] != v) {
	//			v = prev[v];
	//			path.push_back('a' + v);
	//		}
	//		reverse(path.begin(), path.end());
	//		for (int i = 0; i < path.size(); i++) {
	//			if (i != 0) cout << " -> ";
	//			cout << path[i];
	//		}
	//		cout << '\n';
	//	}
	//
	//}

	return result;
}

Result Board::solveWithDFS(std::string order)
{
	Result result;


	return result;

}

Result Board::solveWithHeuristic()
{
	Result result;

	return result;
}


