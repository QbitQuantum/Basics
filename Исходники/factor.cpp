bool isPrimeByFactoring(unsigned long long int n) {
	lldiv_t junk = lldiv(1, 1);
	unsigned long long int i = 2;
	while (true) {
		if (i > ceil(sqrt(n))) {
			std::cout << n << " is prime" << std::endl;
			return true;
		}

		junk = lldiv(n, i);
		if (junk.rem == 0) {
			//std::cout << n << " is not prime" << std::endl;
			return false;
			//std::cout << n << "/" << i << "=" << junk.quot << " r" << junk.rem << " (" << i << ")" << std::endl;
			//n = junk.quot;
			//std::cout << i << "*";
			//i = 1;
		}
		i++;
	}
}