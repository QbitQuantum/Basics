int main(int argc, char *argv[]) {
	if (3 <= argc && argc <= 4) {
		int nbytes= atoi(argv[2]);
		if (nbytes <= 0) {
			cerr << "bitcount: nbytes must be greater than zero\n";
			return EXIT_FAILURE;
		}
		int nthreads= (argc > 3) ? atoi(argv[3]) : 0;
		if (nthreads < 0) {
			cerr << "bitcount: nthreads must not be less than zero\n";
			return EXIT_FAILURE;
		}
		
		vector<unsigned char> space(atol(argv[2]));
		fillMemory(space);

		if (strcmp(argv[1], "shift") == 0) {
			if (nthreads == 0)
				cout << bitCount(&space[0], space.size(), bits_shift);
			else
				cout << bitCount_mt(&space[0], space.size(), nthreads, bits_shift);
			cout << endl;
			return EXIT_SUCCESS;
		}
		if (strcmp(argv[1], "lookup") == 0) {
			if (nthreads == 0)
				cout << bitCount(&space[0], space.size(), bits_lookup);
			else
				cout << bitCount_mt(&space[0], space.size(), nthreads, bits_lookup);
			cout << endl;
			return EXIT_SUCCESS;
		}
	}
	cerr << "Usage: bitcount [shift|lookup] nbytes [nthreads]\n";
	return EXIT_FAILURE;
}