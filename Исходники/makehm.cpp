BOOL IsValidSymbol(const TCHAR* psz)
{
#ifdef UNICODE
	if (!__iswcsymf(*psz))
#else
	if (!__iscsymf(*psz))
#endif
		return FALSE;

	ASSERT(*psz != 0);
	++psz;
	while (*psz)
	{
#ifdef UNICODE
		if (!__iswcsym(*psz))
#else
		if (!__iscsym(*psz))
#endif
			return FALSE;
		++psz;
	}
	return TRUE;
}