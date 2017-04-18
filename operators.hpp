void stocUnivSelect(double* aptitude, int* members, int size) {
		int k = 0, j;
		double ma = 1.001 * (aptitude[maxx(aptitude, size)]);

		double expectVal = ma - mean(aptitude, size);

		double ptr = random(0, 1), sum = 0;

		for (int i = 0; i < size; ++i) {
			j = ma - aptitude[i] ;
			for (sum += j / expectVal ; sum > ptr; ++ptr ) {
				members[k++] = i;
			}
		}

		// shuffle array
		for (int i = 0; i < size; ++i) {
			j = randint() % size;
			k = members[j];
			members[j] = members[i];
			members[i] = k;
		}
}

void deterBinTournament(double* aptitude, int* members, int size){
	int counter = 0, i, j;
	while(counter <= size) {
	    i = randint() % (size - 1);
	    j = randint() % (size - 1);

	    if (aptitude[i] < aptitude[j])
			members[counter++] = i;
	    else
			members[counter++] = j;
	}
}

void simpleMutation(bool* c1, int size, double mutationP){
	if (random(0, 1) <= mutationP) {
		int k = randint() % (size - 1);
		c1[k] = not c1[k];
	}
}

void uniformMutation(double* c1, int size, double mutationP, double a, double b){
	if (random(0, 1) <= mutationP) {
		int k = randint() % (size - 1);
		c1[k] = random(a, b);
	}
}

class TwoPointCrossover
{
private:
	Binary children;
	double prob, prob_mut;
	int* parents;
	int pop_size;
	int member_size;

	void mixing(bool* p1, bool* p2, int i){
		bool* c1 = new bool[member_size],
			 *c2 = new bool[member_size];
		int point1 = 1 + randint() % (member_size - 3),
			point2 = point1 + randint() % (member_size - point1 - 2);

		for (int i = 0; i < member_size; ++i) {
			if (i < point1 or i > point2) {
				c1[i] = p1[i];
				c2[i] = p2[i];
				continue;
			}

			c1[i] = p2[i];
			c2[i] = p1[i];
		}

		simpleMutation(c1, member_size, prob);
		simpleMutation(c2, member_size, prob);


		children.insert(c1, 2*i);
		children.insert(c2, 2*i + 1);
		delete[] c1, c2;
	}

	void crossover(Population population){
		int len = pop_size / 2, j, k;
		bool *p1, *p2;
		double* x = new double[population.getDim()];

		for (int i = 0; i < len; ++i) {
			j = parents[2*i];
			k = parents[2*i + 1];
			p1 = population.getBinaryElement(j);
			p2 = population.getBinaryElement(k);
			
			if (random(0, 1) > prob){
				simpleMutation(p1, member_size, prob);
				simpleMutation(p2, member_size, prob);

				children.insert(p1, 2*i);
				children.insert(p2, 2*i + 1);
			}else{
				mixing(p1, p2, i);
			}

			delete[] p1, p2;

			p1 = children.getMember(2*i);
			p2 = children.getMember(2*i + 1);
			gen2fen(x, p1, population.getLen(),
						   population.getLmin(),
						   population.getLmax(),
						   population.getDim(),
						   population.getAcc());
			children.setApt(testFunction(x, population.getDim(), FUNC) , 2*i);

			gen2fen(x, p2, population.getLen(),
						   population.getLmin(),
						   population.getLmax(),
						   population.getDim(),
						   population.getAcc());
			children.setApt(testFunction(x, population.getDim(), FUNC), 2*i + 1);
		
			delete[] p1, p2;

		}
		
	delete[] x;			
}

public:
	TwoPointCrossover(Population population, int* parents, double prob, double mutationP):
		parents(parents), prob(prob), prob_mut(mutationP)
	{
		pop_size = population.getPopSize();
		member_size = population.getMemberSize();
		children = Binary(member_size, pop_size);

		crossover(population);
	};

	TwoPointCrossover() {};


	Binary getChildren(){
		return children;
	}
	
};

class SBX
{
	int* parents, pop_size, dim;
	double crossP, mutationP, lmin, lmax;
	Real children;

	double beta(double u, double eta){
		if (u <= 0.5)
			return pow(2 * u, 1.0 / (eta - 1));

		return pow(2 - 2 * u, -1.0 / (eta - 1));
	}

	void mixing(double* p1, double* p2, double* c1, double* c2){
		double u, b;
		for (int i = 0; i < dim; ++i) {
			u = random(0, 1);
			b = beta(u, 5);
			c1[i] = 0.5 * (p1[i] + p2[i] - b * (p2[i] - p1[i]));
			c2[i] = 0.5 * (p1[i] + p2[i] + b * (p2[i] - p1[i]));
		}

		uniformMutation(c1, mutationP, dim, lmin, lmax);
	}

	void crossover(Population population){
		int n = pop_size / 2;
		double* p1, *p2,
			*c1 = new double[dim],
			*c2 = new double[dim];
		
		for (int i = 0; i < n; ++i) {
			p1 = population.getDoubleElement(parents[2*i]);
			p2 = population.getDoubleElement(parents[2*i + 1]);

			// cout << "cross 1" << endl;
			if (random(0, 1) > crossP) {
				children.insert(p1, 2*i);
				children.insert(p2, 2*i + 1);
			}else{
				// cout << "cross 2" << endl;
				mixing(p1, p2, c1, c2);
				// cout << "cross 3" << endl;
				children.insert(c1, 2*i);
				// cout << "cross 4 >>>> " << 2*i + 1 << endl;
				children.insert(c2, 2*i + 1);
				// cout << "cross 5" << endl;
			}
			
			delete[] p1, p2;
		}

		delete[] c1, c2;
	}
public:
	SBX(Population population, int* p, double c, double m) :
		parents(p), crossP(c), mutationP(m)
	{
		dim = population.getDim();
		pop_size = population.getPopSize();
		lmin = population.getLmin();
		lmax = population.getLmax();
		children = Real(dim, pop_size);
		// cout << "sbx" << endl;
		SBX::crossover(population);
		// cout << "sbx 1" << endl;
	};

	Real getChildren(){
		return children;
	}

	
};