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