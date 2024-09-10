void __cdecl DebugPrintA(__in_z __format_string LPCSTR lpcszFormat, ...) 
{ 
	va_list pArguments; 
	char szDebugBuffer[1024];
	va_start(pArguments, lpcszFormat); 
	if (SUCCEEDED(StringCchVPrintfA(szDebugBuffer, _countof(szDebugBuffer), lpcszFormat, pArguments))) 
		OutputDebugStringA(szDebugBuffer); 
	va_end(pArguments); 
}