double
ldexp(double value, int exp0)
{
	if(!finite(value)||value==0.0) return value;
	value = scalbn(value,exp0);
	/*if(!finite(value)||value==0.0) errno = POK_ERRNO_ERANGE;*/
	return value;
}