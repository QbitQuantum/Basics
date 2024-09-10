long double complex
csinl(long double complex z)
{
	long double complex w;
	long double ch, sh;

	cchshl(cimagl(z), &ch, &sh);
	w = sinl(creall(z)) * ch + (cosl(creall(z)) * sh) * I;
	return (w);
}