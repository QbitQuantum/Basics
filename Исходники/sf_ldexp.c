float ldexpf(float value, int exp)
{
	if(!finitef(value)||value==(float)0.0) return value;
	value = scalbnf(value,exp);
	if(!finitef(value)||value==(float)0.0) errno = ERANGE;
	return value;
}