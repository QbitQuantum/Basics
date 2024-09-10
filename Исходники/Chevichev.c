int main (void)
{
	double *x, *f;
	int i;
	x = aCy (n, -1., 1. );

	SV (n, x);
	f = DIV (n);
	for (i = 0; i < n; i++)
		f[i] = fun (x[i]);
	difdiv (n, x, f); /* generat el polinomi */
	writeFile (n, 0.001, -1, 1, x, f);
	return 0;
}