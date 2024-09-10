long double complex
cexpl(long double complex z)
{
	long double complex w;
	long double r;

	r = expl(creall(z));
	w = r * cosl(cimagl(z)) + (r * sinl(cimagl(z))) * I;
	return (w);
}