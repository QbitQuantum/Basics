/// Prints to stdout if it is a console application
void SHVConsole::PrintfList16(const SHVWChar* str, SHVVA_LIST args)
{
SHVVA_LIST argList;
	SHVVA_COPY( argList, args );
#ifdef __SHIVA_POSIX
	printf("%s", SHVString16C::FormatList(str, argList).ToStrT().GetSafeBuffer());
#else
	vwprintf((const WCHAR*)str,argList);
#endif
	SHVVA_END( argList );
}