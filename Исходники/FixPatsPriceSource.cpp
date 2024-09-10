void FixPatsPriceSource::ReadIniConfig()
{ // 登录需要的参数 HeartBeatInterval,username,password
	m_HeartBeatInterval = 30;
	m_useSimEngine = 0;
	memset(m_szUsername,   0, sizeof(m_szUsername));
	memset(m_szPassword,   0, sizeof(m_szPassword));

	GetPrivateProfileStringA("FIXPATSGW", "LOGON_UID", "patsusername", m_szUsername, 16, ".\\AIB.ini");
	GetPrivateProfileStringA("FIXPATSGW", "LOGON_PWD", "patspassword", m_szPassword, 16, ".\\AIB.ini");
	m_HeartBeatInterval = GetPrivateProfileIntA("FIXPATSGW","LOGON_HBINT",30,".\\AIB.ini");
	m_useSimEngine = GetPrivateProfileIntA("FIXPATSGW","SIMENGINE_PS",0,".\\AIB.ini");
	TRACE_LOG("FixPatsPriceSource ReadIniConfig UID:%s,PWD:%s,HeartBeatInt:%d,UseSimEngine:%d.",m_szUsername,m_szPassword,m_HeartBeatInterval,m_useSimEngine);
}