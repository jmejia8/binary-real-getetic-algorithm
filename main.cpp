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

#ifndef FUNC
#define FUNC 0
#endif

#include "functions.hpp"
#include "tools.hpp"
#include "population.hpp"
#include "operators.hpp"

int main(int argc, char const *argv[])
{
	int pop_size 	= 10,
		dim 	 	= 10,
		maxEvals	= 100000,
		maxIters   = 15000;
	double crossP	= 0.9,
		   mutationP= 0.1;

	Population population(REPR, pop_size, dim, 3);
	population.init(-10, 10);
	// population.show();

	int* parents = new int[pop_size];
	for (int t = 0; t < maxIters and evals < maxEvals; ++t){
		if (REPR == 0) {
			// population.show();
			// cout << "perro" << endl;
			stocUnivSelect(population.getAllApt(), parents, pop_size);
			// cout << "gato" << endl;
			TwoPointCrossover cross(population, parents, crossP);
			// cout << "rata" << endl;
			population.replace(cross.getChildren());
			// cout << "toro" << endl;
		}

	}


	return 0;
}