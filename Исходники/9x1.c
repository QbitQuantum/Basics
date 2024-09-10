int
main ()
{
	int n;
	double *x, *f, *g;
	printf ("\nEntreu les coordenades\n");
	x = HGVM (&n);
	printf ("\nEntreu els valors de la funcio\n");
	f = GVM (n);
	printf ("\nEntreu les derivades\n");
	g = GVM (n);

/* Obte el polinomi desitjat */
	difdivherm (n, &x, &f, &g);

/* Dibuixa el polinomi */
	writeFile (2 * n, 1e-2, -2, 2, x, f);

	FV (x, n);
	FV (f, n);
	return 0;
}