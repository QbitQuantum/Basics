int main(void) {
	double r1 = 0.1 * 10 - 1;
	double r2 = fma(0.1, 10, -1);
	print_bin_double(r1);
	print_bin_double(r2);
	long int i;
//	printf("off;reg;fma;expect\n");
//	for(i = 1; i < 1L << 62; i *= 10) {
//		printf("%ld;", i);
//		printf("%.15G;", (i * M_PI + M_PI_2) - (i * M_PI - M_PI_2) - M_PI);
//		printf("%.15G;%.15G\n", (1* fma(i, M_PI, +M_PI_2) - fma(i, M_PI, -M_PI_2)) - M_PI, M_PI);
//	}
	double shift = M_PI*000;
	double l = shift - 1e-20;
	double r = shift + 1e-20;
	long int n = 5;
	double dx = (r - l) / n;
	long double res = 0;
	printf("dx=%.15G\nl, r, v\n", dx);
	for(i = 0; i < n; i++) {
		double tl = l + dx * i;
		double tr = l + dx * (i + 1);
//		printf("%.15G %.15G %.15G\n", tl, tr, (sin(tl) + sin(tr)) / 2);
		res += (sin(tl) + sin(tr));
	}
	res *= dx / 2;
//	printf("%.15G\n", (double)res);
//	printf("%.15G\n%.15G\n", (shift + M_PI) - shift, M_PI);
//	printf("%.15G\n", -cos(r)+cos(l));
//	printf("%.15G", sin(M_PI_2*100001));
	long int offset = 1e9;
	printf("%.15G\n%.15G", sin((M_PI + offset) - offset), sin(M_PI));
	return 0;
}