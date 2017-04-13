#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

int evals = 0;

double sphere(double* x, int dim) {
	double s = 0.0;

	for (int i = 0; i < dim; ++i)
		s += x[i] * x[i];

	return s;
}

double multimodal(double* x, int dim){
	double s = 10 * dim;
	for (int i = 0; i < dim; ++i)
		s += x[i] * x[i] - 10 * cos(2 * PI * x[i]);

	return s;
}

double testFunction(double* x, int dim, int func){
	if (func == 0)
		return sphere(x, dim);
	if (func == 1)
		return multimodal(x, dim);
}