bool TSmartServer::GetSysItemInfo(HQUERY	hQuery, 
								 char *pszPath, 
								 DWORD nType, 
								 PDH_FMT_COUNTERVALUE& fmtValue)
{
	DWORD dwType;
	HCOUNTER  hCounter ;
	if( PdhAddCounter(hQuery, pszPath, 0, &hCounter) != ERROR_SUCCESS )
		return false;

	if( PdhCollectQueryData(hQuery) != ERROR_SUCCESS )
		return false;

	if( PdhGetFormattedCounterValue(hCounter, nType, &dwType, &fmtValue) != ERROR_SUCCESS )
		return false;

	return true;
}