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

double abs(double x){
	if (x < 0)
		return -x;
	return x;
}

int maxx(double* list, int size){
	int m = 0;
	for (int i = 1; i < size; ++i) {
		if (list[i] > list[m] ) {
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
