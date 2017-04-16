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
		Binary::init();
	};

	Binary() {
		members = NULL;
		aptitude = NULL;
	};

	void init(){
		for (int i = 0; i < len; ++i){
			members[i] = randint() % 2;
			// cout << members[i];
		}
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
		for (int i = 0; i < dim; ++i) 
			members[position + i] = element[i];
	}

	void setApt(double val, int index){
		aptitude[index] = val;
	}

	double* getAllApt (){
		return aptitude;
	}

	double getApt (int index){
		return aptitude[index];
	}

	int getMaxAptIndex(){
		return maxx(aptitude, pop_size);
	}

	int getMinAptIndex(){
		return minn(aptitude, pop_size);
	}

	void show(){
		cout << "================================\n";
		cout << "        P o p u l a t i o n\n";
		cout << "================================\n";
		for (int i = 0; i < len; ++i) {
			cout << members[i];
			if (i % dim == 0)
				cout << "\n------------------------\n";
		}
		cout << "\n================================\n";
	}

	void close(){
		delete[] members, aptitude;
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

	void init(int lmn, int lmx){
		lmin = lmn;
		lmax = lmx;

		if (representation == 0) {
			int L = (int) pow(10, accuracy);
			L = (int)(log2(L * (lmax - lmin))  + 0.7);
			len = L;

			// bits population
			bpopulation = Binary(dimension * L, pop_size);
			// bpopulation.show();

			// aux for fotness evaluation
			double* tmp = new double[dimension];
			bool* bin_tmp;

			for (int i = 0; i < pop_size; ++i){
				bin_tmp = bpopulation.getMember(i);
				gen2fen(tmp, bin_tmp, len, lmn, lmx, dimension, accuracy);
				bpopulation.setApt(testFunction(tmp, dimension, FUNC), i);
			}

			delete[] tmp;
			delete[] bin_tmp;
			
			return;
		}
	}

	bool* getBinaryElement(int index){
		return bpopulation.getMember(index);
	}

	double* getDoubleElement(){
		return NULL;
	}

	double getAptitude(int index){
		return bpopulation.getApt(index);
	}

	double* getAllApt(){
		return bpopulation.getAllApt();
	}

	int getLen(){
		return len;
	}

	int getDim(){
		return dimension;
	}

	int getPopSize(){
		return pop_size;
	}

	void show(int index){
		bool* number = new bool[len];
		bool* bin_vector = bpopulation.getMember(index);

		cout << "[" ;
		for (int i = 0; i < dimension; ++i){
			for (int j = 0, k = i * len; j < len; ++j){
				number[j] =  bin_vector[k + j];
			}
			cout << lmin + bin2double(number, len) / pow(10, accuracy) 
				 << ", ";
		}
		cout << "]"
			 << "\t f(x) = " << bpopulation.getApt(index) << endl;
		
		delete[] bin_vector, number;
	}

	int getMemberSize(){
		return dimension * len;
	}

	double getLmin(){
		return lmin;
	}

	double getLmax(){
		return lmax;
	}

	int getAcc(){
		return accuracy;
	}

	void replace(Binary children){
		// elitism
		int imin = bpopulation.getMinAptIndex();
		show(imin);
		bool* tmp = bpopulation.getMember(imin);
		bpopulation.insert(tmp, 0);
		bpopulation.setApt(bpopulation.getApt(imin), 0);

		delete[] tmp;

		// replace entire generation
		bool* c;
		for (int i = 1; i < pop_size; ++i) {
			c = children.getMember(i);
			bpopulation.insert(c, i);
			bpopulation.setApt(children.getApt(i), i);

			delete[] c;
		}

		children.close();

	}

	
};