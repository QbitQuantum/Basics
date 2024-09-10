// Note: This may be Windows specific way of handling
// variable args--there are other methods.
void sml::PrintDebugFormat(char const* pFormat, ...)
{
	va_list args;
	va_start(args, pFormat);

	char szBuffer[10000];

	int nBuf = VSNPRINTF(szBuffer, sizeof(szBuffer), pFormat, args);

	// was there an error? was the expanded string too long?
	if (nBuf < 0)
	{
		strcpy(szBuffer, "** Debug message too long for PrintDebugFormat's buffer **") ;
	}

#ifdef DEBUG_CALLS
	CTDebugEnterMethod::PrintStackTrace() ;

	PrintDebugMethod(CTDebugEnterMethod::GetCurrentMethodName(), szBuffer) ;
#else
	PrintDebugSimple(szBuffer) ;
#endif

	va_end(args);
}