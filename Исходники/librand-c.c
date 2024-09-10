static long double P(long double mu, long double sigma, long double x)
{
	long double tmp = 1 / (sigma * sqrtl(2.0 * M_PIl));
	long double up = -powl(x-mu, 2) / (2 * powl(sigma, 2));
	tmp *= expl(up);
	return tmp;
}