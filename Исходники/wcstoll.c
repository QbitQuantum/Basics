long long
_wcstoll_r (struct _reent *rptr,
	const wchar_t *nptr,
	wchar_t **endptr,
	int base)
{
	return _wcstoll_l (rptr, nptr, endptr, base, __get_current_locale ());
}