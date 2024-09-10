long double
roundl(long double x)
{
	long double t;

	if (!isfinite(x))
		return (x);

	if (x >= 0.0) {
		t = floorl(x);
		if (t - x <= -0.5)
			t += 1.0;
		return (t);
	} else {
		t = floorl(-x);
		if (t + x <= -0.5)
			t += 1.0;
		return (-t);
	}
}