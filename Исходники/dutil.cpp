/*******************************************************************
Dutil_Trace

*******************************************************************/
extern "C" void DAPI Dutil_Trace(
								 __in LPCSTR szFile,
								 __in int iLine,
								 __in REPORT_LEVEL rl,
								 __in LPCSTR szFormat,
								 ...
								 )
{
	AssertSz(REPORT_NONE != rl, "REPORT_NONE is not a valid tracing level");

	HRESULT hr = S_OK;
	char szOutput[DUTIL_STRING_BUFFER];
	char szMsg[DUTIL_STRING_BUFFER];

	if (Dutil_rlCurrentTrace < rl)
		return;

	va_list args;
	va_start(args, szFormat);
	hr = StringCchVPrintfA(szOutput, countof(szOutput), szFormat, args);
	va_end(args);

	if (SUCCEEDED(hr))
	{
		LPCSTR szPrefix = "Trace/u";
		char szMsg[DUTIL_STRING_BUFFER];
		switch (rl)
		{
		case REPORT_STANDARD:
			szPrefix = "Trace/s";
			break;
		case REPORT_VERBOSE:
			szPrefix = "Trace/v";
			break;
		case REPORT_DEBUG:
			szPrefix = "Trace/d";
			break;
		}

		if (Dutil_fTraceFilenames)
			hr = StringCchPrintfA(szMsg, countof(szMsg), "%s [%s,%d]: %s\r\n", szPrefix, szFile, iLine, szOutput);
		else
			hr = StringCchPrintfA(szMsg, countof(szMsg), "%s: %s\r\n", szPrefix, szOutput);

		if (SUCCEEDED(hr))
			OutputDebugStringA(szMsg);
		// else fall through to the case below
	}

	if (FAILED(hr))
	{
		if (Dutil_fTraceFilenames)
			StringCchPrintfA(szMsg, countof(szMsg), "Trace [%s,%d]: message too long, skipping\r\n", szFile, iLine);
		else
			StringCchPrintfA(szMsg, countof(szMsg), "Trace: message too long, skipping\r\n");
		OutputDebugStringA(szMsg);
	}
}