void UGStr::stprintf(TCHAR * dest, size_t size, const TCHAR * src, ...)
{
	va_list vl;
	va_start( vl, src );

#ifdef _UNICODE
#if _MSC_VER >= 1400
	_vswprintf_s_l(dest, size, src, NULL, vl);
#else
	UNREFERENCED_PARAMETER(size);
	_vstprintf(dest, src, vl);
# endif
#else
#if _MSC_VER >= 1400
    _vsprintf_s_l(dest, size, src, NULL, vl);
#else
	UNREFERENCED_PARAMETER(size);
	_vstprintf(dest, src, vl);
# endif
#endif

	va_end( vl );
}