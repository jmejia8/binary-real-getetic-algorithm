using namespace std;

int seed = 7; 
double random(double lmin, double lmax){
	srand(time(NULL) + seed );
	seed = rand();
	double r = (double) seed / (double) RAND_MAX;
	return  lmin + r * ( lmax - lmin );
}

int randint(){
	srand(time(NULL) + seed );
	seed = rand();
	return seed;
}

// double abs(double x){
// 	if (x < 0)
// 		return -x;
// 	return x;
// }

int maxx(double* list, int size){
	int m = 0;
	for (int i = 1; i < size; ++i) {
		if (list[i] > list[m] ) {
			m = i;
		}
	}

	return m;
}

int minn(double* list, int size){
	int m = 0;
	for (int i = 1; i < size; ++i) {
		if (list[i] < list[m] ) {
			m = i;
		}
	}

	return m;
}

double mean(double* data, int size){
	double m = 0.0;
	for (int i = 0; i < size; ++i) m += data[i];

	return m / size;
}

double bin2double (bool* number, int size){
		double v = 0.0;
		for (int i = 0; i < size; ++i) {
			if (not number[i]) continue;
			v += pow(2, size - i - 1);
		}

		return v;
}

void gen2fen(double* x,
			 bool* bin_vector,
			 int bin_len,
			 int lmin,
			 int lmax,
			 int dimension,
			 double accuracy)
{
	bool* number = new bool[bin_len];
	// cout << "ZZZZ  " << bin_len << endl;
	for (int i = 0; i < dimension; ++i){
		for (int j = 0, k = i * bin_len; j < bin_len; ++j){
			number[j] =  bin_vector[k + j];
			// cout << number[j];
		}
		// cout << "\n<<<<<<\n";
		x[i] = lmin + bin2double(number, bin_len) / pow(10, accuracy);
		// cout << x[i] << ", ";
	}

	// cout << endl;
}

void printVector(bool* v, int size, int point1, int point2){
	for (int i = 0; i < size; ++i) {
		if (i == point1 or i == point2)
			cout << "|";
		cout << v[i];
	}

	cout << "\n===============================" << endl ;
}