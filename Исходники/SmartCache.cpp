void CALLBACK MyEnumerateCacheCallback(INTERNET_CACHE_ENTRY_INFO* pCacheEntryInfo)
{
	if (!pCacheEntryInfo)
		return;

	CString strUrlName = pCacheEntryInfo->lpszSourceUrlName;
	int iPos = strUrlName.Find("?");
	if (iPos >= 0)
		strUrlName = strUrlName.Left(iPos);
	strUrlName += "\n";
	ATLTRACE(strUrlName);
	BOOL bOK = DeleteUrlCacheEntry(pCacheEntryInfo->lpszSourceUrlName);
}