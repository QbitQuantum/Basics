inline bool wcs_whitespace(const wchar_t c)
{
	return (c) && (iswcntrl(c) || iswspace(c));	//return (c == L' ') || (c == L'\t') || (c == L'\n') || (c == L'\r');
}