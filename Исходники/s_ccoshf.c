float complex
ccoshf(float complex z)
{
	float complex w;
	float x, y;

	x = creal(z);
	y = cimag(z);
	w = coshf (x) * cosf (y)  +  (sinhf (x) * sinf (y)) * I;
	return (w);
}