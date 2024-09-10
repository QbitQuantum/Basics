int ivsprintf(ichar *buffer, size_t max_size, const ichar *format, va_list argptr)
{
#ifdef UNICODE__ICHAR_WIDE
#ifdef _INC_SWPRINTF_INL_
	return  vswprintf(buffer, max_size, format, argptr);
#else
	return  vswprintf(buffer, format, argptr);
#endif
#else
	return  vsprintf(buffer, format, argptr);
#endif	
}