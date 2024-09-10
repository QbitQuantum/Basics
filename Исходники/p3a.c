double solve()
{
	double c, s;
	int i, j, k, r;

	r = n - 1;
	k = r >> 1;

	if (r & 1) {
		c = exp(lgamma(r + 1) - lgamma(k + 1) - lgamma(r - k + 1) - r * l2);
		for (s = 0., i = k, j = k + 1; i >= 0; i--, j++) {
			s += c * (a[i] + a[j]);
			c *= i / (double)(r - i + 1.);
		}
	} else {
		c = exp(lgamma(r + 1) - 2 * lgamma(k + 1) - r * l2);
		s = c * a[k];
		c *= k / (double)(r - k + 1.);
		for (i = k - 1, j = k + 1; i >= 0; i--, j++) {
			s += c * (a[i] + a[j]);
			c *= i / (double)(r - i + 1.);
		}
	}

	return s;
}