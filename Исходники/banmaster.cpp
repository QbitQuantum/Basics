int SendResponse(NETADDR *pAddr, NETADDR *pCheck)
{
	static char aIpBan[sizeof(BANMASTER_IPBAN) + 32 + 256] = { 0 };
	static char *pIpBanContent = aIpBan + sizeof(BANMASTER_IPBAN);
	if (!aIpBan[0])
		mem_copy(aIpBan, BANMASTER_IPBAN, sizeof(BANMASTER_IPBAN));
	
	static CNetChunk p;
	
	p.m_ClientID = -1;
	p.m_Address = *pAddr;
	p.m_Flags = NETSENDFLAG_CONNLESS;

	CBan* pBan = CheckBan(pCheck);
	if(pBan)
	{
		str_format(pIpBanContent, 32, "%d.%d.%d.%d", pCheck->ip[0], pCheck->ip[1], pCheck->ip[2], pCheck->ip[3]);
		char *pIpBanReason = pIpBanContent + (str_length(pIpBanContent) + 1);
		str_copy(pIpBanReason, pBan->m_aReason, 256);
		
		p.m_pData = aIpBan;
		p.m_DataSize = sizeof(BANMASTER_IPBAN) + str_length(pIpBanContent) + 1 + str_length(pIpBanReason) + 1;
		m_Net.Send(&p);
		return 1;
	}
	else
	{
		p.m_DataSize = sizeof(BANMASTER_IPOK);
		p.m_pData = BANMASTER_IPOK;
		m_Net.Send(&p);
		return 0;
	}
}