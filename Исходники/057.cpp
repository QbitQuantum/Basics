int problem057(void)
{
	long double numer = 3, denom = 2; // 分子, 分母 

	int count = 0;
	for (int i = 1; i < 1000; ++i) {
		const long double tmp_numer = numer + denom * 2;
		const long double tmp_denom = numer + denom;
		numer = tmp_numer;
		denom = tmp_denom;
		if ((int)log10l(numer)+1 > (int)log10l(denom)+1)
			++count;
	}
	return count;
}