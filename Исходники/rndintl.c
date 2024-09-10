long double
anintl(long double x) {
	long double t, w, z;

	if (!finitel(x))
		return (x + x);
	w = fabsl(x);
	t = rintl(w);
	if (t == w)
		return (copysignl(t, x));
	z = t - w;
	if (z > qhalf)
		t = t - qone;
	else if (z <= qmhalf)
		t = t + qone;
	return (copysignl(t, x));
}