long double complex
ccosl(long double complex z)
{
	long double complex w;
	long double ch, sh;

	_cchshl(cimagl(z), &ch, &sh);
	w = cosl(creall(z)) * ch - (sinl(creall(z)) * sh) * I;
	return w;
}