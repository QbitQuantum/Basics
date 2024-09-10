bool CHttpHelper::connect(void)
{
	m_hConnect = InternetOpen("pocketnoc", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if(m_hConnect == NULL)
		return false;
	
	m_hSession = InternetConnect(m_hConnect,
							   m_routerSettings->routerServer,
							   m_routerSettings->routerPort,
							   m_routerSettings->routerUser,
							   m_routerSettings->routerPass,
							   INTERNET_SERVICE_HTTP,
							   0,
							   0);

	if(m_hSession == NULL) {
		InternetCloseHandle(m_hConnect);
		return false;
	}

	return true;
}