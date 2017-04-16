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
#define FUNC 1
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
	double crossP	= 1.0,
		   mutationP= 0.3;

	Population population(REPR, pop_size, dim, ACCURACY);
	population.init(-5, 5);
	int* parents = new int[pop_size];

	if (REPR == 0) {
		TwoPointCrossover* cross;
		for (int t = 0; t < maxIters and evals < maxEvals; ++t){
			cout << "====================================" << endl;
			cout << ">>>>> Gen " << t << "\t Evals.: " << evals << endl;

			stocUnivSelect(population.getAllApt(), parents, pop_size);
			cross = new TwoPointCrossover(population, parents, crossP, mutationP);
			population.replace(cross->getChildren());
			delete cross;
		}
		return 0;
	}


	for (int t = 0; t < maxIters and evals < maxEvals; ++t){
		cout << "====================================" << endl;
		cout << ">>>>> Gen " << t << "\t Evals.: " << evals << endl;
		deterBinTournament(population.getAllApt(), parents, pop_size);
		

	}

	return 0;
}