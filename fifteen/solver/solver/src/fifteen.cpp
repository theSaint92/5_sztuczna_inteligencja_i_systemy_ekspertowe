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
	cout << (hex) << UINTMAX_MAX << " " << 0xFFFFFFFFFFFFFFFF << endl;


	for (int i = 0; i < 17; i++) {
		cout << i << "! = " << Factorial::getInstance().get(i) << endl;
	}
	
	std::srand(unsigned(std::time(0)));
	Board* board = new Board(4,3);
	cout << "BOARD:\n" << board->toString() << endl;
	board->changeTransformer("factorial");
	uint64_t transformed = board->transformToState();
	cout << "State form: " << board->transformToState() << endl;
	board->getFromState(transformed);
	cout << "After takeing from transformed form:\n" << board->toString() << endl;
	int x = 0x11;
	cout << x << endl;
	return 0;


}

