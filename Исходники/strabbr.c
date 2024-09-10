int
strabbr (
	char	*tst_,
	char	*ref_,
	int	cmplen,
	int	abbr)
{
	while (*tst_ && *ref_ && (cmplen > 0))
	{
		if (_toupper(*tst_) != _toupper(*ref_))	break;
		tst_++;
		ref_++;
		cmplen--;
		abbr--;
	}
	return ((abbr <= 0) && (cmplen <= 0));
}