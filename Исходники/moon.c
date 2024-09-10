long double fmod360(long double d)
{
	d = fmodl(d, 360);
	if (d < 0) d += 360;
	return d;
}