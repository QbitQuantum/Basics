	double
mayr_kernel(double x, void * n) {
	return (pow(cos(x), *(double*)n));
}