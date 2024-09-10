int main(int argc, char* argv[]) {
	INT n = (argc == 2) ? atol(argv[1]) : 0;
	for (INT i = 1; i <= n; ++i) 
		printf ("%llu : %llu\n", i, orbita(i));
	return 0;
}