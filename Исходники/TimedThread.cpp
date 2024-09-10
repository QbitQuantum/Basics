void CTimedThread::GetMachineName( void )
{

	DWORD dwLevel            = 102;
	LPWKSTA_INFO_102 pBuf    = NULL;
	LPTSTR pszServerName     = NULL;
	NET_API_STATUS nStatus;

	nStatus = NetWkstaGetInfo(pszServerName,dwLevel,(LPBYTE *)&pBuf);
	if ( nStatus == NERR_Success)
	{
		CString lDomain( (LPWSTR)pBuf->wki102_langroup);
		CString lHost  ( (LPWSTR)pBuf->wki102_computername);
		FullName.Format("%s.%s",lHost,lDomain);

	}

	if ( pBuf != NULL )
	{
		NetApiBufferFree(pBuf);
		pBuf = NULL;
	}
}