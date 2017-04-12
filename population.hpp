class Population
{
private:
	// 0 binary, 1 = real.
	int representation = 0;
	int pop_size;
	int dimension;
	bool* bpopulation = NULL;
	double* dpopulation = NULL;
	double* aptitude;
	int accuracy;
	int len;
	double lmin, lmax;

	double bin2double (int index){
		double v = 0.0;
		for (int i = 0; i < len; ++i) {
			if (not bpopulation[i + index])
				continue;
			v += pow(2, len - i - 1);
		}

		return lmin + v / pow(10, accuracy);
	}

public:
	Population(int repr, int size, int d, int acc) :
		representation(repr),
		pop_size (size), 
		dimension (d), 
		accuracy (acc) 
	{
		aptitude = new double[size];
		switch (repr){
			case 1:
				dpopulation = new double[d * size];
				break;
			default:
				break;
		}
	} ;

	~Population() {
		if (bpopulation != NULL)
			delete[] bpopulation;
		if (dpopulation != NULL)
			delete[] dpopulation;
	};

	void show(){
		for (int i = 0; i < pop_size * len * dimension; ++i) {
			cout << bpopulation[i];
			if (i % len == 0)
				cout << " ";

			if (i % (len * dimension) == 0)
				cout << endl;
		}

	}

	void gen2fen(double* x, int index){
		for (int i = 0; i < dimension; ++i){
			dpopulation[i] = bin2double(index*len*dimension + i*len );
		}
	}

	void init(int lmn, int lmx){
		lmin = lmn;
		lmax = lmx;

		if (representation == 0) {
			int L = (int) pow(10, accuracy);
			L = (int)(log2(L * (lmax - lmin))  + 0.7);
			len = L;
			bpopulation = new bool[pop_size * L * dimension];
			dpopulation = new double[dimension];


			for (int i = 0; i < pop_size * L * dimension; ++i)
				bpopulation[i] = randint() % 2;

			for (int i = 0; i < pop_size; ++i){
				gen2fen(dpopulation, i);
				aptitude[i] = testFunction(dpopulation, dimension, 0);
			}
			
			return;
		}
	}

	bool* getBinaryElement(int index){
		bool* item = new bool[len * dimension];
		index *= len * dimension;

		for (int i = 0; i < len * dimension; ++i)
			item[i] = bpopulation[index + i];

		return item;
	}

	double* getDoubleElement(){
		return NULL;
	}

	double getAptitude(int index){
		return aptitude[index];
	}

	int getLen(){
		return len;
	}
	
};