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