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
	int pop_size 	= 100,
		dim 	 	= 10,
		maxEvals	= 100000,
		maxIters   = 1000;
	double crossP	= 0.7,
		   mutationP= 0.5;

	Population population(REPR, pop_size, dim, 3);
	population.init(-10, 10);
	TwoPointCrossover cross;

	int* parents = new int[pop_size];
	for (int t = 0; t < maxIters and evals < maxEvals; ++t){
		cout << "====================================" << endl;
		cout << ">>>>> Gen " << t << "\t Evals.: " << evals << endl;
		if (REPR == 0) {
			stocUnivSelect(population.getAllApt(), parents, pop_size);
			cross = TwoPointCrossover(population, parents, crossP, mutationP);
			population.replace(cross.getChildren());
		}

	}


	return 0;
}