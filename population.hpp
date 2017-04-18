#include "classes/Binary.hpp"
#include "classes/Real.hpp"

class Population
{
private:
	// 0 binary, 1 = real.
	int representation;
	int pop_size;
	int dimension;
	Binary binaryPop;
	Real realPop;
	int accuracy;
	int len;
	double lmin, lmax;


public:
	Population(int repr, int size, int d, int acc) :
		representation(repr),
		pop_size (size), 
		dimension (d), 
		accuracy (acc) 
	{} ;

	void init(int lmn, int lmx){
		lmin = lmn;
		lmax = lmx;

		if (representation == 0) {
			int L = (int) pow(10, accuracy);
			L = (int)(log2(L * (lmax - lmin))  + 0.7);
			len = L;

			// bits population
			binaryPop = Binary(dimension * L, pop_size);
			// binaryPop.show();

			// aux for fotness evaluation
			double* tmp = new double[dimension];
			bool* bin_tmp;

			for (int i = 0; i < pop_size; ++i){
				bin_tmp = binaryPop.getMember(i);
				gen2fen(tmp, bin_tmp, len, lmn, lmx, dimension, accuracy);
				binaryPop.setApt(testFunction(tmp, dimension, FUNC), i);
			}

			delete[] tmp;
			delete[] bin_tmp;
			
			return;
		}

		if (representation == 1) {
			realPop = Real(dimension, pop_size, lmin, lmax);
		}
	}

	bool* getBinaryElement(int index){
		return binaryPop.getMember(index);
	}

	double* getDoubleElement(int index){
		return realPop.getMember(index);
	}

	double getAptitude(int index){
		return binaryPop.getApt(index);
	}

	double* getAllApt(){
		if (representation == 0)
			return binaryPop.getAllApt();
		return realPop.getAllApt();
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
		bool* bin_vector = binaryPop.getMember(index);

		cout << "[" ;
		for (int i = 0; i < dimension; ++i){
			for (int j = 0, k = i * len; j < len; ++j){
				number[j] =  bin_vector[k + j];
			}
			cout << lmin + bin2double(number, len) / pow(10, accuracy) 
				 << ", ";
		}
		cout << "]"
			 << "\t f(x) = " << binaryPop.getApt(index) << endl;
		
		delete[] bin_vector, number;
	}

	void showDouble(int index){
		double* tmp = realPop.getMember(index);
		for (int i = 0; i < dimension; ++i) {
			cout << tmp[i] << ", ";
		}

		delete[] tmp;

		cout << "\t f(x) = " << realPop.getApt(index) << "\t" << mean(realPop.getAllApt(), pop_size) << endl;

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
		int imin = binaryPop.getMinAptIndex();
		show(imin);
		bool* tmp = binaryPop.getMember(imin);
		binaryPop.insert(tmp, 0);
		binaryPop.setApt(binaryPop.getApt(imin), 0);

		delete[] tmp;

		// replace entire generation
		bool* c;
		for (int i = 1; i < pop_size; ++i) {
			c = children.getMember(i);
			binaryPop.insert(c, i);
			binaryPop.setApt(children.getApt(i), i);

			delete[] c;
		}

		children.close();

	}

	void replaceDouble(Real children){
		// elitism
		int imin = realPop.getMinAptIndex();
		showDouble(imin);
		double* c = realPop.getMember(imin);
		realPop.insert(c, 0);
		realPop.setApt(realPop.getApt(imin), 0);


		delete[] c;

		// replace entire generation
		for (int i = 1; i < pop_size; ++i) {
			c = children.getMember(i);
			realPop.insert(c, i);
			realPop.setApt(children.getApt(i), i);

			delete[] c;
		}
		children.close();
	}

	
};