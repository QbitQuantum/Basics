void CConfigManager::ReadRouteTCPListen(int *pPorts, unsigned long *pIP)
{
	char BuffIP[16];

	*pPorts = GetPrivateProfileIntA("TCP_SOCKET", "LISTEN_LOCAL_PORT", -1, "Config\\PostofficeRoute\\PostofficeRoute.ini");
	GetPrivateProfileStringA("TCP_SOCKET", "LISTEN_LOCAL_IP", "255.255.255.255", BuffIP, 16, "Config\\PostofficeRoute\\PostofficeRoute.ini");

	*pIP = inet_addr(BuffIP);
	unsigned long L =inet_addr("255.255.255.255");

	MTVERIFY( -1!=*pPorts );
	MTVERIFY( L!=*pIP );

}