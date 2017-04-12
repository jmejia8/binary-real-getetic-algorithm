#include <iostream>
#include <cmath>
#ifndef REPR
#define REPR 0
#endif

#ifndef ACCURACY
// 3 digits
#define ACCURACY 3 
#endif

#include "functions.hpp"
#include "tools.hpp"
#include "population.hpp"

int main(int argc, char const *argv[])
{
	Population population = Population(REPR, 10, 10, 3);
	population.init(-10, 10);

	return 0;
}