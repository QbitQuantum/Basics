//////////////////////////////////////////////////////////////////
// void InternalTrace
//
//////////////////////////////////////////////////////////////////
void InternalTrace(const WCHAR*	pwszFmt, ...)
{
	va_list		marker;
	WCHAR		wszBuffer[MAX_TRACE_LEN];
	CHAR		szBuffer[MAX_TRACE_LEN];

	// Use format and arguements as input
	//This version will not overwrite the stack, since it only copies
	//upto the max size of the array
	va_start(marker, pwszFmt);
	_vsnwprintf(wszBuffer, MAX_TRACE_LEN, pwszFmt, marker);
	va_end(marker);

	//Make sure there is a NULL Terminator, vsnwprintf will not copy
	//the terminator if length==MAX_TRACE_LEN
	wszBuffer[MAX_TRACE_LEN-2] = L'\n';
	wszBuffer[MAX_TRACE_LEN-1] = L'\0';
	
	//Convert to MBCS
	ConvertToMBCS(wszBuffer, szBuffer, MAX_TRACE_LEN);
	
	//Output to the DebugWindow
	for(ULONG x=0; x <= strlen(szBuffer); x+=1029)
		OutputDebugStringA(szBuffer+x);
}