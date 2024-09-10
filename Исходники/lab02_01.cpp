/*
 * Desenarea graficului in zona din stanga a ecranului.
 */
void initialize_left_area()
{
	set(2);

	// desenarea graficului
	setcolor(LIGHTBLUE);
	moveto(x[0], y[0]);

	for (int i = 1; i <= REF; i++)
		lineto(x[i], y[i]);

	setcolor(LIGHTGRAY);
	// desenarea axelor daca sunt in figura
	if ((minf <= 0) && (maxf >= 0))
	{
		// axa Ox
		line(0, virtualY(f(zerof())), 316, virtualY(f(zerof())));
	}
	if ((a <= 0) && (b >= 0))
	{
		// axa Oy
		line(virtualX(0), 0, virtualX(0), 316);
	}

	setwritemode(XOR_PUT);
	setcolor(GREEN);
	rectangle(x1, y1, x2, y2);
}