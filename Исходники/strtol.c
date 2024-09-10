Long
strToL(const char *nptr, char **endptr, int base)
{
	Long		value;

	value = (Long)strTouL(nptr, endptr, base);
	if (Long_neg) {
		if (value >= 0) {
			value = lONG_MIN;
			errno = ERANGE;
		}
	} else if (value < 0) {
		value = lONG_MAX;
		errno = ERANGE;
	}
	return (value);
}