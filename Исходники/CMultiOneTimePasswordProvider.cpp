// Get user and domain from session information
void CMultiOneTimePasswordProvider::_GetUserAndDomainName()
{
	PWSTR szUserName   = NULL;
	PWSTR szDomainName = NULL;
	DWORD dwLen;

#ifdef _DEBUG
	//*************************** DEBUG:
	OutputDebugStringA("szUserName: (BEFORE) \t");   if (_szUserName   != NULL) OutputDebugStringW(_szUserName);   else OutputDebugStringA("NULL"); OutputDebugStringA("\n");	
	OutputDebugStringA("szDomainName: (BEFORE) \t"); if (_szDomainName != NULL) OutputDebugStringW(_szDomainName); else OutputDebugStringA("NULL"); OutputDebugStringA("\n");	
	//*/
#endif

	if ( ! WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE,
				WTS_CURRENT_SESSION,
				WTSUserName,
				&szUserName,
				&dwLen)) szUserName = NULL;

	if ( ! WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE,
				WTS_CURRENT_SESSION,
				WTSDomainName,
				&szDomainName,
				&dwLen)) szDomainName = NULL;

	_szUserName   = (szUserName   != NULL && szUserName[0]   != NULL) ? StrDupW(szUserName)   : NULL;
	_szDomainName = (szDomainName != NULL && szDomainName[0] != NULL) ? StrDupW(szDomainName) : NULL;

	if (szUserName != NULL)   WTSFreeMemory(szUserName);
	if (szDomainName != NULL) WTSFreeMemory(szDomainName);

#ifdef _DEBUG
	//*************************** DEBUG:
	OutputDebugStringA("_szUserName: \t");   if (_szUserName   != NULL) OutputDebugStringW(_szUserName);   else OutputDebugStringA("NULL"); OutputDebugStringA("\n");	
	OutputDebugStringA("_szDomainName: \t"); if (_szDomainName != NULL) OutputDebugStringW(_szDomainName); else OutputDebugStringA("NULL"); OutputDebugStringA("\n");	
	//*/
#endif
}