void UTBStr::sprintf(char * dest, size_t size, const char * src, ...)
{
	va_list vl;
	va_start( vl, src );

#if _MSC_VER >= 1400
    _vsprintf_s_l(dest, size, src, NULL, vl);
#else
	UNREFERENCED_PARAMETER(size);
	vsprintf(dest, src, vl);
# endif

	va_end( vl );
}