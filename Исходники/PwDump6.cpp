bool GetPhysicalPathForShare(char* szServer, char* lpszShare, char** lpszPhysicalPath, int nBufferSize)
{
	PSHARE_INFO_502 BufPtr;
	NET_API_STATUS res;
	wchar_t share[MAX_PATH];
	wchar_t server[MAX_PATH];
	char szTemp[MAX_PATH];
	char szServerWithSlashes[MAX_PATH];
	bool bRet = false;


	::ZeroMemory(server, MAX_PATH);
	::ZeroMemory(share, MAX_PATH);
	::ZeroMemory(szServerWithSlashes, MAX_PATH);
	::ZeroMemory(*lpszPhysicalPath, nBufferSize);
	_snprintf(szServerWithSlashes, MAX_PATH, "%s", szServer);
	mbstowcs(server, szServerWithSlashes, strlen(szServerWithSlashes));
	mbstowcs(share, lpszShare, strlen(lpszShare));
  
	// Try to get share information
	res = NetShareGetInfo(server, share, 502, (LPBYTE*)&BufPtr);
	if(res == ERROR_SUCCESS)
	{
		// It is assumed that we've already tested for whether we can write to this share
		::ZeroMemory(szTemp, MAX_PATH);
		wcstombs(szTemp, (LPWSTR)(BufPtr->shi502_netname), MAX_PATH);

		// Copy the physical path to the out variable
		wcstombs(szTemp, (LPWSTR)(BufPtr->shi502_path), MAX_PATH);
		strncpy(*lpszPhysicalPath, szTemp, nBufferSize);
		bRet = true;

		NetApiBufferFree(BufPtr);
		return bRet;
	}
	else
	{
			printf("GetPhysicalPathForShare returned an error of %ld, are you sure the share you specified exists?\n", res);
	}

	return false;

}