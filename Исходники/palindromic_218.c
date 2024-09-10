	unsigned long long reverse2(unsigned long long a) {
		unsigned long long aux;
		unsigned long long rev = 0;
		while(a>0){
			lldiv_t longdiv = lldiv(a, 10);
			rev = rev*10 + longdiv.rem;
			a = longdiv.quot;
		}
		return rev;
	}