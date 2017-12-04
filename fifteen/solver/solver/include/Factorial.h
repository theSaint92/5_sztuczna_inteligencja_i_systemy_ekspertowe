#include <vector>

//Singleton

class Factorial
{
	std::vector<uint64_t> values;

public:

	static Factorial& getInstance();
	Factorial();
	uint64_t get(int number);

private:
	Factorial(Factorial const&);      // Don't Implement.
	void operator=(Factorial const&); // Don't Implement.
};

