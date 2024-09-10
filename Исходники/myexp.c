float myexp(float x)
{
	int sign = +1;

	if (x < 0)
		sign = -1;

	x = abs(x);

	const float z = x * M_LOG2E;
	const int m = floorf(z);
	const float w = z - m;
	float r = 0.0;
	const float u = w * M_LN2;

	float r1 = ldexpf(1, m);

	float r2 = 1.0/5040;;

	//r2 = fmaf(r2, x, 1.0/5040);
	r2 = fmaf(r2, x, 1.0/720);
	r2 = fmaf(r2, x, 1.0/120);
	r2 = fmaf(r2, x, 1.0/24);
	r2 = fmaf(r2, x, 1.0/6);
	r2 = fmaf(r2, x, 0.5);
	r2 = fmaf(r2, x, 1);
	r2 = fmaf(r2, x, 1);

	r = fmaf(r1, r2, 0);
	//r = r1 * r2;

	return (sign < 0)? 1.0/r : r;
}