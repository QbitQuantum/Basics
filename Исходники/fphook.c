static char *
_pfloat(long double r, register char *s, int n, int flags)
{
	register char *s1;
	int sign, dp;
	register int i;

	s1 = _fcvt(r, n, &dp, &sign);
	if (sign)
		*s++ = '-';
	else if (flags & FL_SIGN)
		*s++ = '+';
	else if (flags & FL_SPACE)
		*s++ = ' ';

	if (dp<=0)
		*s++ = '0';
	for (i=dp; i>0; i--)
		if (*s1) *s++ = *s1++;
		else *s++ = '0';
	if (((i=n) > 0) || (flags & FL_ALT))
		*s++ = '.';
	while (++dp <= 0) {
		if (--i<0)
			break;
		*s++ = '0';
	}
	while (--i >= 0)
		if (*s1) *s++ = *s1++;
		else *s++ = '0';
	return s;
}