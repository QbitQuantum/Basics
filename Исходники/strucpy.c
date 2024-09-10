char *
strucpy (
	char	*optr,			/* => output string		*/
	char	*iptr)			/* => input string		*/
{
	if (!iptr)	iptr = optr;

	while (*iptr)
	{
		*optr++ = _toupper(*iptr);
		iptr++;
	}
	*optr = '\0';			/* Copy a trailing null		*/
	return (optr);
}