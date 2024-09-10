bool CHttpReqSocket::IsInternetConnected ()
{
	return true;	// MCH 17.09.04 (what the heck...)

	//////////////////////////////////////////////////////////////

	DWORD dwState;
	InternetGetConnectedState (&dwState, 0);

	if (dwState & INTERNET_CONNECTION_LAN)
		return true;
	else
	{
		bool bConnected = false;
		RASCONN rasConn;
		rasConn.dwSize = sizeof (RASCONN);
		DWORD dwBufSize = sizeof (RASCONN);
		DWORD dwNumConns;
		if (RasEnumConnections (&rasConn, &dwBufSize, &dwNumConns) == 0)
		{
			// RasEnumConnections succeeded
			RASCONNSTATUS rasConnStatus;
			for (UINT i = 0; i < dwNumConns; i++)
			{
				rasConnStatus.dwSize = sizeof (RASCONNSTATUS);
				RasGetConnectStatus (rasConn.hrasconn, &rasConnStatus);
				if (rasConnStatus.rasconnstate == RASCS_Connected)
				{
					bConnected = true;
					break;
				}
			}
		}

		return bConnected;
	}
}