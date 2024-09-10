static void text_append_va(void *obj, const wgChar *format, va_list list)
{
#ifdef _UNICODE
	vwprintf(format, list);
#else
	vprintf(format, list);
#endif
}