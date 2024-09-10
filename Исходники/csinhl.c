long double complex
csinhl(long double complex z)
{
	long double complex w;
	long double x, y;

	x = creall(z);
	y = cimagl(z);
	w = sinhl(x) * cosl(y) + (coshl(x) * sinl(y)) * I;
	return w;
}