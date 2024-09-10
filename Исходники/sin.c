static float get_0x1p120f(void)
{
#ifdef _MSC_VER
	return ldexpf(1.0, 120);
#else
	return 0x1p120f;
#endif
}