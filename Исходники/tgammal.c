static long double stirf(long double x)
{
	long double y, w, v;

	w = 1.0L/x;
	/* For large x, use rational coefficients from the analytical expansion.  */
	if (x > 1024.0L)
		w = (((((6.97281375836585777429E-5L * w
		      + 7.84039221720066627474E-4L) * w
		      - 2.29472093621399176955E-4L) * w
		      - 2.68132716049382716049E-3L) * w
		      + 3.47222222222222222222E-3L) * w
		      + 8.33333333333333333333E-2L) * w
		      + 1.0L;
	else
		w = 1.0L + w * polevll( w, STIR, 8 );
	y = expl(x);
	if (x > MAXSTIR)
	{ /* Avoid overflow in pow() */
		v = powl(x, 0.5L * x - 0.25L);
		y = v * (v / y);
	}
	else
	{
		y = powl(x, x - 0.5L) / y;
	}
	y = SQTPI * y * w;
	return (y);
}