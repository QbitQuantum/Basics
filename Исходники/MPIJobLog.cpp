// Note: I could overload LogMsg to take a WCHAR* as the first argument but
//       this way I am less likely to match the WCHAR* version with a char* argument
//       or vice versa.  It would also conflict with the UNICODE build.
// Function name	: LogWMsg
// Description	    : 
// Return type		: void 
// Argument         : WCHAR* pFormat
// Argument         : ...
void LogWMsg(WCHAR* pFormat, ...)
{
    WCHAR    wchMsg[LOCAL_BUFFER_SIZE];
    va_list pArg;

    va_start(pArg, pFormat);
    vswprintf(wchMsg, pFormat, pArg);
    va_end(pArg);

	//*
	openlog("MPILauncher", LOG_APP);
	char msg[LOCAL_BUFFER_SIZE];
	wcstombs(msg, wchMsg, wcslen(wchMsg)+1);
	syslog(LOG_INFO, msg);
	closelog();
	/*/
	WaitForSingleObject(g_hLogMutex, INFINITE);
	FILE *fout = _tfopen(MPIJOB_LOG_FILENAME, TEXT("a"));
	if (fout != NULL)
	{
		fprintf(fout, "%4d :%7u ", GetCurrentThreadId(), clock());
		fwprintf(fout, L"%s", wchMsg);
		fclose(fout);
	}
	ReleaseMutex(g_hLogMutex);
	//*/
}