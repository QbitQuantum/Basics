long32_t EXP_LVL9 CS_strtol (Const char *ptr,char **endPtr,int base)
{
#ifdef __WINCE__
	wchar_t *wEndPtr;
	long32_t rtnValue;
	wchar_t wAscii [64];
	mbstowcs (wAscii,ptr,64);
	rtnValue = (long32_t)wcstol (wAscii,&wEndPtr,base);
	*endPtr = (char *)ptr + (wEndPtr - wAscii);
	return rtnValue;
#else
	/* time is ANSI standard, so this part is easy. */
	return (long32_t)strtol (ptr,endPtr,base);
#endif
}