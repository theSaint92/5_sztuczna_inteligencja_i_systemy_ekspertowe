// fifteen.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "Board.h"
#include "Factorial.h"

using namespace std;


int main(int argc, char* argv[])
{
	//cout << (hex) << UINTMAX_MAX << " " << 0xFFFFFFFFFFFFFFFF << endl;

	
	//for (int i = 0; i < 17; i++) {
	//	cout << i << "! = " << Factorial::getInstance().get(i) << endl;
	//}

	HexaTransformer hex;
	FactorialTransformer fac;
	Board::changeTransformer(hex);
	
	std::srand(unsigned(std::time(0)));
	Board* board = new Board();
	cout << "BOARD:\n" << board->toString() << endl;
	uint64_t transformed = board->transformToState();
	cout << "State form: " << transformed << endl;
	board->getFromState(transformed);
	cout << "After takeing from transformed form:\n" << board->toString() << endl;
	int x = 0x11;
	cout << x << endl;

	clock_t begin = clock();
	for (int i = 1; i < 10000; i++) {
		board = new Board(4, 4);
		uint64_t transformed = board->transformToState();
		board->getFromState(transformed);
	}
	clock_t end = clock();
	std::cout << "Wykonano w " << end - begin << " clocks\n";

	Board::changeTransformer(fac);
	begin = clock();
	for (int i = 1; i < 10000; i++) {
		board = new Board(4, 4);
		uint64_t transformed = board->transformToState();
		board->getFromState(transformed);
	}
	end = clock();
	std::cout << "Wykonano w " << end - begin << " clocks\n";

	//for (int i = 1; i < 20; i++) {
	//	board = new Board(3, 3);
	//	cout << "BOARD:\n" << board->toString() << endl;
	//	cout << "Logical result: " << board->moveFreeTile('D') << endl;
	//	cout << "BOARD AFTER:\n" << (dec) << board->toString() << endl;
	//	cout << "//////////////////////////////\n";
	//}








	return 0;



}

