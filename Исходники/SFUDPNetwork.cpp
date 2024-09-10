bool SFUDPNetwork::Start()
{
	GetPrivateProfileStringA("UDPInfo", "IP", NULL, m_IP, 20, "./Connection.ini");
	m_Port = GetPrivateProfileIntA("UDPInfo", "PORT", 0, "./Connection.ini");

	if(m_P2PModule)
		m_P2PModule->RunP2P(m_IP, m_Port);

	return true;
}