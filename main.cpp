#include <iostream>
#include <cmath>
#include <ctime>
#include <stdlib.h>

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
#include "operators.hpp"

int main(int argc, char const *argv[])
{
	int pop_size 	= 20,
		dim 	 	= 10,
		maxEvals	= 100000;
	double crossP	= 0.9,
		   mutationP= 0.1;

	Population population = Population(REPR, pop_size, dim, 3);
	population.init(-10, 10);

	int* parents = new int[pop_size];
	for (int t = 0; t < 1 and evals < maxEvals; ++t){
		if (REPR == 0) {
			stocUnivSelect(population.getAllApt(), parents, pop_size);
			TwoPointCrossover(population, parents);
		}

	}


	return 0;
}