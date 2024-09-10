u64 CInifileEx::r_u64(LPCSTR S, LPCSTR L)
{
	LPCSTR		C = r_string(S,L);
#ifndef _EDITOR
	return		_strtoui64(C,NULL,10);
#else
	return		(u64)_atoi64(C);
#endif
}