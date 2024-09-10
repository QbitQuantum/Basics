TCHAR *vncImportACL::AddDomainname(const TCHAR *user){
	unsigned long buflen = MAXLEN;
	TCHAR domain[MAXLEN * sizeof(wchar_t)];
	LPWKSTA_INFO_100 wkstainfo = NULL;
	NET_API_STATUS nStatus;

	nStatus = NetWkstaGetInfo( 0 , 100 , (LPBYTE *) &wkstainfo);
	if (nStatus == NERR_Success)
		_tcsncpy(domain, wkstainfo->wki100_langroup, MAXLEN);
	else
		_ftprintf(stderr, _T("NetWkstaGetInfo() returned %lu \n"), wkstainfo);
	domain[MAXLEN - 1] = _T('\0');
	_ftprintf(stderr, _T("Detected domain = %s\n"),domain);
	NetApiBufferFree(wkstainfo);
	wkstainfo = NULL;

	// Length of domainname and user minus beginning dots plus terminating '\0'.
	TCHAR *domainaccount = new TCHAR[_tcslen(domain) + _tcslen(user) - 1];
	_tcscpy(domainaccount, domain);
	_tcscat(domainaccount, user + 2);

	return domainaccount;
}