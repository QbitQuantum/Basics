BOOL CDDEServer::Execute(LPCTSTR pszTopic, HDDEDATA hData, HDDEDATA* phResult)
{
	DWORD nLength	= 0;
	LPVOID pData	= DdeAccessData( hData, &nLength );

	BOOL bResult = Execute( pszTopic, pData, nLength );

	DdeUnaccessData( hData );

	*phResult = (HDDEDATA)( bResult ? DDE_FACK : DDE_FNOTPROCESSED );

	return bResult;
}