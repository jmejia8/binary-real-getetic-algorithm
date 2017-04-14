class Binary
{
private:
	int dim, pop_size, len;

	bool* members = NULL;
	double* aptitude = NULL;
public:
	Binary(int d, int ps) : dim(d), pop_size(ps){
		len = d * pop_size;
		members = new bool[len];
		aptitude = new double[pop_size];
	};

	~Binary(){
		if (members != NULL)
			delete[] members;
	};

	void init(){
		for (int i = 0; i < len; ++i)
			members[i] = randint() % 2;
	}

	double bin2double (bool* t){
		double v = 0.0;
		for (int i = 0; i < len; ++i) {
			if (not t[i]) continue;
			v += pow(2, len - i - 1);
		}

		return lmin + v / pow(10, accuracy);
	}

	bool* getMember(int index){
		bool* t = new bool[dim];
		index *= dim;
		for (int i = 0; i < dim; ++i)
			t[i] = members[index + i ];

		return t;
	}

	void insert(bool* element, int position) {
		position *= dim;
		for (int i = 0; i < dimension; ++i) 
			members[position + i] = element[i];
	}
	
};


class Population
{
private:
	// 0 binary, 1 = real.
	int representation;
	int pop_size;
	int dimension;
	Binary bpopulation;
	double* dpopulation = NULL;
	int accuracy;
	int len;
	double lmin, lmax;


public:
	Population(int repr, int size, int d, int acc) :
		representation(repr),
		pop_size (size), 
		dimension (d), 
		accuracy (acc) 
	{
		switch (repr){
			case 1:
				dpopulation = new double[d * size];
				break;
			default:
				break;
		}
	} ;

	~Population() {
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

	void gen2fen(double* x, bool* t){
		for (int i = 0; i < dimension; ++i){
			dpopulation[i] = bin2double(t, i);
		}
	}

	void init(int lmn, int lmx){
		lmin = lmn;
		lmax = lmx;

		if (representation == 0) {
			int L = (int) pow(10, accuracy);
			L = (int)(log2(L * (lmax - lmin))  + 0.7);
			len = L;

			bpopulation = Binary(dimension * L, pop_size);
			double* tmp = new double[dimension];

			for (int i = 0; i < pop_size; ++i){
				gen2fen(tmp, bpopulation.getMember(i));
				aptitude[i] = testFunction(tmp, dimension, 0);
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

	double* getAllApt(){
		return aptitude;
	}

	int getLen(){
		return len;
	}

	
};