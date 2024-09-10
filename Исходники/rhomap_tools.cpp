int my_finite(double x)
{
	#ifdef _MSC_VER
		return _finite(x);
	#else
		return finite(x);
	#endif
}