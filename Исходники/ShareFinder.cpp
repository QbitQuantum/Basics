bool ShareFinder::GetAvailableWriteableShare(char* szServer, int nPhysicalBufferSize, char** lplpPhysicalPath, int nUNCPathSize, char** lplpUNCPath)
{
	// Returns the drive letter if successful, otherwise 0
	PSHARE_INFO_502 BufPtr, p;
	NET_API_STATUS res;
	DWORD er = 0, tr = 0, resume = 0, i;
	wchar_t server[MAX_PATH];
	char szTemp[MAX_PATH], szTemp2[MAX_PATH];
	bool bFound = false;
	char szServerWithSlashes[MAX_PATH];

	::ZeroMemory(server, MAX_PATH);
	::ZeroMemory(szServerWithSlashes, MAX_PATH);
	::ZeroMemory(*lplpPhysicalPath, nPhysicalBufferSize);
	::ZeroMemory(*lplpUNCPath, nUNCPathSize);
	_snprintf_s(szServerWithSlashes, MAX_PATH, 2+strlen(szServer), "\\\\%s", szServer);
	
	size_t requiredSize = 0;
	
	mbstowcs_s(&requiredSize, server, MAX_PATH, szServerWithSlashes, strlen(szServerWithSlashes));

	do
	{
		// F**k Microsoft and it's lame-ass unicode crap
		res = NetShareEnum((LPWSTR)server, 502, (LPBYTE*)&BufPtr, -1, &er, &tr, &resume);
		if(res == ERROR_SUCCESS || res == ERROR_MORE_DATA)
		{
			p = BufPtr;
			for(i = 1; i <= er; i++)
			{
				::ZeroMemory(szTemp, MAX_PATH);
				size_t requiredSize2 = 0;

				wcstombs_s(&requiredSize, szTemp, MAX_PATH, (LPWSTR)(p->shi502_netname), MAX_PATH);

				// Look for shares that are not SYSVOL or NETLOGON, and that have a physical path
				if (((p->shi502_type == STYPE_DISKTREE) || (p->shi502_type == STYPE_SPECIAL)) /*&& stricmp(szTemp, "QS1LPT3") != 0*/ && _stricmp(szTemp, "SYSVOL") != 0 && _stricmp(szTemp, "NETLOGON") != 0 && wcslen((LPWSTR)(p->shi502_path)) > 0)
				{
					// If this is a potentially workable share, try uploading something
					memset(szTemp2, 0, MAX_PATH);
					_snprintf_s(szTemp2, MAX_PATH, strlen(szServerWithSlashes)+1+strlen(szTemp), "%s\\%s", szServerWithSlashes, szTemp);
					if (CanUpload(szTemp2))
					{
						// Success!
						// Copy the physical path to the out variable
						size_t requiredSize3 = 0;

						wcstombs_s(&requiredSize3, szTemp, MAX_PATH, (LPWSTR)(p->shi502_path), MAX_PATH);
						strncpy_s(*lplpPhysicalPath, MAX_PATH, szTemp, nPhysicalBufferSize);

						// Also copy the UNC path to the out variable
						strncpy_s(*lplpUNCPath, MAX_PATH, szTemp2, nUNCPathSize);
						bFound = true;
						break;
					}

					// Otherwise continue and try another share
				}
				
				p++;
			}

			NetApiBufferFree(BufPtr);
		}
		else 
			Log.CachedReportError(m_nCacheID, CRITICAL, "BindUploadShareToLocalDrive returned an error of %ld\n",res);
	}
	while (res == ERROR_MORE_DATA); // end do

	return bFound;
}