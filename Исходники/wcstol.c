uintmax_t wcstoumax(const wchar_t *s, wchar_t **p, int base)
{
	return wcstoull(s, p, base);
}