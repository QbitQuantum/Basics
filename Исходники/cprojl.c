long double complex cprojl(long double complex z)
{
	if (isinf(creall(z)) || isinf(cimagl(z)))
		return cpackl(INFINITY, copysignl(0.0, creall(z)));
	return z;
}