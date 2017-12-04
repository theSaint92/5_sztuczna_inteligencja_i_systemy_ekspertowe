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
	cout << UINTMAX_MAX;

	for (int i = 0; i < 21; i++) {
		cout << i << "! = " << Factorial::getInstance().get(i) << endl;
	}
	
	std::srand(unsigned(std::time(0)));
	Board* board = new Board(4,2);
	cout << board->toString() << endl;
	int x = 0x11;
	cout << x << endl;
	return 0;


}

