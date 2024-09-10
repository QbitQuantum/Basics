/*
 * @implemented
 */
unsigned char * _mbsdup(const unsigned char *_s)
{
	unsigned char *rv;
	if (_s == 0)
		return 0;
	rv = (unsigned char *)malloc(_mbslen(_s) + 1);
	if (rv == 0)
		return 0;
	_mbscpy(rv, _s);
	return rv;
}