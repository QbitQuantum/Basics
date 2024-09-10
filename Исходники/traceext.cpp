extern "C" VOID SQL_API TraceFirstEntry( char* szDriverDLLName )
{
#ifndef DISABLE_TRACE
	EnterCriticalSection2(&g_csWrite);

	if (!fhTraceFile)
	{
		(void) TraceOpenLogFile((LPWSTR)szGlobalTraceFileName,NULL,0);
		if (!fhTraceFile)
		{
		   	LeaveCriticalSection2(&g_csWrite);
			return;
		}
	}

	traceInfo(szDriverDLLName);
	fflush(fhTraceFile);

	LeaveCriticalSection2(&g_csWrite);
#endif
}