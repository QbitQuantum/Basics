BOOL HttpComm::Connect( ULONG targetIP )
{
	char szPort[255] = {0};

	sprintf_s(szPort,"%d",g_ConfigInfo.nPort);

	IN_ADDR connectIP;
	connectIP.S_un.S_addr = targetIP;
	
	tstring strIp;

	if (m_ssl)
	{
		strIp = _T("https://");

		strIp += a2t(inet_ntoa(connectIP));
		strIp += _T(":");

		if (g_ConfigInfo.nPort != 443)
			strIp += a2t(szPort);
	}
	else
	{
		strIp = _T("http://");

		strIp += a2t(inet_ntoa(connectIP));
		strIp += _T(":");

		if (g_ConfigInfo.nPort != 80)
			strIp += a2t(szPort);
	}


	if (!m_http)
	{
		m_http = new ctx::http(strIp.c_str());
	}
	else
	{
		m_http->UpdateUrl(strIp.c_str());
	}

	return m_http != NULL;
}