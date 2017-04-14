void stocUnivSelect(double* aptitude, int* members, int size) {
		int k = 0, j;
		double ma = 2 * (aptitude[maxx(aptitude, size)]);

		double expectVal = ma - mean(aptitude, size);

		double ptr = random(0, 1), sum = 0;

		for (int i = 0; i < size; ++i) {
			j = ma - aptitude[i] ;
			for (sum += j / expectVal ; sum > ptr; ++ptr ) {
				members[k++] = i;
			}
		}

		// shuffle array
		for (int i = 0; i < size; ++i) {
			j = randint() % size;
			k = members[j];
			members[j] = members[i];
			members[i] = k;
		}

		// for (int i = 0; i < size; ++i) {
		// 	cout << members[i] << "\t" << aptitude[i]
		// 		 << "\t \t" << (ma-aptitude[i]) / expectVal << endl;
		// }
	
}

class TwoPointCrossover
{
private:
	Population children;
public:
	TwoPointCrossover(Population population, int* parents, double prob){
		
	};
	
};