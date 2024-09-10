wchar_t *
StrToUnicode( const char *buf )
{
	wchar_t unibuf[1024];
	ASCIIToUnicode( buf, unibuf, sizeof(unibuf) );
	return _wcsdup( unibuf );
}