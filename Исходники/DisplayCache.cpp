//////////////////////////////////////////////////////////////////////
// Methode : CDisplayCache
// Resume : Display cahce entry
// In : INTERNET_CACHE_ENTRY_INFO
// Out : None
//////////////////////////////////////////////////////////////////////
void CDisplayCache::DisplayCacheEntry(INTERNET_CACHE_ENTRY_INFO* pInfo)
{
	SetConsoleCP(1252);
	CString strTemp;

	printf("------->\n");

	if (m_bDisp_dwStructSize)
	{
			printf(" Structure Size     : %s \n", DWORD2String(pInfo->dwStructSize));
	}
	if (m_bDisp_lpszSourceUrlName)
	{
		if (pInfo->lpszSourceUrlName) printf(" Source URL Name    : %s \n", pInfo->lpszSourceUrlName);
		else printf(" Source URL Name    : \n");
	}
	if (m_bDisp_lpszLocalFileName)
	{
		if (pInfo->lpszLocalFileName) printf(" Local File Name    : %s \n", pInfo->lpszLocalFileName);
		else printf(" Local File Name    : \n");
	}
	if (m_bDisp_CacheEntryType)
	{
		printf(" Type               : %s \n", GetCacheType(pInfo->CacheEntryType));
	}
	if (m_bDisp_dwUseCount)
	{
		printf(" Use Count          : %s \n", DWORD2String(pInfo->dwUseCount));
	}
	if (m_bDisp_dwHitRate)
	{
		printf(" Hit Rate           : %s \n", DWORD2String(pInfo->dwHitRate));
	}
	if (m_bDisp_dwSizeLow)
	{
		printf(" Size Low           : %s \n", DWORD2String(pInfo->dwSizeLow));
	}
	if (m_bDisp_dwSizeHigh)
	{
		printf(" Size High          : %s \n", DWORD2String(pInfo->dwSizeHigh));
	}
	if (m_bDisp_LastModifiedTime)
	{
		printf(" Last Modified Time : %s \n", GetTime(pInfo->LastModifiedTime));
	}
	if (m_bDisp_ExpireTime)
	{
		printf(" Expire Time        : %s \n", GetTime(pInfo->ExpireTime));
	}
	if (m_bDisp_LastAccessTime)
	{
		printf(" Last Access Time   : %s \n", GetTime(pInfo->LastAccessTime));
	}
	if (m_bDisp_LastSyncTime)
	{
		printf(" Last Sync Time     : %s \n", GetTime(pInfo->LastSyncTime));
	}
	if (m_bDisp_lpHeaderInfo)
	{
		if (pInfo->lpHeaderInfo) 
		{
			printf(" Header Info        : ");
			printf("%s \n",pInfo->lpHeaderInfo);
		}
		else printf(" Header Info        : \n");

	}
	if (m_bDisp_dwHeaderInfoSize)
	{
		printf(" Header Info Size   : %s \n", DWORD2String(pInfo->dwHeaderInfoSize));
	}
	if (m_bDisp_lpszFileExtension)
	{
		if (pInfo->lpszFileExtension) printf(" File Extension     : %s \n",pInfo->lpszFileExtension);
		else printf(" File Extension     : \n");
	}
}