long double complex
catanl(long double complex z)
{
	long double complex w;
	long double a, t, x, x2, y;

	x = creall(z);
	y = cimagl(z);

	if ((x == 0.0L) && (y > 1.0L))
		goto ovrf;

	x2 = x * x;
	a = 1.0L - x2 - (y * y);
	if (a == 0.0L)
		goto ovrf;

	t = atan2l(2.0L * x, a) * 0.5L;
	w = redupil(t);

	t = y - 1.0L;
	a = x2 + (t * t);
	if (a == 0.0L)
		goto ovrf;

	t = y + 1.0L;
	a = (x2 + (t * t)) / a;
	w = w + (0.25L * logl(a)) * I;
	return (w);

ovrf:
	/*mtherr( "catanl", OVERFLOW );*/
	w = LDBL_MAX + LDBL_MAX * I;
	return (w);
}