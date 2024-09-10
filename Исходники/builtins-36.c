long double test1l(long double x)
{
	long double y1, y2;

	y1 = sinl(x);
	y2 = cosl(x);

	return y1 - y2;
}