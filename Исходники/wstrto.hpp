unsigned long long strto<unsigned long long>(const wchar_t *str, wchar_t **str_end, int base)
{
	return wcstoull(str, str_end, base);
}