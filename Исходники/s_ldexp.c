long double ldexpl(long double value, int exp)
{
	if(!isfinite(value)||value==0.0) return value;
	value = scalbnl(value,exp);
//	if(!finitel(value)||value==0.0) errno = ERANGE;
	return value;
}