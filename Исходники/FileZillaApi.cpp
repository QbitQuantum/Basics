int CFileZillaApi::Connect(const t_server &server)
{
	//Check parameters
	if (server.host==_MPT("") || server.port<1 || server.port>65535)
		return FZ_REPLY_INVALIDPARAM;

#ifndef MPEXT_NO_GSS
	BOOL bUseGSS = FALSE;
	if (COptions::GetOptionVal(OPTION_USEGSS))
	{
		USES_CONVERSION;

		CString GssServers = COptions::GetOption(OPTION_GSSSERVERS);
		hostent *fullname = gethostbyname(T2CA(server.host));
		CString host;
		if (fullname)
			host = fullname->h_name;
		else
			host = server.host;
		host.MakeLower();
		int i;
		while ((i=GssServers.Find( _T(";") ))!=-1)
		{
			if ((_MPT(".")+GssServers.Left(i))==host.Right(GssServers.Left(i).GetLength()+1) || GssServers.Left(i)==host)
			{
				bUseGSS = TRUE;
				break;
			}
			GssServers = GssServers.Mid(i+1);
		}
	}
	if (!bUseGSS && server.user == _MPT(""))
		return FZ_REPLY_INVALIDPARAM;
#endif

	if (!(server.nServerType&FZ_SERVERTYPE_HIGHMASK))
		return FZ_REPLY_INVALIDPARAM;

	//Check if call allowed
	if (!m_bInitialized)
		return FZ_REPLY_NOTINITIALIZED;
	if (m_pMainThread->IsBusy())
		return FZ_REPLY_BUSY;

	t_command command;
	command.id=FZ_COMMAND_CONNECT;
	command.server=server;
	m_pMainThread->Command(command);
	if (m_hOwnerWnd)
		return FZ_REPLY_WOULDBLOCK;
	else
		return m_pMainThread->LastOperationSuccessful()?FZ_REPLY_OK:FZ_REPLY_ERROR;
}