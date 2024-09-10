long long sum_of_digits(long long n) {
    long long sum = 0;
    while(n) {
	lldiv_t d = lldiv(n,10ull);
	sum += d.rem;
	n = d.quot;
    }
    return sum;
}