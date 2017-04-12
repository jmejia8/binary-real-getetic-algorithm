class stochasticUniversal
{
public:
	stochasticUniversal(double* aptitude, int pop_size) {
		double expectVal = mean(aptitude, pop_size);
		double ptr = random(0, 1), sum = 0;

		for (int i = 0; i < pop_size; ++i) {
			for (sum += aptitude[i] / expectVal ; sum > ptr; ++ptr ) {
				// pass
			}
		}
	};
	~stochasticUniversal();
	
};

class TwoPointCrossover
{
public:
	TwoPointCrossover(int pop_size){
		int* list = new int[pop_size];
	};
	
};