int main(int argc, char *argv[])
{
	double x = 5.5, y = 3;
	double a, b;
	printf("erfc(%lg): %lg, %lg\n", x, erfc(x), kf_erfc(x));
	printf("upper-gamma(%lg,%lg): %lg\n", x, y, kf_gammaq(y, x)*tgamma(y));
	a = 2; b = 2; x = 0.5;
	printf("incomplete-beta(%lg,%lg,%lg): %lg\n", a, b, x, kf_betai(a, b, x) / exp(kf_lgamma(a+b) - kf_lgamma(a) - kf_lgamma(b)));
	return 0;
}