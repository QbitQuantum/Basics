float complex
ctanf(float complex z)
{
	float complex w;
	float d;

	d = cosf( 2.0f * crealf(z) ) + coshf( 2.0f * cimagf(z) );

	if(fabsf(d) < 0.25f)
		d = _ctansf(z);

	if (d == 0.0f) {
		/*mtherr( "ctanf", OVERFLOW );*/
		w = MAXNUMF + MAXNUMF * I;
		return (w);
	}
	w = sinf (2.0f * crealf(z)) / d + (sinhf (2.0f * cimagf(z)) / d) * I;
	return (w);
}