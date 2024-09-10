void CCmd_Depots::OnOutputInfo( char level, LPCTSTR data, LPCTSTR msg )
{
	if( APP_ABORTING( ) && m_Asynchronous )
    {
		ReleaseServerLock();	
        ExitThread(0);
    }

	if ( StrNCmp(data, _T("Depot "), 6) ==0 )
		m_GotDepot = TRUE;
	else
		ASSERT(0);
	CTokenString str;
	str.Create( data + 6);

	CString depotName;
	depotName.Format(_T("//%s"), str.GetToken()); 
	CString date= str.GetToken();
	ASSERT(StrStr(date, _T("/")));
	
	CString depotType= str.GetToken();
	if( depotType.CompareNoCase(_T("local")) == 0)
		m_LocalDepotList.AddHead( depotName );
	else if( depotType.CompareNoCase(_T("remote")) == 0)
		m_RemoteDepotList.AddHead( depotName );
	else if( depotType.CompareNoCase(_T("spec")) == 0)
	{
		if (GET_SERVERLEVEL() >= 18)
			m_RemoteDepotList.AddHead( depotName );
	}
	else
		ASSERT(0);
}