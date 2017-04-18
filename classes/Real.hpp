class Real
{
private:
	int dim, pop_size, len;

	double* members = NULL;
	double* aptitude = NULL;
public:
	Real(int d, int ps, double lmin, double lmax) : dim(d), pop_size(ps){
		len = d * pop_size;
		members = new double[len];
		aptitude = new double[pop_size];

		for (int i = 0; i < len; ++i)
			members[i] = random(lmin, lmax);

		double* x;
		for (int i = 0; i < pop_size; ++i) {
			x = Real::getMember(i);
			Real::setApt(testFunction(x, dim, FUNC), i);
		}

	};

	Real(int d, int ps) : dim(d), pop_size(ps){
		len = d * pop_size;
		members = new double[len];
		aptitude = new double[pop_size];

	};

	Real() {
		members = NULL;
		aptitude = NULL;
	};

	double* getMember(int index){
		double* t = new double[dim];
		index *= dim;
		for (int i = 0; i < dim; ++i)
			t[i] = members[index + i ];

		return t;
	}

	void setApt(double val, int index){
		aptitude[index] = val;
	}

	void insert(double* element, int position) {
		position *= dim;
		for (int i = 0; i < dim; ++i) {
			members[position + i] = element[i];
		}

		setApt(testFunction(element, dim, FUNC), position / dim);

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
			cout << members[i] << ", ";
			if (i % dim == 0)
				cout << "\n------------------------\n";
		}
		cout << "\n================================\n";
	}

	void close(){
		delete[] members, aptitude;
	}
	
};