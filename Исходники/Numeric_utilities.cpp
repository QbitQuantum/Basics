double unit_uniform_random_variable()
{
	double x;
	do {
		x = double(rand())/RAND_MAX;
		} while (x == 0.0 || x == 1.0);
	return x;
}