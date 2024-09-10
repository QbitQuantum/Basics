double maths_rand(double a, double b)
{
	return (b - a) * ((double)rand() / RAND_MAX) + a;
}