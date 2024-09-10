long double complex
clogl(long double complex z)
{
	long double complex w;
	long double p, rr;

	rr = cabsl(z);
	p = logl(rr);
	rr = atan2l(cimagl(z), creall(z));
	w = p + rr * I;
	return w;
}