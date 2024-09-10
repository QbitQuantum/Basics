/* for uint64_t instance */
uintmax_t
wcstoumax(const wchar_t *nptr, wchar_t **endptr, int base)
{
	return ((uintmax_t)wcstoull(nptr, endptr, base));
}